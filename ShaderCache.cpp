#include "ShaderCache.h"
#include "ErrorReporter.h"
#include "GlErrorChecker.h"
#include "FileManager.h"

using namespace Graphics;
using namespace AssetManagement;
using namespace Common;

const char* ShaderCache::VERTEX = "vert.glsl";
const char* ShaderCache::FRAGMENT = "frag.glsl";
const char* ShaderCache::GEOMETRY = "geom.glsl";
const char* ShaderCache::COMPUTE = "comp.glsl";
const char* ShaderCache::TESS_CONTROL = "tessc.glsl";
const char* ShaderCache::TESS_EVAL = "tesse.glsl";

ShaderCache::ShaderCache(size_t numShaders)
{
	shaders_.reserve(numShaders);
	shaderNames_.reserve(numShaders);
}

const Shader& ShaderCache::getShader(i32 index) const
{
	return shaders_[index];
}

i32 ShaderCache::getShaderIndex(const std::string& name) const
{
	auto it = shaderNames_.find(name);

	if (it != shaderNames_.end())
	{
		return it->second;
	}
	else
	{
		if (name.find('.') != std::string::npos)
			ErrorReporter::panic("Tried to retrieve non-existent shader " + name + " from cache.");
		else
			ErrorReporter::panic("Tried to retrieve non-existent shader " + name + " from cache. Remember to include the shader type extension, e.g., .vert, .frag.");
	}
}

i32 ShaderCache::cacheShader(const Path& path)
{
	ShaderMetaData meta = getMetaData(path);
	Shader shader = Shader::fromFile(path, meta.type);
	GlErrorChecker::checkShader(shader).report();

	i32 index = shaders_.size();
	shaders_.push_back(std::move(shader));
	shaderNames_.insert({ meta.name, index });

	return index;
}

ShaderCache::ShaderMetaData ShaderCache::getMetaData(const Path& path)
{
	std::string name = std::string(path.name().data());
	
	if (path.fullExtensionMatches(VERTEX))
	{
		return ShaderMetaData(name, Shader::Type::Vertex);
	}
	else if (path.fullExtensionMatches(FRAGMENT))
	{
		return ShaderMetaData(name, Shader::Type::Fragment);
	}
	else if (path.fullExtensionMatches(GEOMETRY))
	{
		return ShaderMetaData(name, Shader::Type::Geometry);
	}
	else if (path.fullExtensionMatches(COMPUTE))
	{
		return ShaderMetaData(name, Shader::Type::Compute);
	}
	else if (path.fullExtensionMatches(TESS_CONTROL))
	{
		return ShaderMetaData(name, Shader::Type::TessellationControl);
	}
	else if (path.fullExtensionMatches(TESS_EVAL))
	{
		return ShaderMetaData(name, Shader::Type::TessellationEvaluation);
	}
	
	ErrorReporter::panic(path.path() + " doesn't declare its type; file extension must be .x.glsl, where x is vert, frag, geom, comp, tessc, or tesse.");
}
