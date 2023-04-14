#include "graham.hpp"

std::vector<Point>* convex_hull_graham(std::vector<Point>* set_points)
{   
    Point p0 = (* set_points)[0];

    for (const Point& p : (*set_points))
    {
        if (p.x < p0.x || (p.x == p0.x && p.y < p0.y))
            p0 = p;
    }

    std::sort((*set_points).begin(), (*set_points).end(), [&p0](const Point& a, const Point& b) {
            double angle_a = std::atan2(a.y - p0.y, a.x - p0.x);
            double angle_b = std::atan2(b.y - p0.y, b.x - p0.x);
            return angle_a < angle_b;
        });//may do it differently!! (with cross_product)

    std::vector<Point>* hull = new std::vector<Point>();
    hull->reserve((*set_points).size()); 
    //TODO: check reserve
    (*hull).push_back(p0);

    for (const Point& p : (*set_points)) 
    {
        while ((*hull).size() > 1) {
            Point new_vector = p - (*hull).back();
            Point last_vector = (*hull).back() - (*hull)[(*hull).size() - 2];
            if (cross_product(new_vector, last_vector) > 0.0)
                (*hull).pop_back();
            else
                break;
        }
        (*hull).push_back(p);
    }
    (*hull).shrink_to_fit(); //capacity = size;
    return hull;
}