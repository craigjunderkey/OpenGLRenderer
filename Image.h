#pragma once
#include "GlImageFormat.h"
#include "Types.h"

namespace Common
{
	struct Image
	{
		enum Format
		{
			Rgb = 3,
			Rgba = 4
		};

		Image(u8* data, i32 width, i32 height, Format format);
		Image(Image&& other) noexcept;
		Image() {}

		~Image();
		
		u8* data = nullptr;
		i32 width = 0;
		i32 height = 0;
		Format format = Format::Rgba;
	};
}
