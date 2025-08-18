#include <fstream>
#include "json.hpp"
#include "ShaderEffectCache.h"
#include "ErrorReporter.h"
#include "FileManager.h"

using namespace Graphics;
using namespace AssetManagement;
using namespace Common;

using json = nlohmann::json;

const char* ShaderEffectCache::VERTEX = "vertex";
const char* ShaderEffectCache::FRAGMENT = "fragment";
const char* ShaderEffectCache::GEOMETRY = "geometry";
const char* ShaderEffectCache::COMPUTE = "compute";
const char* ShaderEffectCache::TESS_CONTROL = "tess_control";
const char* ShaderEffectCache::TESS_EVAL = "tess_eval";

ShaderEffectCache::ShaderEffectCache(size_t numFx)
{
	this->fx_.reserve(numFx);
	this->fxNames_.reserve(numFx);
}

ShaderEffect& ShaderEffectCache::getEffect(i32 index)
{
	return this->fx_[index];
}

ShaderEffect& ShaderEffectCache::getEffect(const std::string& name)
{
	return getEffect(getEffectIndex(name));
}

i32 ShaderEffectCache::getEffectIndex(const std::string& name) const
{
	auto it = fxNames_.find(name);

	if (it != fxNames_.end())
	{
		return it->second;
	}
	else
	{
		ErrorReporter::panic("Tried to retrieve non-existent shader effect " + name + " from cache.");
	}
}

i32 ShaderEffectCache::cacheShaderEffect(const ShaderCache& shaders, const Path& path)
{
	// load effect file
	ShaderBlock block = ShaderBlock();
	std::ifstream effectFile = std::ifstream(path.path().data());
	json effectJson = json::parse(effectFile);

	// get effect name
	std::string name = std::string(path.name().data());
	
	// fill out block with shader indices
	for (const auto& [type, shaderName]: effectJson.items())
	{
		i32 shaderIndex = shaders.getShaderIndex(shaderName);
		i32* slot = nullptr;		// this is bullshit;
									// just to avoid an error about possible uninitialized pointer
		if (type == VERTEX)
			slot = &block.vertex;
		else if (type == FRAGMENT)
			slot = &block.fragment;
		else if (type == GEOMETRY)
			slot = &block.geometry;
		else if (type == COMPUTE)
			slot = &block.compute;
		else if (type == TESS_CONTROL)
			slot = &block.tessControl;
		else if (type == TESS_EVAL)
			slot = &block.tessEval;
		else
			ErrorReporter::panic("\"" + type + "\" is an invalid shader type. Found in " + name + ".");

		ErrorReporter::panicElse(*slot == ShaderCache::NO_SHADER,
			"Tried to write two shaders to " + type + " shader. Found in " + name + ".");

		*slot = shaderIndex;
	}

	// create the shader effect
	ErrorReporter::panicElse(block.compute == ShaderCache::NO_SHADER
		|| block.vertex == ShaderCache::NO_SHADER,
		"Effect must be either a compute shader or have a vertex shader; " + name + " isn't.");

	ShaderEffect effect = createEffectFromBlock(shaders, block);

	// add effect to cache
	u32 index = this->fx_.size();
	this->fx_.push_back(std::move(effect));
	this->fxNames_.insert({ name, index });

	return index;
}

ShaderEffect ShaderEffectCache::createEffectFromBlock(const ShaderCache& shaders, const ShaderBlock& block)
{
	if (block.compute != ShaderCache::NO_SHADER)
	{
		return ShaderEffect(shaders, block.compute);
	}
	else
	{
		return ShaderEffect(shaders, block.vertex, block.geometry,
			block.fragment, block.tessControl, block.tessEval);
	}
}