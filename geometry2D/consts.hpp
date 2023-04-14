#pragma once
#include<cstdint>

//some constants that i use (meant to use)
//thought there be more....
static const uint32_t MAX_COUNT_POINTS =  100'000;

typedef double point_type;

static const point_type eps = 1e-6;

#define m_p std::make_pair