#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include "ShaderEffect.h"
#include "Types.h"
#include "ShaderCache.h"

namespace AssetManagement
{
	class ShaderEffectCache
	{
		friend class ContentManager;

	public:
		static const i32 NO_EFFECT = -1;

		ShaderEffectCache(size_t numFx);
		Graphics::ShaderEffect& getEffect(i32 index);
		Graphics::ShaderEffect& getEffect(const std::string& name);
		i32 getEffectIndex(const std::string& name) const;
		size_t numEffects() const { return this->fx_.size(); }

	private:
		struct ShaderBlock
		{
			i32 vertex = ShaderCache::NO_SHADER;
			i32 fragment = ShaderCache::NO_SHADER;
			i32 geometry = ShaderCache::NO_SHADER;
			i32 compute = ShaderCache::NO_SHADER;
			i32 tessControl = ShaderCache::NO_SHADER;
			i32 tessEval = ShaderCache::NO_SHADER;
		};
		
		std::vector<Graphics::ShaderEffect> fx_;
		std::unordered_map<std::string, i32> fxNames_;

		i32 cacheShaderEffect(const ShaderCache& shaders, const std::string& path);
		
		static Graphics::ShaderEffect createEffectFromBlock(const ShaderCache& shaders, const ShaderBlock& block);

		static const std::string& VERTEX;
		static const std::string& FRAGMENT;
		static const std::string& GEOMETRY;
		static const std::string& COMPUTE;
		static const std::string& TESS_CONTROL;
		static const std::string& TESS_EVAL;
	};
}