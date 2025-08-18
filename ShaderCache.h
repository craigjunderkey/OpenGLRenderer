#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include "Shader.h"
#include "Types.h"
#include "Path.h"

namespace AssetManagement
{
	class ShaderCache
	{
		friend class ContentManager;

	public:
		static const i32 NO_SHADER = -1;

		ShaderCache(size_t numShaders);
		const Graphics::Shader& getShader(i32 index) const;
		i32 getShaderIndex(const std::string& name) const;

	private:
		struct ShaderMetaData
		{
			ShaderMetaData(const std::string& name, Graphics::Shader::Type type)
				: name(name), type(type) {}
			
			std::string name;
			Graphics::Shader::Type type;
		};
		
		static const char* VERTEX;
		static const char* FRAGMENT;
		static const char* GEOMETRY;
		static const char* COMPUTE;
		static const char* TESS_CONTROL;
		static const char* TESS_EVAL;

		std::vector<Graphics::Shader> shaders_;
		std::unordered_map<std::string, i32> shaderNames_;

		i32 cacheShader(const Common::Path& path);
		
		static ShaderMetaData getMetaData(const Common::Path& path);
	};
}
