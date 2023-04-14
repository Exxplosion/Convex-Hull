#pragma once
#include "consts.hpp"
#include "objects_2D.hpp"
#include <stack>
#include <algorithm>
#include <cmath>
#include <functional>

//Return the convex hull using the graham algorithm
std::vector<Point>* convex_hull_graham(std::vector<Point>* set_points);