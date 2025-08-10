#pragma once
#include <vector>
#include "UniformCommand.h"
#include "UniformManager.h"
#include "Types.h"

namespace Graphics
{
	class UniformCommandBlock
	{
	public:
		UniformCommandBlock();
		~UniformCommandBlock();
		void addCommand(UniformCommand* command);
		void execute(UniformManager& uniformManager);

	private:
		std::vector<UniformCommand*> commands_;
	};
}
