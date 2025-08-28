#pragma once
#include "ResourceLoader.h"

namespace Resources
{
	class PackageDefinitionLoader : public ResourceLoader
	{
		Resource* load(const Common::Path& source) const override;
		std::unique_ptr<ResourceLoader> newInstance() const override;
		~PackageDefinitionLoader() override = default;
	};
}
