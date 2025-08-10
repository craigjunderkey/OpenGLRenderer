#pragma once
#include "TextureAtlas.h"

namespace AssetManagement
{
	class TextureUnpacker
	{
	public:
		static TextureAtlas importAtlas(const std::string& moduleName, Graphics::Texture::Unit textureUnit);
	};
}
