#include "Image.h"
#include "ErrorReporter.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace Common;

Image::Image(const char* filePath, Format format, bool flipVertically) : format(format)
{
	stbi_set_flip_vertically_on_load(flipVertically);
	
	i32 numChannels;
	this->data = stbi_load(filePath, &this->width, &this->height, &numChannels, (i32)format);

	ErrorReporter::panicElse(this->data != NULL,
		"Failed to load image " + std::string(filePath) + ".");
}

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
		stbi_image_free(this->data);
}