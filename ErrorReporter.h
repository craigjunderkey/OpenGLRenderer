#pragma once
#include <iostream>
#include "String.h"

namespace Common
{
	class ErrorReporter
	{
	public:
		static void report(const char* message)
		{
			std::cerr << "ERROR: " << message << std::endl;
		}
		static void report(std::string message)
		{
			report(message.data());
		}
		static void report(String message)
		{
			report(message.data());
		}

		static void warn(const char* message)
		{
			std::cerr << "WARNING: " << message << std::endl;
		}
		static void warn(std::string message)
		{
			warn(message.data());
		}
		static void warn(String message)
		{
			warn(message.data());
		}
		
		static void panic(const char* message)
		{
			report(message);
			exit(EXIT_FAILURE);
		}
		static void panic(std::string message)
		{
			panic(message.data());
		}
		static void panic(String message)
		{
			panic(message.data());
		}

		static void panicElse(bool condition, const char* message)
		{
			if (!condition)
				panic(message);
		}
		static void panicElse(bool condition, std::string message)
		{
			panicElse(condition, message.data());
		}
		static void panicElse(bool condition, String message)
		{
			panicElse(condition, message.data());
		}
	};
}