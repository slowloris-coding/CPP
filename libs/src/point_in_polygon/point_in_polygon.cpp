#include "point_in_polygon.h"

#include <bits/stdc++.h>

using namespace std;


// [POINT]
Point_t::Point_t(){}
Point_t::Point_t(double x, double y): x(x), y(y) {}


// [POLYGON]
// CONSTRUCTORS:
Polygon_t::Polygon_t(): name(""){}
Polygon_t::Polygon_t(string n): name(n){}
Polygon_t::Polygon_t(const vector<Point> &pts, string n = ""): edges(pts), name(n){}

// PUBLIC:

bool Polygon_t::point_inside(const Point *point){
    // using Winding Number algorithm

    int wNo = 0;    // winding number

    // loop through polygon-edges
    for(auto pt1 = this->edges.begin(); pt1 != this->edges.end(); ++pt1){
        auto pt2 = ((pt1 + 1) == this->edges.end())? this->edges.begin() : (pt1 + 1);

        if (pt1->y <= point->y) {
            if (pt2->y > point->y) {
                if (((pt2->x - pt1->x) * (point->y - pt1->y) - (point->x - pt1->x) * (pt2->y - pt1->y)) > 0) {
                    ++wNo;
                }
            }
        }
        else {
            if (pt2->y <= point->y) {
                if (((pt2->x - pt1->x) * (point->y - pt1->y) - (point->x - pt1->x) * (pt2->y - pt1->y)) < 0) {
                    --wNo;
                }
            }
        }
    }

    return (wNo != 0);
}
bool Polygon_t::point_inside(const Point &point){
    // using Winding Number algorithm

    int wNo = 0;    // winding number

    // loop through polygon-edges
    for(auto pt1 = this->edges.begin(); pt1 != this->edges.end(); ++pt1){
        auto pt2 = ((pt1 + 1) == this->edges.end())? this->edges.begin() : (pt1 + 1);

        if (pt1->y <= point.y) {
            if (pt2->y > point.y) {
                if (((pt2->x - pt1->x) * (point.y - pt1->y) - (point.x - pt1->x) * (pt2->y - pt1->y)) > 0) {
                    ++wNo;
                }
            }
        }
        else {
            if (pt2->y <= point.y) {
                if (((pt2->x - pt1->x) * (point.y - pt1->y) - (point.x - pt1->x) * (pt2->y - pt1->y)) < 0) {
                    --wNo;
                }
            }
        }
    }

    return (wNo != 0);
}

//////////////////////////////////////////////////

