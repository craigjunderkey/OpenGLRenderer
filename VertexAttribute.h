#pragma once
#include "Types.h"
#include <GL/glew.h>

namespace Graphics
{
	class VertexAttribute
	{
	public:
		enum class DataType
		{
			Float = GL_FLOAT,
			Uint = GL_UNSIGNED_INT
		};
		
		VertexAttribute(u16 numElements, DataType dataType);
		VertexAttribute(u16 numElementsPer, u16 numAttributes, DataType dataType);
		void bind(u32 index, u32 stride, u32 offset) const;
		u32 size();
		u32 numGlAttributes() const { return this->numGlAttributes_; }

	private:
		DataType type_;
		u16 numElementsPer_;
		u16 numGlAttributes_;

		static u32 sizeOf(DataType type);
	};
}
