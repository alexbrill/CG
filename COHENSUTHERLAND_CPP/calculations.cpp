#include "calculations.h"

double X = 0, Y = 0, W = 0, H = 0;
Lines LINES;
Lines LINES_CLIPPED;

const int N = 20;
const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000


int randint(int b, int a = 0) {
    return rand() % b + a;
}

Point getRandomPoint(int maxW, int maxH) {
    return std::make_pair(randint(maxW), randint(maxH));
}

Line getRandomLine(int maxW, int maxH) {
    return std::make_pair(getRandomPoint(maxW, maxH),
                                getRandomPoint(maxW, maxH));
}

Lines getRandomLines(int n, int maxW, int maxH) {
    Lines lines;

    for (int i = 0; i < n; ++i)
        lines.push_back(getRandomLine(maxW, maxH));

    return lines;
}

OutCode ComputeOutCode(double x, double y)
{
    OutCode code;

    code = INSIDE;          // initialised as being inside of [[clip window]]

    if (x < X)           // to the left of clip window
        code |= LEFT;
    else if (x > X + W)      // to the right of clip window
        code |= RIGHT;
    if (y < Y)           // below the clip window
        code |= TOP;
    else if (y > Y + H)      // above the clip window
        code |= BOTTOM;

    return code;
}

Line CohenSutherland(Line line)
{
    double x0 = line.first.first, y0 = line.first.second,
        x1 = line.second.first, y1 = line.second.second;

    OutCode outcode0 = ComputeOutCode(x0, y0);
    OutCode outcode1 = ComputeOutCode(x1, y1);
    bool accept = false;

    while (true)
    {
        if (!(outcode0 | outcode1))
        {
            accept = true;
            break;
        }
        else if (outcode0 & outcode1)
            break;
        else
        {
            double x = 0, y = 0;

            OutCode outcodeOut = outcode0 ? outcode0 : outcode1;

            if (outcodeOut & BOTTOM)
            {
                x = x0 + (x1 - x0) * (Y + H - y0) / (y1 - y0);
                y = Y + H;
            }
            else if (outcodeOut & TOP)
            {
                x = x0 + (x1 - x0) * (Y - y0) / (y1 - y0);
                y = Y;
            }
            else if (outcodeOut & RIGHT)
            {
                y = y0 + (y1 - y0) * (X + W - x0) / (x1 - x0);
                x = X + W;
            }
            else if (outcodeOut & LEFT)
            {
                y = y0 + (y1 - y0) * (X - x0) / (x1 - x0);
                x = X;
            }

            if (outcodeOut == outcode0)
            {
                x0 = x;
                y0 = y;
                outcode0 = ComputeOutCode(x0, y0);
            }
            else
            {
                x1 = x;
                y1 = y;
                outcode1 = ComputeOutCode(x1, y1);
            }
        }
    }

    if (accept)
        return Line(Point(x0, y0), Point(x1, y1));

    return Line(Point(0, 0), Point(0, 0));
}

Lines getClippedLines(Lines lines)
{
    Lines clippedLines;

    for (Line line : lines)
        clippedLines.push_back(CohenSutherland(CohenSutherland(line)));

    return clippedLines;
}
