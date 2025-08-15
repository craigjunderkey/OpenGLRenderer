#pragma once
#include <iostream>
#include "Types.h"

struct StringId
{
	u32 id;	
	StringId(u32 id) : id(id) {}

	// canonize a conversion from StringId to u32
	constexpr operator u32() const noexcept { return this->id; }
};

constexpr u32 hashCrc32(const char* string);
constexpr u32 hashCrc32(const char* string, u32 length);

StringId internString(const char* string);
const char* lookupString(StringId sid);

extern inline constexpr u32 operator""_sid(const char* str, size_t size)
{
	return hashCrc32(str, size);
}

#if _DEBUG
	#define SID(string) internString(string);
#else
	#define SID(string) StringId(hashCrc32(string));
#endif