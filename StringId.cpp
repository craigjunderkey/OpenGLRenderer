#include "StringId.h"
#include "compile_time_crc.hpp"

constexpr u32 hashCrc32(const char* string)
{
	return crcdetail::compute(string, strlen(string));
}

constexpr u32 hashCrc32(const char* string, u32 length)
{
	return crcdetail::compute(string, length);
}

StringId internString(const char* string)
{
	// TODO: add it to a table
	return StringId(hashCrc32(string));
}