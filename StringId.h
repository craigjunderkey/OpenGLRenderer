#pragma once
#include <iostream>
#include "Types.h"

struct StringId
{
	static constexpr u32 NONE = 0;

	u32 id = NONE;
	
	StringId(u32 id) : id(id) {}
	StringId() : id(0) {}

	// canonize a conversion from StringId to u32
	constexpr operator u32() const noexcept { return this->id; }

	// formal check for NONE value
	constexpr bool isValid() const noexcept { return this->id != NONE; }
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