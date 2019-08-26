#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include <iostream>
#include <vector>

typedef std::pair<double, double> Point;
typedef std::pair<Point, Point> Line;
typedef std::vector<Line> Lines;
typedef int OutCode;

extern double X, Y, W, H;
extern Lines LINES;
extern Lines LINES_CLIPPED;
extern const int N;
extern const int INSIDE, LEFT, RIGHT, BOTTOM, TOP;

int randint(int, int);
Point getRandomPoint(int, int);
Line getRandomLine(int, int);
Lines getRandomLines(int, int, int);
OutCode ComputeOutCode(double, double);
Line CohenSutherland(Line);
Lines getClippedLines(Lines);


#endif // CALCULATIONS_H
