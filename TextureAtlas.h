#pragma once
#include "Texture.h"
#include "Texture2D.h"
#include "Resource.h"
#include "StringIdTable.h"

namespace AssetManagement
{
	class TextureAtlas : Resources::Resource
	{
		friend class TexturePacker;
		friend class TextureUnpacker;

	public:
		TextureAtlas(StringId source, u32 capacity);
		
		const Graphics::Texture& source() const { return *this->source_; }
		const Graphics::Texture2D& get(StringId textureId) const;

		void initResource() override {};

	private:
		Graphics::Texture* source_;
		Common::StringIdTable<Graphics::Texture2D> textures_;

		void addTexture(StringId textureId, Graphics::Texture2D texture);
	};
}
