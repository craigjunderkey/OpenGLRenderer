#include "Mesh.h"
#include <iostream>

using namespace Graphics;

Mesh::Mesh(const void* data, u32 size, const VertexAttributeSet& attributes)
	: vao_(VertexArrayObject()),
	vbo_(VertexBufferObject()),
	ebo_(ElementBufferObject::makeEmpty())
{
	this->count_ = size / attributes.size_;
	
	this->vao_.bind();
	this->vbo_.bind(data, size);
	attributes.bind();
}

Mesh::Mesh(const void* data, u32 size, const u32* indices, u32 indexCount, const VertexAttributeSet& attributes)
	: vao_(VertexArrayObject()),
	vbo_(VertexBufferObject()),
	ebo_(ElementBufferObject())
{
	this->count_ = indexCount;

	this->vao_.bind();
	this->vbo_.bind(data, size);
	this->ebo_.bind(indices, indexCount);
	attributes.bind();
}

void Mesh::bind()
{
	vao_.bind();
}

bool Mesh::hasEbo() const
{
	return !this->ebo_.isEmpty();
}