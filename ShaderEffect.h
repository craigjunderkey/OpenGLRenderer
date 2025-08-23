#pragma once
#include "Shader.h"
#include "ShaderProgram.h"
#include "UniformManager.h"
#include "Types.h"
#include "ShaderCache.h"
#include "StringId.h"
#include "Resource.h"

namespace Graphics
{
	class ShaderEffect : Resources::Resource
	{
		// TODO: get rid of these; just add a public use function. (why did I do this?)
		friend class SpriteBatch;
		friend class Scene3D;
		friend class VirtualScreen;
	
	public:
		struct ShaderIdBlock
		{
			StringId vertex = StringId::NONE;
			StringId fragment = StringId::NONE;
			StringId geometry = StringId::NONE;
			StringId compute = StringId::NONE;
			StringId tessControl = StringId::NONE;
			StringId tessEval = StringId::NONE;
		};

		ShaderEffect(ShaderIdBlock shaders);
		UniformManager& uniforms();

		void initResource() override;

	private:
		ShaderProgram program_;
		ShaderIdBlock shaders_;
		
		struct ShaderPtrBlock
		{
			const Shader* vertex = nullptr;
			const Shader* fragment = nullptr;
			const Shader* geometry = nullptr;
			const Shader* compute = nullptr;
			const Shader* tessControl = nullptr;
			const Shader* tessEval = nullptr;
		};
		
		void link(ShaderPtrBlock* pointers);
		void linkStandardEffect(ShaderPtrBlock* pointers);
		void linkComputeEffect(ShaderPtrBlock* pointers);
	};
}
