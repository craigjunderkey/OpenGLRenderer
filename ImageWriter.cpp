#include "ImageWriter.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBI_MSC_SECURE_CRT
#include <stb_image_write.h>

using namespace Common;

void ImageWriter::write(const Image& image, const char* path)
{
	stbi_write_png(path, image.width, image.height, (i32)image.format, image.data, 0);
}