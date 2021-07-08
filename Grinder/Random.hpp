#pragma once
#ifndef _RANDOM_HPP_
#define _RANDOM_HPP_

#include <stdint.h>
#include <random>

inline int64_t randRange(int64_t beg, int64_t end)
{
	return beg + rand() % (end - beg);
}

#endif // _RANDOM_HPP_