#include "String.h"

using namespace Common;

String String::makeCopy(const char* text)
{
	u32 length = strlen(text);
	char* newText = new char[length + 1];
	memcpy(newText, text, length + 1);
	return String(newText);
}

String String::makeCopy(const char* text, u32 length)
{
	char* newText = new char[length + 1];
	memcpy(newText, text, length);
	newText[length] = '\0';
	return String(newText);
}

String String::makeOwner(const char* text)
{
	assert(text != nullptr);
	return String(text);
}

String::String(String&& other) noexcept
	: text_(other.text_)
{
	other.text_ = nullptr;
}

String& String::operator=(String&& other) noexcept
{
	if (this != &other)
	{
		if (this->text_ != nullptr)
			delete this->text_;

		this->text_ = other.text_;
		other.text_ = nullptr;
	}

	return *this;
}

String::~String()
{
	if (this->text_ != nullptr)
		delete this->text_;
}

String String::makeSubstring(u32 start, u32 length) const
{
	return String::makeCopy(&this->text_[start], length);
}

String String::makeSubstringFromAddress(const char* start, u32 length) const
{
	return String::makeCopy(start, length);
}

std::string_view String::view() const
{
	return std::string_view(this->text_);
}

const char* String::findFirst(char toFind) const
{
	const char* current = this->text_;

	while (*current != '\0')
	{
		if (*current == toFind)
		{
			return current;
		}
		else
		{
			current++;
		}
	}

	return nullptr;
}

const char* String::findLast(char toFind) const
{
	const char* current = this->text_ + strlen(this->text_);
	const char* start = this->text_;

	while (current != start)
	{
		if (*current == toFind)
		{
			return current;
		}
		else
		{
			current--;
		}
	}

	return nullptr;
}

bool String::contains(char toFind) const
{
	return findFirst(toFind) != nullptr;
}