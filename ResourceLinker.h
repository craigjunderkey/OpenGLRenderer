#pragma once
#include "Resource.h"

namespace Resources
{
	class ResourceLinker
	{
		virtual void link(Resource& resource) = 0;
		virtual ~ResourceLinker() = default;
	};
}
