#pragma once
#include "objects_2D.hpp"


inline int sgn(const double& x)
{
    if (x > eps)
    {
        return 1;
    }
    return -1;
}

//Class with 2 convex hull (polygon A, B)
//if origin in triangle, there is intersaction 
class GJK
{
public:
    const Polygon A;
    const Polygon B;
    std::vector<Point> triangle;
    Point direction;
    double distance;

    GJK(Polygon &A_o, Polygon& B_o):
    A(A_o), B(B_o) 
    {
        direction = {-1.0, 1.0}; //will not use
        triangle.resize(3);
        distance = 1e6;
    }

    Point support_func(const Point& d);

    bool check_origin_in_triangle();

    bool GJK_initial();

    double find_distance_to_origin(const Point& point_1, const Point& point_2);

    double get_min_dist_and_change_triangle();

    bool GJK_continue();

    bool check_intersection();
};