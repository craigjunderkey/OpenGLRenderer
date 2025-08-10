#include "TextureAtlas.h"
#include "ErrorReporter.h"

using namespace Graphics;
using namespace Common;
using namespace AssetManagement;

TextureAtlas::TextureAtlas(const char* fileName, Texture::Unit textureUnit, u32 numTextures)
	: source_(Texture::fromFile(fileName, textureUnit))
{
	this->textures_.reserve(numTextures);
	this->textureMap_.reserve(numTextures);
}

TextureAtlas::TextureAtlas(Graphics::Texture&& source, u32 numTextures)
	: source_(std::move(source))
{
	this->textures_.reserve(numTextures);
	this->textureMap_.reserve(numTextures);
}

TextureAtlas::TextureAtlas(TextureAtlas&& other) noexcept
	: source_(std::move(other.source_)),
	textures_(std::move(other.textures_)),
	textureMap_(std::move(other.textureMap_))
{
}

const Texture2D& TextureAtlas::get(std::string textureName) const
{
	auto it = this->textureMap_.find(textureName);

	if (it != this->textureMap_.end())
	{
		return this->textures_[it->second];
	}
	else
	{
		ErrorReporter::panic("Tried to retrieve but couldn't find " + textureName + ".");
	}
}

void TextureAtlas::addTexture(std::string textureName, Texture2D texture)
{
	u32 textureIndex = this->textures_.size();
	this->textures_.push_back(std::move(texture));
	this->textureMap_.insert({std::move(textureName), textureIndex});
}
