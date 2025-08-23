#pragma once
#include "Types.h"

namespace Resources
{
	class Resource
	{
	public:
		virtual void initResource() = 0;
		virtual void destroyResource() {};
		virtual ~Resource() = default;
		u32 refCount = 0;
	};
}