#pragma once
#include "TextureAtlas.h"

namespace AssetManagement
{
	class TextureUnpacker
	{
	public:
		static TextureAtlas importAtlas(const char* moduleName, Graphics::Texture::Unit textureUnit);
	};
}
