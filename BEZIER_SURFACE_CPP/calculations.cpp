#include "calculations.h"

double ***surface = nullptr;
double ***surfacePersp = nullptr;
const int DESIRED_N = 24,
          DESIRED_M = 24;

double*** dataCopy(double ***src, int n, int m) {
    double*** dest = new double**[n];

    for (int i = 0, j; i < n; ++i)
    {
        dest[i] = new double*[m];

        for (j = 0; j < m; ++j)
        {
            dest[i][j] = new double[3];
            dest[i][j][0] = src[i][j][0];
            dest[i][j][1] = src[i][j][1];
            dest[i][j][2] = src[i][j][2];
        }
    }

    return  dest;
}

void memFree(double ***data, int n, int m)
{
    if (!data) return;

    for (int i = 0, j; i < n; ++i)
    {
        for (j = 0; j < m; ++j)
            delete [] data[i][j];

        delete [] data[i];
    }
    delete [] data;
}

int factorial(int n)
{
    if (n == 1 || n == 0) return 1;
    else if (n == 2) return 2;
    else if (n == 3) return 6;
    else if (n == 4) return 24;
    else if (n == 5) return 120;
    else if (n == 6) return 720;
    else return factorial(n - 1) * n;
}

double getBernsteinPoly(int n, int i, double u, double factN = -1)
{
    if (factN < 0) factN = factorial(n);
    double B = factorial(n) / (factorial(i) * factorial(n - i));
    B *= pow(u, i) * pow(1 - u, n - i);

    return B;
}


double*** getSurfaceBezier(double ***data, int n, int m, int desN, int desM) //desired N, M
{
    double ***result = new double**[DESIRED_N + 1];

    for (int i = 0, j; i <= DESIRED_N; ++i)
    {
        result[i] = new double*[DESIRED_M + 1];

        for (j = 0; j <= DESIRED_M; ++j)
            result[i][j] = new double[3];
    }

    double STEP_N = 1./DESIRED_N,
           STEP_M = 1./DESIRED_M;
    double factN = factorial(n - 1),
           factM = factorial(m - 1);

    omp_set_dynamic(0);
    omp_set_num_threads(8);

#pragma omp parallel for shared(result) schedule(dynamic, DESIRED_N/8)
    for (int I = 0; I <= DESIRED_N * DESIRED_M; ++I)
    {
        int u = int(I / DESIRED_M);
        int v = I - u * DESIRED_M;
        double BU, BV, x = 0, y = 0, z = 0;

        for (int i = 0, j; i < n; ++i)
            for (j = 0; j < m; ++j)
            {
                BU = getBernsteinPoly(n-1, i, u * STEP_N, factN);
                BV = getBernsteinPoly(m-1, j, v * STEP_M, factM);

                x += BU * BV * data[i][j][0];
                y += BU * BV * data[i][j][1];
                z += BU * BV * data[i][j][2];
            }

        result[u][v][0] = x;
        result[u][v][1] = y;
        result[u][v][2] = z;
    }

    return result;
}

void rotateX(double ***data, int n, int m, double angle)
{
    double cosA = cos(angle);
    double sinA = sin(angle);
    double y, z;

    for (int i = 0, j; i < n; ++i)
        for (j = 0; j < m; ++j)
        {
            y = data[i][j][1];
            z = data[i][j][2];
            data[i][j][1] = y * cosA - z * sinA;
            data[i][j][2] = y * sinA + z * cosA;
        }
}

void rotateY(double ***data, int n, int m, double angle)
{
    double cosA = cos(angle);
    double sinA = sin(angle);
    double x, z;

    for (int i = 0, j; i < n; ++i)
        for (j = 0; j < m; ++j)
        {
            x = data[i][j][0];
            z = data[i][j][2];
            data[i][j][0] = x * cosA + z * sinA;
            data[i][j][2] = - x * sinA + z * cosA;
        }
}

void moveM(double ***data, int n, int m, double offx, double offy, double offz)
{
    for (int i = 0, j; i < n; ++i)
        for (j = 0; j < m; ++j)
        {
            data[i][j][0] += offx;
            data[i][j][1] += offy;
            data[i][j][2] += offz;
        }
}

void applyPerspective(double ***data, int n, int m, double x, double y, double z)
{
    moveM(data, n, m, -x, -y, -z);

    double r = - 1. / z;
    double h;

    for (int i = 0, j; i < n; ++i)
        for (j = 0; j < m; ++j)
        {
            h = 1. / (data[i][j][2] * r + 1);
            data[i][j][0] *= h;
            data[i][j][1] *= h;
            data[i][j][2] *= h;
        }

    moveM(data, n, m, x, y, z);
}


