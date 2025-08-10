#pragma once

namespace Graphics
{
	class VertexAttributeSet;
	
	class VertexAttributeSets
	{
	public:
		static VertexAttributeSet* POSITION;
		static VertexAttributeSet* POSITION_UV;
		static VertexAttributeSet* POSITION2D_UV;
		static VertexAttributeSet* POSITION_COLOR;
		static VertexAttributeSet* TRANSFORM_UV;
		static VertexAttributeSet* TRANSFORM_UV_UINT;

		static void initialize();

	private:
		VertexAttributeSets() = delete;
	};
}
