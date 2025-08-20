#pragma once
#include "Path.h"

namespace Resources
{
	class ResourcePacker
	{
		virtual void addFile(Common::Path path) = 0;
		virtual void pack() = 0;
		virtual ~ResourcePacker() = default;
	};
}
