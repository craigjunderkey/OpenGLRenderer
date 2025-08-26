#pragma once
#include <memory>
#include "Path.h"

namespace Resources
{
	class ResourceCompiler
	{
	public:
		virtual void compile(Common::Path source, Common::Path destination) const = 0;
		virtual std::unique_ptr<ResourceCompiler> newInstance() const = 0;
		virtual ~ResourceCompiler() = default;
	};
}
