#pragma once
#include "Types.h"
#include "Window.h"
#include "FrameBufferObject.h"
#include "RenderBufferObject.h"
#include "ShaderProgram.h"
#include "Mesh.h"
#include "Color.h"
#include "ShaderEffect.h"
#include "ShaderEffectCache.h"

namespace Graphics
{
	class VirtualScreen
	{
	public:
		VirtualScreen(const Window& parentWindow, AssetManagement::ShaderEffectCache& effectCache, const char* defaultEffect, u32 width, u32 height);
		~VirtualScreen();
		void begin();
		void end();
		void setBackgroundColor(Common::ColorRgba color);
		void setEffect(const char* effect);
		u32 width() const { return this->width_; }
		u32 height() const { return this->height_; }

	private:
		const Window& parentWindow_;
		u32 width_;
		u32 height_;
		FrameBufferObject fbo_;
		Texture colorAttachment_;
		RenderBufferObject depthStencilAttachment_;
		AssetManagement::ShaderEffectCache& fxCache_;
		ShaderEffect* shaderEffect_;
		Mesh screenQuad_;
		Common::ColorRgba backgroundColor_;

		Mesh createScreenQuad();
	};
}
