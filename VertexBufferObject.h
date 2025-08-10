#pragma once
#include <vector>
#include "Types.h"

namespace Graphics
{
	class VertexBufferObject
	{
	public:
		VertexBufferObject();
		u32 id() const { return this->id_; }
		void bind(const void* data, u32 size);
		void bind();
		~VertexBufferObject();
	
	private:
		u32 id_;
	};
}