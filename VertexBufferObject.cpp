#include "VertexBufferObject.h"
#include <GL/glew.h>

using namespace Graphics;

VertexBufferObject::VertexBufferObject()
{
	glGenBuffers(1, &this->id_);
}

void VertexBufferObject::bind(const void* data, u32 size)
{
	glBindBuffer(GL_ARRAY_BUFFER, this->id_);

	// TODO: add options for draw type
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
}

void VertexBufferObject::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, this->id_);
}

VertexBufferObject::~VertexBufferObject()
{
	glDeleteBuffers(1, &this->id_);
}
