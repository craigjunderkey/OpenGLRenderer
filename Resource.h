#pragma once

namespace Resources
{
	class Resource
	{
		virtual void init() = 0;
		virtual void destroy() = 0;
		virtual ~Resource() = default;
	};
}