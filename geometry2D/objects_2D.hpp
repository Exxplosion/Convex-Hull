#pragma once
#include "consts.hpp"
#include <iostream>
#include<vector>
#include<cmath>

class Point
{
public:
    point_type x;
    point_type y;

    Point() = default;
    Point(point_type x_other, point_type y_other) :
    x(x_other), y(y_other) {}
    Point(const Point& other):
    x(other.x), y(other.y) {}

    inline point_type lenght() const
    {
        return std::sqrt(x * x + y * y);
    }

    Point operator-(const Point& other) const
    {
        return Point(this->x - other.x, this->y - other.y);
    }

    Point operator+(const Point& other) const
    {
        return Point(this->x + other.x, this->y + other.y);
    }

    Point operator*(const double& m) const
    {
        return Point(m*this->x, m*this->y);
    }

    Point operator*(const int& m) const
    {
        return Point(m*this->x, m*this->y);
    }

    Point operator=(const Point& other)
    {
        this->x = other.x;
        this->y = other.y;
        return *this;
    }
};

inline double cross_product(const Point& a, const Point& b)
{
    return a.x * b.y - b.x * a.y;
}

inline double dot_product(const Point& a, const Point& b)
{
    return a.x * b.x + a.y * b.y;
}

inline double cross_product(const Point& O, const Point& A, const Point& B) 
{
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

inline Point double_cross_product(const Point& a, const Point& b, const Point& c)
{
    return b * dot_product(a, c) - c * dot_product(a, b);
}

class Polygon
{
public:
    std::vector<Point>* points;
    Polygon(std::vector<Point> *cur_pointer) :
    points(cur_pointer) {} //NOTE: check it

    uint32_t size() const
    {
        return points->size();
    }

    Point operator[](uint32_t i) const
    {
        return (*points)[i];
    }


    void print() const
    {
        std::cout << "([" << std::endl;
        for (const Point& p : (*points))
        {
            std::cout << "[" << p.x << "," << p.y << "]," << std::endl;
        }
        std::cout << "])" << std::endl;
    }
};