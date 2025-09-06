#pragma once
#include <string>
#include <unordered_map>
#include <array>
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
		const Common::Path* getPath(PreResourceType type, const std::string& name) const;

	private:
		void fillMap(i32 index, const PreResourceDescription& preResource);

		using FileMapRep = std::array<std::unordered_map<std::string, Common::Path>, PreResourceMeta::NUM_PRE_RESOURCES>;
		FileMapRep modules_;

	public:
		FileMapRep::const_iterator begin() const { return this->modules_.begin(); }
		FileMapRep::const_iterator end() const { return this->modules_.end(); }
	};
}
