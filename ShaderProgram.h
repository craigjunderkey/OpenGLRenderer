#pragma once
#include "Shader.h"
#include "Types.h"
#include "UniformManager.h"

namespace Graphics
{
	class ShaderProgram
	{
	public:
		void attachShader(const Shader& shader);
		void link();
		void use() const;
		UniformManager& uniforms();
		u32 id() const { return this->id_; }
		ShaderProgram();
		ShaderProgram(ShaderProgram&& other) noexcept;
		~ShaderProgram();

	private:
		static const u32 NO_PROGRAM = 0;
		
		u32 id_;
		UniformManager uniforms_;
	};
}
