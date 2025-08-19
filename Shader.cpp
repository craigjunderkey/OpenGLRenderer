#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Shader.h"
#include "ErrorReporter.h"

using namespace Graphics;
using namespace Common;

Shader::Shader(const char* source, Type type)
{
	this->id_ = glCreateShader((GLenum)type);
	glShaderSource(this->id_, 1, &source, NULL);
	glCompileShader(this->id_);
}

Shader::Shader(Shader&& other) noexcept
	: id_(other.id_)
{
	other.id_ = NO_SHADER;
}

Shader Shader::fromFile(const char* filePath, Type type)
{
	std::ifstream file;
	std::string source;

	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	
	try
	{
		file.open(filePath);
		std::stringstream sourceStream;
		sourceStream << file.rdbuf();
		file.close();
		source = sourceStream.str();
	}
	catch (std::ifstream::failure e)
	{
		ErrorReporter::panic("Failed to load shader " + std::string(filePath) + ".");
	}

	Shader shader = Shader(source.c_str(), type);
	
	return shader;
}

Shader Shader::fromFile(const Path& path, Type type)
{
	return fromFile(path.path().data(), type);
}

Shader::~Shader()
{
	if (this->id_ != NO_SHADER)
		glDeleteShader(this->id_);
}