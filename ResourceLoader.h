#pragma once
#include "Resource.h"
#include "Path.h"

namespace Resources
{
	class ResourceLoader
	{
	public:
		// TODO: add a memory allocator 'destination'
		virtual Resource* load(Common::Path source) = 0;
		
		virtual ResourceLoader* newInstance() = 0;
		virtual ~ResourceLoader() = default;
	};
}
