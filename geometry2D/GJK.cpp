#include "GJK.hpp"

Point GJK::support_func(const Point& d)
{
    double max_dot = dot_product(A[0], d);
    uint32_t max_id_point_A = 0;
    for (uint32_t i = 1; i < A.size(); i++)
    {
        if (dot_product(A[i], d) > max_dot)
        {
            max_dot = dot_product(A[i], d);
            max_id_point_A = i;
        }
    }
    
    Point d_minus = d * (-1);
    max_dot = dot_product(B[0], d_minus);
    uint32_t max_id_point_B = 0;
    for (uint32_t i = 1; i < B.size(); i++)
    {
        if (dot_product(B[i], d_minus) > max_dot)
        {
            max_dot = dot_product(B[i], d_minus);
            max_id_point_B = i;
        }
    }
    //std::cout << "POINT:" << A[max_id_point_A].x - B[max_id_point_B].x << " " << A[max_id_point_A].y - B[max_id_point_B].y << std::endl;
    return A[max_id_point_A] - B[max_id_point_B];
}

bool GJK::check_origin_in_triangle()
{
    Point AB = triangle[0] - triangle[1];
    Point CB = triangle[1] - triangle[2];
    Point AC = triangle[2] - triangle[0];
    
    if ((sgn(cross_product(AB, triangle[0])) == sgn(cross_product(CB, triangle[1]))) && (sgn(cross_product(AC, triangle[2])) == sgn(cross_product(CB, triangle[1]))))
    {
        return true;
    }
    return false;
}

bool GJK::GJK_initial()
{
    triangle[0] = A[0] - B[0]; //may use direction
    triangle[1] = support_func(triangle[0] * (-1));
    Point edge_triangle = triangle[0] - triangle[1];
    Point last_point = double_cross_product(edge_triangle, triangle[1], edge_triangle) * (-1);
    //std::cout << "last_one_go: " << last_point.x << " " << last_point.y << std::endl;
    triangle[2] = support_func(last_point);
    
    // std::cout << "TRIANGLE GO: ([" << std::endl;
    // for (const Point& p : triangle)
    // {
    //     std::cout << "[" << p.x << "," << p.y << "]," << std::endl;
    // }
    // std::cout << "])" << std::endl;

    if (check_origin_in_triangle())
    {
        return true;
    }
    return false;
}

double GJK::find_distance_to_origin(const Point& point_1, const Point& point_2)
{
    double A = point_1.y - point_2.y;
    double B = point_2.x - point_1.x;
    double C = -A * point_1.x - B * point_1.y;
    return std::abs(C) / std::sqrt(A*A + B*B);
}


double GJK::get_min_dist_and_change_triangle()
{
    std::vector<std::pair<std::pair<int, int>, double>> candidates;
    Point AB = triangle[0] - triangle[1];
    Point CB = triangle[1] - triangle[2];
    Point AC = triangle[2] - triangle[0];

    if (sgn(dot_product(AB, triangle[0])) != sgn(dot_product(AB, triangle[1])))
    {
        candidates.push_back(m_p(m_p(0, 1), find_distance_to_origin(triangle[0],triangle[1])));
    }
    if (sgn(dot_product(CB, triangle[1])) != sgn(dot_product(CB, triangle[2])))
    {
        candidates.push_back(m_p(m_p(1, 2), find_distance_to_origin(triangle[1],triangle[2])));
    }
    if (sgn(dot_product(AC, triangle[2])) != sgn(dot_product(AC, triangle[0])))
    {
        candidates.push_back(m_p(m_p(2, 0), find_distance_to_origin(triangle[2],triangle[0])));
    }

    if (candidates.size() == 0)
    {
        //TODO!!!!!!!!
        return 1e7;
    }

    double min_distance = candidates[0].second;
    uint32_t min_candidate_id = 0;
    for (uint32_t i = 0; i < candidates.size(); i++)
    {
        if (candidates[i].second < min_distance)
        {
            min_distance = candidates[i].second;
            min_candidate_id = i;
        }
    }
    
    std::vector<Point> triangle_copy = triangle;
    uint32_t i = candidates[min_candidate_id].first.first;
    uint32_t j = candidates[min_candidate_id].first.second;
    //std::cout << "i, j goooo"<< i << j <<std::endl;
    triangle[0] = triangle_copy[i];
    triangle[1] = triangle_copy[j];

    return min_distance;
}

bool GJK::GJK_continue()
{
    double cur_distance = get_min_dist_and_change_triangle();
    if (std::abs(cur_distance - distance) < eps)
    {
        //std::cout << "dist:" << cur_distance << " " << distance;
        return false;
    }
    distance = cur_distance;
    Point edge_triangle = triangle[0] - triangle[1];
    Point last_point = double_cross_product(edge_triangle, triangle[1], edge_triangle) * (-1);
    //std::cout << "last_one_go: " << last_point.x << " " << last_point.y << std::endl;
    triangle[2] = support_func(last_point);
    if (check_origin_in_triangle())
    {
        return true;
    }
    return GJK_continue();
}


bool GJK::check_intersection()
{
    if (GJK_initial())
    {
        return true;
    }
    return GJK_continue();
}