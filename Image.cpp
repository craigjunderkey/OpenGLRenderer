#include "Image.h"
#include "ErrorReporter.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace Common;

Image::Image(u8* data, i32 width, i32 height, Format format)
	: data(data), width(width), height(height), format(format)
{
}

Image::Image(Image&& other) noexcept
	: data(other.data), width(other.width), height(other.height), format(other.format)
{
	other.data = nullptr;
	other.width = 0;
	other.height = 0;
}

Image::~Image()
{
	if (this->data != nullptr)
		delete this->data;
}