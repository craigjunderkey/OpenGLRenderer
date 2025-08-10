#include <GL/glew.h>
#include <string>
#include "Texture.h"
#include "ErrorReporter.h"
#include "Image.h"

using namespace Graphics;
using namespace Common;

Texture::Texture(const u8* imageData, u32 imageWidth, u32 imageHeight, GlImageFormat format, Unit textureIndex)
	: size_(Point(imageWidth, imageHeight)), unit_(textureIndex)
{
	activateUnit();

	// generate texture
	glGenTextures(1, &this->id_);
	glBindTexture(GL_TEXTURE_2D, this->id_);

	// send image data to GPU
	glTexImage2D(
		GL_TEXTURE_2D, 0, (GLenum)format,
		imageWidth, imageHeight, 0,
		(GLenum)format, GL_UNSIGNED_BYTE, imageData
	);

	// select nearest neighbor filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

Texture::Texture(Texture&& other) noexcept
	: id_(other.id_), size_(other.size_), unit_(other.unit_)
{
	other.id_ = NO_TEXTURE;
}

Texture::~Texture()
{
	if (this->id_ != NO_TEXTURE)
	{
		activateUnit();
		glDeleteTextures(1, &this->id_);
	}
}

void Texture::bind() const
{
	assert(this->id_ != NO_TEXTURE);
	activateUnit();
	glBindTexture(GL_TEXTURE_2D, this->id_);
}

void Texture::activateUnit() const
{
	glActiveTexture(GL_TEXTURE0 + (u32)this->unit_);
}

Texture Texture::fromFile(const char* filePath, Unit textureIndex)
{
	Image image = Image(filePath, Image::Format::Rgba, true);
	Texture texture = Texture(image.data, image.width, image.height, GlImageFormat::Rgba, textureIndex);
	return texture;
}