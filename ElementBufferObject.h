#pragma once
#include "Types.h"

namespace Graphics
{
	class ElementBufferObject
	{
		friend class Mesh;
		friend class InstancedMesh;
	
	public:
		ElementBufferObject();
		~ElementBufferObject();
		u32 id() const { return this->id_; }
		bool isEmpty() const;

		static ElementBufferObject makeEmpty();
	
	private:
		u32 id_;

		void bind(const u32* indices, u32 indexCount);
		ElementBufferObject(u32 id);
	};
}