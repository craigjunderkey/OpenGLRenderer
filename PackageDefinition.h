#pragma once
#include <vector>
#include <string>
#include "PreResourceMeta.h"

namespace Resources
{
	struct PackageDefinition
	{
		PackageDefinition(std::string name)
			: name(std::move(name))
		{
		}
		
		void addFile(PreResourceType type, std::string name)
		{
			assert(isPackable(type));
			modules[(u32)(PreResourceType)type].push_back(std::move(name));
		}

		std::vector<std::string> modules[PreResourceMeta::NUM_PACKABLE_PRE_RESOURCES];
		std::string name;
	};
}