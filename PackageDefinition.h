#pragma once
#include <vector>
#include <string>
#include "PreResourceMeta.h"

namespace Resources
{
	struct PackageDefinition
	{
		void addFile(PackablePreResource type, std::string name)
		{
			modules[(u32)(PreResourceType)type].push_back(std::move(name));
		}

		std::vector<std::string> modules[PreResourceMeta::NUM_PACKABLE_PRE_RESOURCES];
	};
}