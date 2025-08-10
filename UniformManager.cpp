#include "UniformManager.h"
#include "ErrorReporter.h"
#include "ShaderProgram.h"
#include <GL/glew.h>

using namespace Graphics;

UniformManager::UniformManager(ShaderProgram& program)
	: programId_(program.id())
{
	this->uniformLocations_.reserve(8);
}

i32 UniformManager::retrieve(const std::string& identifier)
{
	i32 location;

	auto it = this->uniformLocations_.find(identifier);
	if (it == this->uniformLocations_.end())
	{
		location = glGetUniformLocation(programId_, identifier.c_str());
		this->uniformLocations_.insert({ identifier, location });
	}
	else
	{
		location = it->second;
	}
	
	bool idExists = location != -1;

	if (idExists)
	{
		return location;
	}
	else
	{
		Common::ErrorReporter::panic("Tried to retrieve an undeclared uniform " + identifier + ".");
	}
}

void UniformManager::set(const std::string& identifier, f32 value)
{
	glUseProgram(programId_);
	glUniform1f(retrieve(identifier), value);
}

void UniformManager::set(const std::string& identifier, const mat4& value)
{
	glUseProgram(programId_);
	glUniformMatrix4fv(retrieve(identifier), 1, GL_FALSE, glm::value_ptr(value));
}

void UniformManager::set(const std::string& identifier, const vec4& value)
{
	glUseProgram(programId_);
	glUniform4fv(retrieve(identifier), 1, glm::value_ptr(value));
}

void UniformManager::set(const std::string& identifier, u32 value)
{
	glUseProgram(programId_);
	glUniform1ui(retrieve(identifier), value);
}

void UniformManager::set(const std::string& identifier, i32 value)
{
	glUseProgram(programId_);
	glUniform1i(retrieve(identifier), value);
}

void UniformManager::set(const std::string& identifier, Texture::Unit value)
{
	glUseProgram(programId_);
	glUniform1i(retrieve(identifier), (i32)value);
}