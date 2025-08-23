#pragma once
#include "Path.h"

namespace Resources
{
	class ResourcePacker
	{
	public:
		virtual void pack() = 0;
		virtual ~ResourcePacker() = default;
	};
}
