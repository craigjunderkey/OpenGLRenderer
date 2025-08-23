#pragma once
#include <GL/glew.h>
#include "Types.h"
#include "Point.h"
#include "GlImageFormat.h"
#include "Path.h"
#include "Resource.h"

namespace Graphics
{
	class Texture : public Resources::Resource
	{
	public:
		enum Unit
		{
			SpriteTextureAtlas = 0,
			MeshTextureAtlas = 1,
			Attachment = 2
		};

		Texture(const u8* imageData, u32 imageWidth, u32 imageHeight, GlImageFormat format, Unit textureUnit);
		Texture(Texture&& other) noexcept;
		~Texture();
		void bind() const;
		Common::Point size() const { return this->size_; }
		u32 id() const { return this->id_; }
		u32 unit() const { return this->unit_; }

		static Texture fromFile(const char* filePath, Unit textureIndex);
		static Texture fromFile(const Common::Path& filePath, Unit textureIndex);

		void initResource() override {}

	private:
		u32 id_;
		Common::Point size_;
		Unit unit_;

		static const u32 NO_TEXTURE = 0;
		
		void activateUnit() const;
	};
}
