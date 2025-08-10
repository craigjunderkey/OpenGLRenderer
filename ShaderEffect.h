#pragma once
#include "Shader.h"
#include "ShaderProgram.h"
#include "UniformManager.h"
#include "Types.h"
#include "ShaderCache.h"

namespace Graphics
{
	class ShaderEffect
	{
		friend class SpriteBatch;
		friend class Scene3D;
	
	public:
		ShaderEffect(const AssetManagement::ShaderCache& cache, i32 vertex, i32 geometry, i32 fragment, i32 tessControl, i32 tessEval);
		ShaderEffect(const AssetManagement::ShaderCache& cache, i32 compute);
		UniformManager& uniforms();

	private:
		ShaderProgram program_;
	};
}
