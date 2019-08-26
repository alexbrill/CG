#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->drawArea->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    QGraphicsScene *scene = new QGraphicsScene();
    ui->drawArea->setScene(scene);
    ui->drawArea->setSceneRect(0, 0, ui->drawArea->viewport()->width(),
                               ui->drawArea->viewport()->height());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawTriangle(vect t0, vect t1, vect t2, vect &zbuffer, vect color) {
    if (t0[1]==t1[1] && t0[1]==t2[1]) return;
    if (t0[1]>t1[1]) std::swap(t0, t1);
    if (t0[1]>t2[1]) std::swap(t0, t2);
    if (t1[1]>t2[1]) std::swap(t1, t2);    

    QPen pen(QColor(rand() * color[0] % 255, rand() * color[1] % 255, rand() * color[2] % 255));
    int total_height = t2[1]-t0[1];
    for (int i=0; i<total_height; i++) {
        bool second_half = i>t1[1]-t0[1] || t1[1]==t0[1];
        int segment_height = second_half ? t2[1]-t1[1] : t1[1]-t0[1];
        float alpha = i/float(total_height);
        float beta  = float((i-(second_half ? t1[1]-t0[1] : 0))/float(segment_height));
        vect A = {int(t0[0] + (t2[0]-t0[0])*alpha),
                  int(t0[1] + (t2[1]-t0[1])*alpha),
                  int(t0[2] + (t2[2]-t0[2])*alpha)};

        vect B;
        if (second_half) B = {int(t1[0] + (t2[0]-t1[0])*beta),
                              int(t1[1] + (t2[1]-t1[1])*beta),
                              int(t1[2] + (t2[2]-t1[2])*beta)};
        else B = {int(t0[0] + (t1[0]-t0[0])*beta),
                  int(t0[1] + (t1[1]-t0[1])*beta),
                  int(t0[2] + (t1[2]-t0[2])*beta)};

        if (A[0]>B[0]) std::swap(A, B);
        for (int j=A[0]; j<=B[0]; j++) {
            float phi = B[0]==A[0] ? 1. : float((j-A[0])/float((B[0]-A[0])));
            vect P = {int(A[0] + (B[0]-A[0])*phi),
                      int(A[1] + (B[1]-A[1])*phi),
                      int(A[2] + (B[2]-A[2])*phi)};
            int idx = P[0]+P[1] * ui->drawArea->viewport()->width();
            if (zbuffer[idx]<P[2]) {
                zbuffer[idx] = P[2];
                ui->drawArea->scene()->addEllipse(P[0], P[1], 1, 1, pen);
            }
        }
    }
}


vectArray MainWindow::getCoordinates()
{
    vect p0 = {ui->x0->text().toInt(), ui->y0->text().toInt(), ui->z0->text().toInt(), 1};
    vect p1 = {ui->x1->text().toInt(), ui->y1->text().toInt(), ui->z1->text().toInt(), 1};
    vect p2 = {ui->x2->text().toInt(), ui->y2->text().toInt(), ui->z2->text().toInt(), 1};
    vectArray coordinates = {p0, p1, p2};

    return coordinates;
}

vectArray getCube(vect cam, vect c, int a)
{
    vectArray vertexes;

    //float r = -(1./float(cam[2]));

    for (int i = 0; i < 8; ++i)
    {
        vect p = {c[0] + a * ((i/4)%2 == 0 ? 1 : -1), c[1] + a * ((i/2)%2 == 0 ? 1 : -1), c[2] + a * (i%2 == 0 ? 1 : -1), 1};
        p[0] -= cam[0];
        p[1] -= cam[1];
        p[2] -= cam[2];

        float der = float(1 - (p[2] / float(cam[2])));
        p[0] = float(p[0]) / der;
        p[1] = float(p[1]) / der;
        p[2] = float(p[2]) / der;

        p[0] += cam[0];
        p[1] += cam[1];
        p[2] += cam[2];

        vertexes.push_back(p);
    }

    return vertexes;
}

void MainWindow::on_draw_clicked()
{
    if (ui->x0->text().isEmpty() && ui->y0->text().isEmpty() && ui->z0->text().isEmpty()
     && ui->x1->text().isEmpty() && ui->y1->text().isEmpty() && ui->z1->text().isEmpty()
     && ui->x2->text().isEmpty() && ui->y2->text().isEmpty() && ui->z2->text().isEmpty())
        return;

    ui->drawArea->scene()->clear();

    int w = ui->drawArea->viewport()->width(),
        h = ui->drawArea->viewport()->height();

    vectArray coordinates = getCoordinates();
    vect cam = {int(w/2), int(h/2), 400};

    //перспективное преобразование
    vect zbuffer(w * h, INT_MIN);
    //drawTriangle(coordinates[0], coordinates[1], coordinates[2], zbuffer);

    vectArray cube0 = getCube(cam, coordinates[0], 50);
    vectArray cube1 = getCube(cam, coordinates[1], 50);
    vectArray cube2 = getCube(cam, coordinates[2], 50);

    vect indexes = {0, 1, 2,
                    1, 2, 3,
                    1, 5, 3,
                    5, 3, 7,
                    4, 5, 6,
                    5, 6, 7,
                    0, 4, 2,
                    4, 2, 6,
                    4, 0, 1,
                    4, 1, 5,
                    6, 2, 3,
                    6, 3, 7};

    vect magenta = {1, 0, 1};
    vect cyan = {0, 1, 1};
    vect yellow = {1, 1, 0};

    for (int i = 0; i < indexes.size(); i=i+3)
    {
        drawTriangle(cube0[indexes[i]], cube0[indexes[i+1]], cube0[indexes[i+2]], zbuffer, magenta);
        drawTriangle(cube1[indexes[i]], cube1[indexes[i+1]], cube1[indexes[i+2]], zbuffer, cyan);
        drawTriangle(cube2[indexes[i]], cube2[indexes[i+1]], cube2[indexes[i+2]], zbuffer, yellow);
    }
}
