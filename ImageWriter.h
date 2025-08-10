#pragma once
#include "Image.h"

namespace Common
{
	class ImageWriter
	{
	public:
		static void write(const Image& image, const char* path);
	};
}
