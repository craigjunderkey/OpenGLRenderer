#include "VertexAttribute.h"

using namespace Graphics;

VertexAttribute::VertexAttribute(u16 numElements, DataType dataType)
	: numElementsPer_(numElements), numGlAttributes_(1), type_(dataType)
{
}

VertexAttribute::VertexAttribute(u16 numElementsPer, u16 numAttributes, DataType dataType)
	: numElementsPer_(numElementsPer), numGlAttributes_(numAttributes), type_(dataType)
{
}

void VertexAttribute::bind(u32 index, u32 stride, u32 offset) const
{
	for (int i = 0; i < this->numGlAttributes_; i++)
	{
		u32 relativeOffset = offset + i * this->numElementsPer_ * sizeOf(this->type_);
		
		switch (this->type_)
		{
		case DataType::Float:
			glVertexAttribPointer(
				index + i,
				this->numElementsPer_,
				(GLenum)this->type_,
				GL_FALSE,
				stride,
				(const void*)relativeOffset
			);
			break;
		case DataType::Uint:
			glVertexAttribIPointer(
				index + i,
				this->numElementsPer_,
				(GLenum)this->type_,
				stride,
				(const void*)relativeOffset
			);
			break;
		}
		
		glEnableVertexAttribArray(index + i);

		//std::cout << "glVertexAttribPointer( "
		//	<< index + i << " " << this->numElementsPer_ << " GL_FLOAT GL_FALSE "
		//	<< stride << " " << relativeOffset << " );\n";
		//std::cout << "glEnableVertexAttribArray( " << index + i << " );\n";
	}
}

u32 VertexAttribute::size()
{
	return sizeOf(this->type_) * this->numElementsPer_ * this->numGlAttributes_;
}

u32 VertexAttribute::sizeOf(DataType type)
{
	switch (type)
	{
	case DataType::Float:
		return sizeof(f32);
	case DataType::Uint:
		return sizeof(u32);
	}
}
