#include "point.h"

#include <bits/stdc++.h>

using namespace std;

Point_t::Point_t(double x, double y): x(x), y(y) {}
Point_t::Point_t(vector<double> pt): x(pt[0]), y(pt[1]) {}
Point_t::Point_t(double pt[2]): x(pt[0]), y(pt[1]) {}
