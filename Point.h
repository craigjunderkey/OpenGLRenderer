#pragma once
#include "Types.h"
#include <iostream>

namespace Common
{
	struct Point
	{
		Point() : x(0), y(0) {}
		Point(u32 scalar) : x(scalar), y(scalar) {}
		Point(u32 x, u32 y) : x(x), y(y) {}

		Point operator+(const Point& other)
		{
			return Point(this->x + other.x, this->y + other.y);
		}

		Point operator-(const Point& other)
		{
			return Point(this->x - other.x, this->y - other.y);
		}

		friend std::ostream& operator<<(std::ostream& os, const Point& point);

		u32 x;
		u32 y;
	};

	inline std::ostream& operator<<(std::ostream& os, const Point& point)
	{
		os << "(" << point.x << ", " << point.y << ")";
		return os;
	}
}