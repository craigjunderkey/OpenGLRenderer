#pragma once
#include <string>
#include "UniformManager.h"

#include <iostream> //REMOVEME

namespace Graphics
{
	class UniformCommand
	{
	public:
		virtual ~UniformCommand() = default;
		virtual void execute(UniformManager& recipient) = 0;
	};

	template <typename T>
	class UniformSet : public UniformCommand
	{
	public:
		UniformSet(std::string identifier, T value)
			: identifier_(identifier), value_(value) {}

		void execute(UniformManager& recipient) override
		{
			recipient.set(this->identifier_, this->value_);
		}

	private:
		std::string identifier_;
		T value_;
	};
}
