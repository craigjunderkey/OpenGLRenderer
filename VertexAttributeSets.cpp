#include "VertexAttributeSets.h"
#include "VertexAttributeSet.h"
#include "VertexAttributes.h"

using namespace Graphics;

VertexAttributeSet* VertexAttributeSets::POSITION = nullptr;
VertexAttributeSet* VertexAttributeSets::POSITION_UV = nullptr;
VertexAttributeSet* VertexAttributeSets::POSITION2D_UV = nullptr;
VertexAttributeSet* VertexAttributeSets::POSITION_COLOR = nullptr;
VertexAttributeSet* VertexAttributeSets::TRANSFORM_UV = nullptr;
VertexAttributeSet* VertexAttributeSets::TRANSFORM_UV_UINT = nullptr;

void VertexAttributeSets::initialize()
{
	assert(POSITION == nullptr); // and so on...

	// POSITION
	POSITION = new VertexAttributeSet();
	POSITION->add(*VertexAttributes::VECTOR3);

	// POSITION_UV
	POSITION_UV = new VertexAttributeSet();
	POSITION_UV->add(*VertexAttributes::VECTOR3);
	POSITION_UV->add(*VertexAttributes::VECTOR2);

	// POSITION2D_UV
	POSITION2D_UV = new VertexAttributeSet();
	POSITION2D_UV->add(*VertexAttributes::VECTOR2);
	POSITION2D_UV->add(*VertexAttributes::VECTOR2);

	// POSITION_COLOR
	POSITION_COLOR = new VertexAttributeSet();
	POSITION_COLOR->add(*VertexAttributes::VECTOR3);
	POSITION_COLOR->add(*VertexAttributes::VECTOR3);

	// TRANSFORM_UV
	TRANSFORM_UV = new VertexAttributeSet();
	TRANSFORM_UV->add(*VertexAttributes::MATRIX4);
	TRANSFORM_UV->add(*VertexAttributes::VECTOR4);

	// TRANSFORM_UV_UINT
	TRANSFORM_UV_UINT = new VertexAttributeSet();
	TRANSFORM_UV_UINT->add(*VertexAttributes::MATRIX4);
	TRANSFORM_UV_UINT->add(*VertexAttributes::VECTOR4);
	TRANSFORM_UV_UINT->add(VertexAttribute(1, VertexAttribute::DataType::Uint));
}
