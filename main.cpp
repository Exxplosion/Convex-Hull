#include "geometry2D/consts.hpp"
#include "geometry2D/objects_2D.hpp"
#include "geometry2D/graham.hpp"
#include "parse_read/read_points.hpp"
#include "parse_read/parse_arguments.hpp"
#include "geometry2D/GJK.hpp"
#include <iostream>


int main(int argc, char** argv)
{
    std::string filename_A;
    std::string filename_B;
    {
        auto err_info = parse_arguments(argc, argv, filename_A, filename_B);
        if(int(err_info) < 0)
        {
            std::cout << "Error parsing cmd line arg: " << get_error_name(err_info) << std::endl;
            return int(err_info);
        }
    }

    uint32_t count_points_A = 0;
    uint32_t count_points_B = 0;
    {
        auto err_info = check_file(filename_A, count_points_A);
        if (int(err_info) != 0)
        {
            std::cout << "Error checking file A:  " << get_error_name(err_info) << std::endl;
            return int(err_info);
        }
    }
    {
        auto err_info = check_file(filename_B, count_points_B);
        if (int(err_info) != 0)
        {
            std::cout << "Error checking file B:  " << get_error_name(err_info) << std::endl;
            return int(err_info);
        }
    }


    std::vector<Point>* A_points = new (std::nothrow) std::vector<Point>(count_points_A);
    if (!A_points)
    {
        std::cout << "Allocate memory for A fail" << std::endl;
        return 1;
    }

    {
        auto err_info = read_points(filename_A, count_points_A, A_points);
        if (int(err_info) != 0)
        {
            std::cout << "Error read file A: " << get_error_name(err_info) << std::endl;
            return int(err_info);
        }
    }
   
    Polygon A(convex_hull_graham(A_points));
    delete A_points;

    std::vector<Point>* B_points = new (std::nothrow) std::vector<Point>(count_points_B);
    if (!B_points)
    {
        std::cout << "Allocate memory for B fail" << std::endl;
        return 1;
    }

    {
        auto err_info = read_points(filename_B, count_points_B, B_points);
        if (int(err_info) != 0)
        {
            std::cout << "Error read file B: " << get_error_name(err_info) << std::endl;
            return int(err_info);
        }
    }

    Polygon B(convex_hull_graham(B_points));
    delete B_points;

    GJK aux(A, B);
    Point tmp(0, -1);

    if (aux.check_intersection())
    {
        std::cout << "YES" << std::endl;
    }
    else
    {
        std::cout << "NO" << std::endl;
    }

    return 0;
}