#pragma once
#include <vector>
#include <memory>
#include "Resource.h"
#include "Path.h"

namespace Resources
{
	class ResourceLinker
	{
	public:
		virtual void link(Resource& resource) const = 0;
		virtual std::vector<Common::Path> getDependencies() const = 0;
		virtual std::unique_ptr<ResourceLinker> newInstance() const = 0;
		virtual ~ResourceLinker() = default;

	protected:
	};
}
