#pragma once
#include "VertexBufferObject.h"
#include "ElementBufferObject.h"
#include "VertexArrayObject.h"
#include "VertexAttributeSet.h"
#include "Types.h"

namespace Graphics
{
	class InstancedMesh
	{
	public:
		InstancedMesh(const void* staticData, u32 staticDataSize, const VertexAttributeSet& staticAttributes, const VertexAttributeSet& instanceAttributes);
		InstancedMesh(const void* staticData, u32 staticDataSize, const u32* staticIndices, u32 staticIndexCount, const VertexAttributeSet& staticAttributes, const VertexAttributeSet& instanceAttributes);
		void bind();
		void bind(const void* instanceData, u32 instanceDataSize);
		bool hasEbo() const;
		u32 count() const { return this->count_; }
		VertexBufferObject& instanceVbo() { return this->instanceVbo_; }

	private:
		VertexArrayObject vao_;
		VertexBufferObject staticVbo_;
		ElementBufferObject staticEbo_;
		VertexBufferObject instanceVbo_;
		u32 count_;
	};
}