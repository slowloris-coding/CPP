//
// Created by loris on 06.12.2022.
//

#ifndef POINT_IN_POLYGON_POLYGON_H
#define POINT_IN_POLYGON_POLYGON_H

#include <bits/stdc++.h>

#include "../point/point.h"

using namespace std;

typedef class Polygon_t {
private:
public:
    string name;
    vector<Point> edges;

    Polygon_t();
    explicit Polygon_t(string n);
    Polygon_t(const vector<Point> &pts, string n);
    Polygon_t(const vector<double[2]> &pts, string n);
    Polygon_t(const vector<vector<double>> &pts, string n);

    bool point_inside(const Point *point);
    bool point_inside(const Point &point);

} Polygon;

#endif //POINT_IN_POLYGON_POLYGON_H
