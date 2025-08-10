#include <string>
#include "FrameBufferObject.h"
#include "ErrorReporter.h"

using namespace Graphics;
using namespace Common;

FrameBufferObject::FrameBufferObject()
	: numColorAttachments_(0)
{
	glGenFramebuffers(1, &this->id_);
}

FrameBufferObject::~FrameBufferObject()
{
	glDeleteFramebuffers(1, &this->id_);
}

void FrameBufferObject::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, this->id_);
}

void FrameBufferObject::unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBufferObject::attach(Texture& texture, AttachmentType type)
{
	this->bind();

	if (type == AttachmentType::Color)
	{
		ErrorReporter::panicElse(numColorAttachments_ < MAX_COLOR_ATTACHMENTS,
			"Too many color attachments in FBO " + std::to_string(this->id_) + "!");

		glFramebufferTexture2D(GL_FRAMEBUFFER,
			GL_COLOR_ATTACHMENT0 + this->numColorAttachments_,
			GL_TEXTURE_2D, texture.id(), 0);

		this->numColorAttachments_++;
	}
	else
	{
		glFramebufferTexture2D(GL_FRAMEBUFFER, (GLenum)type, GL_TEXTURE_2D, texture.id(), 0);
	}

	this->unbind();
}

void FrameBufferObject::attach(RenderBufferObject& rbo, AttachmentType type)
{
	this->bind();

	if (type == AttachmentType::Color)
	{
		ErrorReporter::panicElse(numColorAttachments_ < MAX_COLOR_ATTACHMENTS,
			"Too many color attachments in FBO " + std::to_string(this->id_) + "!");

		glFramebufferRenderbuffer(GL_FRAMEBUFFER,
			GL_COLOR_ATTACHMENT0 + this->numColorAttachments_,
			GL_RENDERBUFFER, rbo.id());

		this->numColorAttachments_++;
	}
	else
	{
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, (GLenum)type, GL_RENDERBUFFER, rbo.id());
	}

	this->unbind();
}

bool FrameBufferObject::isComplete()
{
	this->bind();
	bool isComplete = glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
	this->unbind();
	return isComplete;
}