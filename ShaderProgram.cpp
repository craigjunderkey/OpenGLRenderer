#include "GL/glew.h"
#include "ShaderProgram.h"
#include "UniformManager.h"

using namespace Graphics;

ShaderProgram::ShaderProgram()
	: id_(glCreateProgram()),
	uniforms_(UniformManager(*this))
{
}

void ShaderProgram::attachShader(const Shader& shader)
{
	glAttachShader(this->id_, shader.id());
}

void ShaderProgram::link()
{
	glLinkProgram(this->id_);
}

void ShaderProgram::use() const
{
	glUseProgram(this->id_);
}

UniformManager& ShaderProgram::uniforms()
{
	return uniforms_;
}

ShaderProgram::~ShaderProgram()
{
	if (this->id_ != NO_PROGRAM)
		glDeleteProgram(this->id_);
}

ShaderProgram::ShaderProgram(ShaderProgram&& other) noexcept
	: uniforms_(other.uniforms_), id_(other.id_)
{
	other.id_ = NO_PROGRAM;
}