#pragma once
#include "Types.h"
#include "Point.h"

namespace Common
{
	struct Rectangle
	{
		Rectangle() : position(Point()), size(Point()) {}
		Rectangle(Point size) : position(Point()), size(size) {}
		Rectangle(u32 width, u32 height) : position(Point()), size(Point(width, height)) {}
		Rectangle(Point position, Point size) : position(position), size(size) {}
		Rectangle(u32 x, u32 y, u32 width, u32 height) : position(Point(x, y)), size(Point(width, height)) {}

		Point position;
		Point size;
	};
}
