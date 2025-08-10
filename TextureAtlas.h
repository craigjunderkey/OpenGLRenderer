#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "Texture.h"
#include "Texture2D.h"

namespace AssetManagement
{
	class TextureAtlas
	{
		friend class TexturePacker;
		friend class TextureUnpacker;

	public:
		TextureAtlas(const char* fileName, Graphics::Texture::Unit textureUnit, u32 numTextures);
		TextureAtlas(Graphics::Texture&& source, u32 numTextures);
		TextureAtlas(TextureAtlas&& other) noexcept;
		const Graphics::Texture& source() const { return this->source_; }
		const Graphics::Texture2D& get(std::string textureName) const;

	private:
		Graphics::Texture source_;
		std::vector<Graphics::Texture2D> textures_;
		std::unordered_map<std::string, u32> textureMap_;

		void addTexture(std::string textureName, Graphics::Texture2D texture);
	};
}
