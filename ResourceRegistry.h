#pragma once
#include "Types.h"
#include "ResourceCache.h"
#include "StringId.h"
#include "Shader.h"
#include "ShaderEffect.h"
#include "TextureAtlas.h"
#include "Texture.h"

namespace Resources
{
	class ResourceRegistry
	{
	public:
		struct RegistryDescription
		{
			u32 numShaders;
			u32 numFx;
			u32 numTextures;
			u32 numAtlases;
		};
		
		ResourceRegistry(RegistryDescription description)
			: shaders_(description.numShaders),
			fx_(description.numFx),
			textures_(description.numTextures),
			atlases_(description.numAtlases)
		{
		}

		const ResourceCache<Graphics::Shader>& shaders() { return this->shaders_; }
		const ResourceCache<Graphics::ShaderEffect>& fx() { return this->fx_; }
		const ResourceCache<Graphics::Texture>& textures() { return this->textures_; }
		const ResourceCache<AssetManagement::TextureAtlas>& atlases() { return this->atlases_; }

	private:
		ResourceCache<Graphics::Shader> shaders_;
		ResourceCache<Graphics::ShaderEffect> fx_;
		ResourceCache<Graphics::Texture> textures_;
		ResourceCache<AssetManagement::TextureAtlas> atlases_;
	}; 
}
