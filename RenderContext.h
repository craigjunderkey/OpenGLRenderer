#pragma once
#include <memory>
#include <vector>
#include "Window.h"
#include "Scene3D.h"
#include "SpriteBatch.h"
#include "VirtualScreen.h"
#include "Types.h"
#include "RenderScene.h"
#include "Color.h"
#include "TextureAtlas.h"
#include "ShaderEffect.h"
#include "ShaderEffectCache.h"
#include "ContentManager.h"

namespace Graphics
{
	class RenderContext
	{
	public:
		RenderContext(Window& window, AssetManagement::ContentManager& contentManager, u32 virtualWidth, u32 virtualHeight);
		~RenderContext();
		void render();
		RenderScene& getScene(u32 sceneIndex);
		void addScene3D(u32 maxObjects = Scene3D::DEFAULT_MAX_OBJECTS);
		void addSpriteBatch(const char* defaultEffect = "spritebatch", u32 maxObjects = SpriteBatch::DEFAULT_MAX_OBJECTS);
		void setBackgroundColor(Common::ColorRgba color);
		void setScreenEffect(const char* effect);

		static void initializeRenderer();

	private:
		Window& window_;
		AssetManagement::ContentManager& contentManager_;
		std::unique_ptr<VirtualScreen> virtualScreen_;
		std::vector<RenderScene*> renderSequence_;

		VirtualScreen* createVirtualScreen(Window& window, u32 virtualWidth, u32 virtualHeight);
		void render(RenderScene* scene);
	};
}
