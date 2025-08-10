#include "GlResult.h"
#include "Shader.h"
#include "ShaderProgram.h"
#pragma once

namespace Graphics
{
	class GlErrorChecker
	{
	public:
		static GlResult checkProgram(const ShaderProgram&);
		static GlResult checkShader(const Shader&);

	private:
		static bool performPrecheck();
		static GlResult makeProgramError(const ShaderProgram&);
		static GlResult makeShaderError(const Shader&);
	};
}