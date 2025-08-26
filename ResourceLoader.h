#pragma once
#include <memory>
#include "Resource.h"
#include "Path.h"

namespace Resources
{
	class ResourceLoader
	{
	public:
		// TODO: add a memory allocator 'destination'
		virtual Resource* load(Common::Path source) const = 0;
		
		virtual std::unique_ptr<ResourceLoader> newInstance() const = 0;
		virtual ~ResourceLoader() = default;
	};
}
