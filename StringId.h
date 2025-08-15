#pragma once
#include <iostream>
#include "Types.h"

struct StringId
{
	u32 id;	
	StringId(u32 id) : id(id) {}
};

constexpr u32 hashCrc32(const char* string);
constexpr u32 hashCrc32(const char* string, u32 length);

StringId internString(const char* string);

inline std::ostream& operator<<(std::ostream& os, const StringId& stringId)
{
	os << stringId.id;
	return os;
}

inline bool operator==(StringId first, StringId other)
{
	return first.id == other.id;
}

extern inline constexpr u32 operator""_sid(const char* str, size_t size)
{
	return hashCrc32(str, size);
}

#if _DEBUG
	#define SID(string) internString(string);
#else
	#define SID(string) StringId(hashCrc32(string));
#endif