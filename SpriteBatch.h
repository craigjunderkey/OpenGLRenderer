#pragma once
#include <vector>
#include "Types.h"
#include "RenderScene.h"
#include "ShaderProgram.h"
#include "InstancedMesh.h"
#include "Rectangle.h"
#include "TextureAtlas.h"
#include "Texture2D.h"
#include "ShaderEffect.h"
#include "ShaderEffectCache.h"
#include "Color.h"
#include "UniformCommandBlock.h"
#include "ErrorReporter.h"
#include "SpriteDrawInfo.h"

namespace Graphics
{
	class SpriteBatch : public RenderScene
	{
	public:
		static constexpr size_t DEFAULT_MAX_OBJECTS = 16384; // 2^14; significant? I think not !

		SpriteBatch(const AssetManagement::TextureAtlas& textureAtlas, AssetManagement::ShaderEffectCache& effectCache, const std::string& defaultEffect, mat4 projectionTransform, size_t maxObjects);
		~SpriteBatch();
		void setZoomLevel(u8 zoomLevel);

		void draw(const Texture2D& texture, vec2 position, SpriteDrawInfo info = SpriteDrawInfo());
		void draw(const std::string& textureName, vec2 position, SpriteDrawInfo info = SpriteDrawInfo());

		void render() override;
		void setView(mat4 viewTransform) override;
		void setProjection(mat4& projectionTransform) override;

	private:
		struct InstancedRenderObject
		{
			InstancedRenderObject(mat4 transform, vec4 uvCoords, u8 flags, Common::ColorRgb tint)
				: transform(transform),
				uvCoords(uvCoords),
				tintAndFlags(
					(u32)(tint.r)   << 24 |
					(u32)(tint.g) << 16 |
					(u32)(tint.b) << 8 |
					(u32)(flags)
				)
			{}
			
			InstancedRenderObject()
				: transform(mat4(0.0f)), uvCoords(vec4(0.0f)), tintAndFlags(0)
			{}

			mat4 transform;
			vec4 uvCoords;
			u32 tintAndFlags;
		};

		struct EffectInfo
		{
			EffectInfo() {}
			EffectInfo(i32 effect, UniformCommandBlock* properties)
				: effect(effect), properties(std::move(properties)) {}

			i32 effect = AssetManagement::ShaderEffectCache::NO_EFFECT;
			UniformCommandBlock* properties = nullptr;
		};

		struct UniformCache
		{
		public:
			enum class Uniform
			{
				TexUnit = 0x01,
				Projection = 0x02,
				View = 0x04
			};

			void setUpdated(Uniform uniform)
			{
				this->flags |= (u8)uniform;
			}

			void setOutdated(Uniform uniform)
			{
				this->flags &= ~(u8)uniform;
			}

			bool isOutdated(Uniform uniform) const
			{
				return (this->flags & (u8)uniform) == 0;
			}

		private:
			u8 flags = 0x0;
		};

		mat4 view_;
		mat4 zoom_;
		mat4 projection_;
		std::vector<InstancedRenderObject> objects_;
		std::vector<EffectInfo> effectInfo_;
		std::vector<UniformCache> effectUniformCaches_;
		AssetManagement::ShaderEffectCache& effectCache_;
		i32 defaultEffectId_;
		InstancedMesh mesh_;
		const AssetManagement::TextureAtlas& textureAtlas_;
		const Texture& textureAtlasSource_;
		size_t maxObjects_;

		InstancedMesh createMesh();
		void bindAndUpdateEffect(EffectInfo info, bool onlyPropertiesChanged);
		void bufferAndDraw(u32 offsetIndex, u32 batchSize);
		i32 effectFromCstr(const char* effect);
		void storeDrawCall(const Texture2D& texture, mat4 model, EffectInfo effectInfo, u8 drawFlags, Common::ColorRgb tint);
		mat4 createModel(const Texture2D& texture, vec2 position, SpriteDrawInfo info);
	};
}