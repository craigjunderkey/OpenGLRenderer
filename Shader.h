#pragma once
#include <string>
#include <GL/glew.h>
#include "Types.h"
#include "Path.h"

namespace Graphics
{
	class Shader
	{
	public:
		enum class Type
		{
			Vertex = GL_VERTEX_SHADER,
			Fragment = GL_FRAGMENT_SHADER,
			Geometry = GL_GEOMETRY_SHADER,
			Compute = GL_COMPUTE_SHADER,
			TessellationControl = GL_TESS_CONTROL_SHADER,
			TessellationEvaluation = GL_TESS_EVALUATION_SHADER
		};

		Shader(const char* source, Type type);
		Shader(Shader&& other) noexcept;
		static Shader fromFile(const char* filePath, Type type);
		static Shader fromFile(const Common::Path& filePath, Type type);
		u32 id() const { return this->id_; }
		~Shader();

	private:
		static const u32 NO_SHADER = 0;

		u32 id_;
	};
}
