#include "VertexArrayObject.h"
#include "VertexAttributeSet.h"
#include <GL/glew.h>

using namespace Graphics;

VertexArrayObject::VertexArrayObject()
{
	glGenVertexArrays(1, &this->id_);
}

VertexArrayObject::~VertexArrayObject()
{
	glDeleteVertexArrays(1, &this->id_);
}

void VertexArrayObject::bind()
{
	glBindVertexArray(this->id_);
}