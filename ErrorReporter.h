#pragma once
#include <iostream>

namespace Common
{
	class ErrorReporter
	{
	public:
		static void report(std::string message)
		{
			std::cerr << "ERROR: " << message << std::endl;
		}

		static void warn(std::string message)
		{
			std::cerr << "WARNING: " << message << std::endl;
		}
		
		static void panic(std::string message)
		{
			report(message);
			exit(EXIT_FAILURE);
		}

		static void panicElse(bool condition, std::string message)
		{
			if (!condition)
				panic(message);
		}
	};
}
