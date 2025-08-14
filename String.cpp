#include "String.h"

using namespace Common;

String String::substring(u32 start, u32 length) const
{
	return String(&this->text[start], length);
}