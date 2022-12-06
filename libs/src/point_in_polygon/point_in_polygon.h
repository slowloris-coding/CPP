//
// Created by loris on 06.12.2022.
//

#ifndef POINT_IN_POLYGON_H
#define POINT_IN_POLYGON_H

#include <bits/stdc++.h>

using namespace std;

typedef class Point_t {
public:
    double x;
    double y;

    Point_t();
    Point_t(double x, double y);
} Point;

typedef class Polygon_t {
private:
public:
    string name;
    vector<Point> edges;

    Polygon_t();
    explicit Polygon_t(string n);
    Polygon_t(const vector<Point> &pts, string n);

    bool point_inside(const Point *point);
    bool point_inside(const Point &point);

} Polygon;

#endif //PIP_ALGO_POINT_IN_POLYGON_H
