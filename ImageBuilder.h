#pragma once
#include "Image.h"
#include "Point.h"
#include "Rectangle.h"
#include "Types.h"

namespace Common
{
	class ImageBuilder
	{
	public:
		ImageBuilder(u32 width, u32 height, Image::Format format);
		~ImageBuilder();

		void writePixel(Point pixel, u8 r, u8 g, u8 b, u8 a);
		void writePixel(Point pixel, u8 r, u8 g, u8 b);
		void writeRegion(Rectangle region, const u8* refData);
		Image build();

		static Image copyImage(const Image& input, bool flippedVertically);

	private:
		u8* data_;
		Image::Format format_;
		u32 width_;
		u32 height_;

		inline u8* getPixel(Point pixel);
		inline const u8* getPixel(const u8* data, Point pixel, u32 dataWidth);
	};
}