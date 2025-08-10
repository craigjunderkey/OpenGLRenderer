#pragma once
#include "Types.h"
#include "GlImageFormat.h"

namespace Graphics
{
	class RenderBufferObject
	{
	public:
		RenderBufferObject(GlImageFormat format, u32 width, u32 height);
		~RenderBufferObject();
		void bind();
		u32 id() const { return this->id_; }

	private:
		u32 id_;
	};
}
