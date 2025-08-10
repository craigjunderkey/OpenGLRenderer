#pragma once

namespace Graphics
{
	class VertexAttribute;
	
	class VertexAttributes
	{
	public:
		static VertexAttribute* VECTOR2;
		static VertexAttribute* VECTOR3;
		static VertexAttribute* VECTOR4;
		static VertexAttribute* MATRIX4;

		static void initialize();

	private:
		VertexAttributes() = delete;
	};
}
