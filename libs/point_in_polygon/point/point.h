//
// Created by loris on 06.12.2022.
//

#ifndef POINT_IN_POLYGON_POINT_H
#define POINT_IN_POLYGON_POINT_H

#include <bits/stdc++.h>

using namespace std;

typedef struct Point_t {
    double x;
    double y;

    Point_t() = default;
    Point_t(double x, double y);
    Point_t(vector<double> pt);
    Point_t(double pt[2]);
} Point;

#endif //POINT_IN_POLYGON_POINT_H
