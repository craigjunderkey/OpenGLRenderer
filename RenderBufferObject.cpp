#include "RenderBufferObject.h"

using namespace Graphics;

RenderBufferObject::RenderBufferObject(GlImageFormat format, u32 width, u32 height)
{
	glGenRenderbuffers(1, &this->id_);
	glBindRenderbuffer(GL_RENDERBUFFER, this->id_);
	glRenderbufferStorage(GL_RENDERBUFFER, (GLenum)format, width, height);
}

RenderBufferObject::~RenderBufferObject()
{
	glDeleteRenderbuffers(1, &this->id_);
}

void RenderBufferObject::bind()
{
	glBindRenderbuffer(GL_RENDERBUFFER, this->id_);
}