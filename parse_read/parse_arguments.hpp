#pragma once
#include <sstream>
#include <cstdio> // <stdio.h>

enum class ParseErrors
{
    INSUFFICIENT_ARGUMENTS = -3,
    TO_MUCH_ARGUMENTS = -200,
    NOT_A_NUMBER = -100,
    SUCCESS = 0
};

ParseErrors parse_arguments(int argc, char **argv, std::string &filename_A, std::string &filename_B);

std::string get_error_name(ParseErrors err_info);