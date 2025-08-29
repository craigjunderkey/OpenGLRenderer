#pragma once
#include "ResourceCompiler.h"

namespace Resources
{
	class PackageDefinitionCompiler : public ResourceCompiler
	{
		void compile(const Common::Path& source, const Common::Path& destination) const override;
		std::unique_ptr<ResourceCompiler> newInstance() const override;
		~PackageDefinitionCompiler() override = default;
	};
}
