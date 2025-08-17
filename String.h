#pragma once
#include <cstring>
#include <iostream>
#include <string_view>
#include "Types.h"

namespace Common
{
	class String
	{
	public:
		// TODO: allocate this memory in some special pool for strings
		static String makeCopy(const char* text);
		static String makeCopy(const char* text, u32 length);
		static String makeOwner(const char* text);

		String(String&& other) noexcept;
		String& operator=(String&& other) noexcept;
		
		~String();

		const char* data() { return this->text_; }
		u32 length() const { return strlen(this->text_); }

		String(const String& other) = delete;
		String& operator=(const String& other) = delete;

		String makeSubstring(u32 start, u32 length) const;
		String makeSubstringFromAddress(const char* start, u32 length) const;
		std::string_view view() const;
		const char* findFirst(char toFind) const;
		const char* findLast(char toFind) const;
		bool contains(char toFind) const;

		friend std::ostream& operator<<(std::ostream& os, const String& string);

	private:
		const char* text_;
		
		String(const char* text)
		{
			this->text_ = text;
		}
	};

	inline std::ostream& operator<<(std::ostream& os, const String& string)
	{
		os << string.text_;
		return os;
	}
}
