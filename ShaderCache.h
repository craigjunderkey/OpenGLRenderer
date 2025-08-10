#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include "Shader.h"
#include "Types.h"

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
		
		static const std::string& VERTEX;
		static const std::string& FRAGMENT;
		static const std::string& GEOMETRY;
		static const std::string& COMPUTE;
		static const std::string& TESS_CONTROL;
		static const std::string& TESS_EVAL;

		std::vector<Graphics::Shader> shaders_;
		std::unordered_map<std::string, i32> shaderNames_;

		i32 cacheShader(const std::string& path);
		
		static ShaderMetaData getMetaData(const std::string& path);
	};
}
