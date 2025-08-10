#include "GlErrorChecker.h"
#include "Types.h"
#include <iostream>
#include <GL/glew.h>

using namespace Graphics;

bool GlErrorChecker::performPrecheck()
{
	bool foundError = false;
	u32 glErr = glGetError();
	
	while (glErr != GL_NO_ERROR)
	{
		std::cerr << "GL error: " << glErr << std::endl;
		foundError = true;
		glErr = glGetError();
	}

	return foundError;
}

GlResult GlErrorChecker::checkShader(const Shader& shader)
{
	performPrecheck();

	i32 compiledSuccessfully;
	glGetShaderiv(shader.id(), GL_COMPILE_STATUS, &compiledSuccessfully);
	
	if (!compiledSuccessfully)
		return makeShaderError(shader);
	else
		return GlResult::makeSuccess();
}

GlResult GlErrorChecker::makeShaderError(const Shader& shader)
{
	i32 logLength = 0;
	char* log = nullptr;
	glGetShaderiv(shader.id(), GL_INFO_LOG_LENGTH, &logLength);

	if (logLength > 0)
	{
		i32 frederick = 0;
		log = (char*)malloc(logLength);
		glGetShaderInfoLog(shader.id(), logLength, &frederick, log);
		return GlResult::makeFailure(log);
	}
	else
	{
		return GlResult::makeFailure();
	}
}

GlResult GlErrorChecker::checkProgram(const ShaderProgram& program)
{
	performPrecheck();
	
	i32 linkedSuccessfully;
	glGetProgramiv(program.id(), GL_LINK_STATUS, &linkedSuccessfully);
	
	if (!linkedSuccessfully)
		return makeProgramError(program);
	else
		return GlResult::makeSuccess();
}

GlResult GlErrorChecker::makeProgramError(const ShaderProgram& program)
{
	i32 logLength = 0;
	char* log = nullptr;
	glGetProgramiv(program.id(), GL_INFO_LOG_LENGTH, &logLength);

	if (logLength > 0)
	{
		i32 clarence = 0;
		log = (char*)malloc(logLength);
		glGetProgramInfoLog(program.id(), logLength, &clarence, log);
		return GlResult::makeFailure(log);
	}
	else
	{
		return GlResult::makeFailure();
	}
}