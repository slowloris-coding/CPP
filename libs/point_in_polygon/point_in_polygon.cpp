#include "point_in_polygon.h"

#include <bits/stdc++.h>

#include "./point/point.h"
#include "./polygon/polygon.h"

using namespace std;

bool point_in_polygon(double x, double y, vector<double[2]> poly){
    Polygon polygon(poly, "");
    return polygon.point_inside(new Point(x,y));
}
