#pragma once
#include <GL/glew.h>
#include "Types.h"
#include "Texture.h"
#include "RenderBufferObject.h"

namespace Graphics
{
	class FrameBufferObject
	{
	public:
		enum AttachmentType
		{
			Color = GL_COLOR_ATTACHMENT0, // + colorAttachmentCount_
			Depth = GL_DEPTH_ATTACHMENT,
			Stencil = GL_STENCIL_ATTACHMENT,
			DepthStencil = GL_DEPTH_STENCIL_ATTACHMENT
		};

		FrameBufferObject();
		~FrameBufferObject();
		void attach(Texture& texture, AttachmentType type);
		void attach(RenderBufferObject& rbo, AttachmentType type);
		void bind();
		void unbind();
		bool isComplete();
		u32 id() const { return this->id_; }

	private:
		static constexpr u8 MAX_COLOR_ATTACHMENTS = 16;

		u32 id_;
		u8 numColorAttachments_;
	};
}
