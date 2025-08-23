#pragma once
#include "ResourceCache.h"
#include "StringId.h"
#include "Shader.h"
#include "ShaderEffect.h"
#include "TextureAtlas.h"

namespace Resources
{
	class ResourceRegistry
	{
	public:
		ResourceRegistry(u32 numShaders, u32 numFx, u32 numSpriteTextures, u32 numMeshTextures)
			: shaders_(numShaders),
			fx_(numFx),
			spriteTextures_()
		{
		}

		ResourceCache<Graphics::Shader>& shaders() { return this->shaders_; }
		ResourceCache<Graphics::ShaderEffect>& fx() { return this->fx_; }

	private:
		ResourceCache<Graphics::Shader> shaders_;
		ResourceCache<Graphics::ShaderEffect> fx_;
		AssetManagement::TextureAtlas spriteTextures_;
		AssetManagement::TextureAtlas meshTextures_;
	}; 
}
