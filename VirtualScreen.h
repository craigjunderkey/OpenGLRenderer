#pragma once
#include "Types.h"
#include "Window.h"
#include "FrameBufferObject.h"
#include "RenderBufferObject.h"
#include "ShaderProgram.h"
#include "Mesh.h"
#include "Color.h"

namespace Graphics
{
	class VirtualScreen
	{
	public:
		VirtualScreen(const Window& parentWindow, u32 width, u32 height);
		~VirtualScreen();
		void begin();
		void end();
		void setBackgroundColor(Common::ColorRgba color);
		u32 width() const { return this->width_; }
		u32 height() const { return this->height_; }

	private:
		const Window& parentWindow_;
		u32 width_;
		u32 height_;
		FrameBufferObject fbo_;
		Texture colorAttachment_;
		RenderBufferObject depthStencilAttachment_;
		ShaderProgram shaderProgram_;
		Mesh screenQuad_;
		Common::ColorRgba backgroundColor_;

		Mesh createScreenQuad();
		ShaderProgram createShaderProgram(Texture::Unit textureUnit);
	};
}
