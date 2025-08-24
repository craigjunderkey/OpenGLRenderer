#pragma once
#include "Resource.h"
#include "Path.h"

namespace Resources
{
	class ResourceLoader
	{
	public:
		virtual Resource* load(Common::Path source) = 0;
		virtual ResourceLoader* newInstance() = 0;
		virtual ~ResourceLoader() = default;
	};
}
