#pragma once
#include <cstdio>
#include <fstream>
#include <string>
#include "../geometry2D/objects_2D.hpp"


/* double* read_points(const std::string &filename)
{
    FILE *fileptr = fopen(filename.c_str(), "r");
} */

//-1 - fail, 1 - ok, can be upgrade optional
enum class ReadErrors
{
    CAN_NOT_OPEN_FILE = -101,
    PARSING_FILE_ERROR = -102,
    PARSING_FILE_PROCESS_ERROR = -105,
    FILE_HAVE_ODD_COUNTS_POINTS = -103,
    SUCCESS = 0
};

ReadErrors check_file(const std::string &filename,  uint32_t &n);
ReadErrors read_points(const std::string &filename, const uint32_t& count_points, std::vector<Point>* points);
std::string get_error_name(ReadErrors err_info);