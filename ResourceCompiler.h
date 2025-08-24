#pragma once
#include "Path.h"

namespace Resources
{
	class ResourceCompiler
	{
	public:
		virtual void compile(Common::Path source, Common::Path destination) = 0;
		virtual ResourceCompiler* newInstance() = 0;
		virtual ~ResourceCompiler() = default;
	};
}
