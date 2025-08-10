#pragma once
#include <string>
#include <unordered_map>
#include "Types.h"
#include "Texture.h"

namespace Graphics
{
	class ShaderProgram;
	
	class UniformManager
	{
	public:
		UniformManager(ShaderProgram& program);
		void set(const std::string& identifier, f32 value);
		void set(const std::string& identifier, const mat4& value);
		void set(const std::string& identifier, const vec4& value);
		void set(const std::string& identifier, u32 value);
		void set(const std::string& identifier, i32 value);
		void set(const std::string& identifier, Texture::Unit value);

	private:
		u32 programId_;
		std::unordered_map<std::string, i32> uniformLocations_;

		i32 retrieve(const std::string& identifier);
	};
}
