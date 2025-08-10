#include "ImageBuilder.h"

using namespace Common;

ImageBuilder::ImageBuilder(u32 width, u32 height, Image::Format format)
	: width_(width), height_(height), format_(format)
{
	this->data_ = new u8[width * height * (i32)format]{ 0 };
}

ImageBuilder::~ImageBuilder()
{
	if (this->data_ != nullptr)
		delete[] this->data_;
}

Image ImageBuilder::build()
{
	Image image = Image(this->data_, this->width_, this->height_, this->format_);
	this->data_ = nullptr;
	return image;
}

void ImageBuilder::writePixel(Point pixel, u8 r, u8 g, u8 b, u8 a)
{
	u8 color[] = {r, g, b, a};
	std::memcpy(getPixel(pixel), color, 4);
}

void ImageBuilder::writePixel(Point pixel, u8 r, u8 g, u8 b)
{
	u8 color[] = { r, g, b };
	std::memcpy(getPixel(pixel), color, 3);
}

inline u8* ImageBuilder::getPixel(Point pixel)
{
	return &this->data_[(pixel.y * this->width_ + pixel.x) * (i32)this->format_];
}

inline const u8* ImageBuilder::getPixel(const u8* data, Point pixel, u32 dataWidth)
{
	return &data[(pixel.y * dataWidth + pixel.x) * (i32)this->format_];
}

void ImageBuilder::writeRegion(Rectangle region, const u8* refData)
{
	assert(region.position.x + region.size.x <= this->width_
		&& region.position.y + region.size.y <= this->height_);

	for (i32 y = 0; y < region.size.y; y++)
	{
		u8* destStart = getPixel(Point(region.position.x, region.position.y + y));
		const u8* srcStart = getPixel(refData, Point(0, y), region.size.x);
		std::memcpy(destStart, srcStart, (size_t)region.size.x * (i32)this->format_);
	}
}

Image ImageBuilder::copyImage(const Image& input, bool flippedVertically)
{
	ImageBuilder builder = ImageBuilder(input.width, input.height, input.format);

	if (!flippedVertically)
	{
		std::memcpy(builder.data_, input.data, (size_t)input.width * (size_t)input.height * (size_t)input.format);
	}
	else
	{
		for (i32 y = 0; y < input.height; y++)
		{
			u8* destStart = builder.getPixel(Point(0, input.height - 1 - y));
			const u8* srcStart = builder.getPixel(input.data, Point(0, y), input.width);
			std::memcpy(destStart, srcStart, (size_t)input.width * (i32)input.format);
		}
	}

	return builder.build();
}