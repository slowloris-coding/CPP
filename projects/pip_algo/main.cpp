#include <bits/stdc++.h>
#include "libs/point_in_polygon/point_in_polygon.h"

int main() {
    try {
        std::system("cls");

        vector<Point> poly{Point(0,0),Point(0,5),Point(5,5),Point(5,0)};
        Polygon polygon(poly, "a");

        if (polygon.point_inside(new Point(6,1.5))) {
            cout << "\x1b[38;2;0;255;0m[+]  \x1b[0mIN Polygon" << endl;
        } else {
            cout << "\x1b[38;2;255;0;0m[-]  \x1b[0mNOT in Polygon" << endl;
        }
    }
    catch(exception &e){
        cerr << e.what() << endl;
    }
    return 0;
}
