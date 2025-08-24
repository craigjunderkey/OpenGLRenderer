#pragma once
#include "Image.h"
#include "Path.h"

namespace Common
{
	class ImageReader
	{
	public:
		ImageReader() = delete;
		static Image read(const Path& file, Image::Format colorFormat,	bool flipVertically);

	private:
		static Image readPng(const Path& file, Image::Format colorFormat, bool flipVertically);
	};
}
