#pragma once
#include <vector>
#include <string>
#include "Types.h"
#include "Texture.h"
#include "Texture2D.h"
#include "TextureAtlas.h"
#include "ShaderCache.h"
#include "ShaderEffectCache.h"

namespace AssetManagement
{
	class ContentManager
	{
	public:
		ContentManager(bool forceRebuild = false);
		const TextureAtlas& spriteTextures() const { return this->spriteAtlas_; }
		const TextureAtlas& meshTextures() const { return this->meshAtlas_; }
		ShaderEffectCache& fx() { return this->fx_; }

	private:
		TextureAtlas spriteAtlas_;
		TextureAtlas meshAtlas_;
		ShaderEffectCache fx_;

		static TextureAtlas loadTextureAtlas(const char* moduleName, Graphics::Texture::Unit textureUnit, bool forceRebuild);
		static TextureAtlas buildTextureAtlas(const char* moduleName, Graphics::Texture::Unit textureUnit);
		static ShaderCache buildShaderCache();
		static ShaderEffectCache buildFxCache();
	};
}
