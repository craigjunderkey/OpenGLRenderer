#include "VertexAttributes.h"
#include "VertexAttribute.h"
#include <cassert>

using namespace Graphics;

VertexAttribute* VertexAttributes::VECTOR2 = nullptr;
VertexAttribute* VertexAttributes::VECTOR3 = nullptr;
VertexAttribute* VertexAttributes::VECTOR4 = nullptr;
VertexAttribute* VertexAttributes::MATRIX4 = nullptr;

void VertexAttributes::initialize()
{
	assert(VECTOR2 == nullptr); // and so on...
	
	VECTOR2 = new VertexAttribute(2, VertexAttribute::DataType::Float);
	VECTOR3 = new VertexAttribute(3, VertexAttribute::DataType::Float);
	VECTOR4 = new VertexAttribute(4, VertexAttribute::DataType::Float);
	MATRIX4 = new VertexAttribute(4, 4, VertexAttribute::DataType::Float);
}