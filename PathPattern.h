#pragma once
#include <optional>
#include "String.h"
#include "Path.h"

namespace Common
{
	struct PathPattern
	{
		PathPattern(Path&& directory, std::optional<String>&& extension)
			: directory(std::move(directory)), extension(std::move(extension)) {
		}

		Path directory;
		std::optional<String> extension;
	};
}
