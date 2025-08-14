#pragma once
#include <cstring>
#include <iostream>
#include "Types.h"

namespace Common
{
	struct String
	{
		const char* text;

		// TODO: allocate this memory in some special pool for strings
		String(const char* text)
		{
			u32 length = strlen(text);
			char* newText = new char[length + 1];
			memcpy(newText, text, length + 1);
			this->text = newText;
		}

		String(const char* text, u32 length)
		{
			char* newText = new char[length + 1];
			memcpy(newText, text, length);
			newText[length] = '\0';
			this->text = newText;
		}

		String(String&& other) noexcept
			: text(other.text)
		{
			other.text = nullptr;
		}
		
		~String()
		{
			if (this->text != nullptr)
				delete this->text;
		}

		String operator=(String) = delete;

		String substring(u32 start, u32 length) const;
	};

	inline std::ostream& operator<<(std::ostream& os, const String& string)
	{
		os << string.text;
		return os;
	}
}
