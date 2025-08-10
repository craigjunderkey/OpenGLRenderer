#include "ElementBufferObject.h"
#include <GL/glew.h>

#define EMPTY 0

using namespace Graphics;

ElementBufferObject::ElementBufferObject()
{
	glGenBuffers(1, &this->id_);
}

ElementBufferObject::ElementBufferObject(u32 id)
{
	this->id_ = id;
}

ElementBufferObject::~ElementBufferObject()
{
	if (this->id_ != EMPTY)
		glDeleteBuffers(1, &this->id_);
}

void ElementBufferObject::bind(const u32* indices, u32 indexCount)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(u32), indices, GL_STATIC_DRAW);
}

bool ElementBufferObject::isEmpty() const
{
	return this->id_ == EMPTY;
}

ElementBufferObject ElementBufferObject::makeEmpty()
{
	return ElementBufferObject(EMPTY);
}