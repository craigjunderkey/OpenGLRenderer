#include "StringId.h"
#include "CompileTimeCrc.h"
#include "StringIdTable.h"

using namespace Common;

static StringIdTable<const char*> table = StringIdTable<const char*>(100);

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
	StringId sid = StringId(hashCrc32(string));
	table.add(sid, string);
	return sid;
}

const char* lookupString(StringId sid)
{
	const char** string = table.get(sid);
	if (string == nullptr)
		return nullptr;
	else
		return *string;
}