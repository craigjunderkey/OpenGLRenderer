#pragma once
#include <string>
#include <unordered_map>
#include "PreResourceMeta.h"
#include "Path.h"
#include "Types.h"

namespace Resources
{
	class PreResourceFileMap
	{
	public:
		PreResourceFileMap();
		const std::unordered_map<std::string, Common::Path>& getMap(PreResourceType type) const;
		const Common::Path& getPath(PreResourceType type, const std::string& name) const;

	private:
		void fillMap(i32 index, const PreResourceDescription& preResource);

		std::unordered_map<std::string, Common::Path> modules_[PreResourceMeta::NUM_PRE_RESOURCES];
	};
}
