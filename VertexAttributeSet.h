#pragma once
#include <vector>
#include "Types.h"
#include "VertexAttribute.h"

namespace Graphics
{
	class VertexAttributeSet
	{
		friend class Mesh;
		friend class InstancedMesh;
	
	public:
		VertexAttributeSet& add(const VertexAttribute attribute);
		VertexAttributeSet& append(const VertexAttributeSet& attributeSet);
	
	private:
		struct BoundVertexAttribute
		{
			BoundVertexAttribute(VertexAttribute attribute, u32 offset)
				: attribute_(attribute), offset_(offset) { }
			
			VertexAttribute attribute_;
			u32 offset_;
		};

		u32 size_ = 0;
		u32 numGlAttributes_ = 0;
		std::vector<BoundVertexAttribute> attributes_;

		void bind() const;
		void bind(u32 offset) const;
	};
}
