#pragma once
#include "Resource.h"
#include "Path.h"

namespace Resources
{
	class ResourceUnpacker
	{
	public:
		virtual Resource unpack(Common::Path pack) = 0;
		virtual ~ResourceUnpacker() = default;
	};
}
