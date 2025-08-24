#pragma once
#include <vector>
#include "Resource.h"
#include "Path.h"

namespace Resources
{
	class ResourceLinker
	{
	public:
		virtual void link(Resource& resource) = 0;
		virtual std::vector<Common::Path> getDependencies() = 0;
		virtual ResourceLinker* newInstance() = 0;
		virtual ~ResourceLinker() = default;

	protected:
	};
}
