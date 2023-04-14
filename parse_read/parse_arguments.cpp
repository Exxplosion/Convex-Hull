#include "parse_arguments.hpp"

[[nodiscard]] ParseErrors parse_arguments(int argc, char **argv, std::string &filename_A, std::string &filename_B)
{
    if (argc < 3)
    {
        return ParseErrors::INSUFFICIENT_ARGUMENTS;
    }
    if (argc > 3)
    {
        return ParseErrors::TO_MUCH_ARGUMENTS;
    }
    filename_A = argv[1];
    filename_B = argv[2];

    return ParseErrors::SUCCESS;
}

std::string get_error_name(ParseErrors err_info)
{
    switch (err_info)
    {
    case ParseErrors::INSUFFICIENT_ARGUMENTS:
        return "Not enough arguments";
    case ParseErrors::TO_MUCH_ARGUMENTS:
        return "To much arguments";
    case ParseErrors::NOT_A_NUMBER:
        return "Can not convert input argument to double";
    case ParseErrors::SUCCESS:
        return "No error";
    default:
        return "Uknown error";
    }
}