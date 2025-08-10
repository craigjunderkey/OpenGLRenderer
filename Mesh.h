#pragma once
#include "Types.h"
#include "VertexBufferObject.h"
#include "VertexArrayObject.h"
#include "VertexAttributeSet.h"
#include "ElementBufferObject.h"

namespace Graphics
{
	class Mesh
	{
	public:
		Mesh(const void* data, u32 size, const VertexAttributeSet& attributes);
		Mesh(const void* data, u32 size, const u32* indices, u32 indexCount, const VertexAttributeSet& attributes);
		void bind();
		bool hasEbo() const;
		u32 count() const { return this->count_; }
	
	private:
		VertexArrayObject vao_;
		VertexBufferObject vbo_;
		ElementBufferObject ebo_;
		u32 count_;
	};
}
