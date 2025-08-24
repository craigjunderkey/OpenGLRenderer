#include "ImageReader.h"
#include "ErrorReporter.h"
#include "Types.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace Common;

Image ImageReader::read(const Path& file, Image::Format colorFormat, bool flipVertically)
{
	if (file.extensionMatches("png"))
	{
		return readPng(file, colorFormat, flipVertically);
	}
	else
	{
		ErrorReporter::panic(file.path() + " does not have a valid extension.");
	}
}

Image ImageReader::readPng(const Path& file, Image::Format colorFormat, bool flipVertically)
{
	stbi_set_flip_vertically_on_load(flipVertically);

	i32 numChannels, width, height;
	u8* data = stbi_load(file.path().data(), &width, &height, &numChannels, (i32)colorFormat);

	ErrorReporter::panicElse(data != NULL,
		"Failed to load image " + file.path() + ".");

	return Image(data, width, height, colorFormat);
}