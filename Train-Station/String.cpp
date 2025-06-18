#include "String.h"
#pragma warning(disable:4996)

void String::copyFrom(const String& other)
{
    length = other.length;
    data = new char[length + 1];
    std::strcpy(data, other.data);
}

String::String() : data(new char[1] { '\0' }), length(0) {}

String::String(const char* str)
{
    if (str == nullptr)
    {
        length = 0;
        data = new char[1];
        data[0] = '\0';
    }
    else
    {
        length = std::strlen(str);
        data = new char[length + 1];
        std::strcpy(data, str);
    }
}

String::String(const String& other)
{
    copyFrom(other);
}

String& String::operator=(const String& other)
{
    if (this != &other)
    {
        delete[] data;
        copyFrom(other);
    }
    return *this;
}

String::~String()
{
    delete[] data;
}

const char* String::c_str() const { return data; }

size_t String::size() const { return length; }

bool String::operator==(const String& other) const
{
    return std::strcmp(data, other.data) == 0;
}

bool String::operator!=(const String& other) const
{
    return !(*this == other);
}

String String::operator+(const String& other) const
{
    size_t newLen = length + other.length;
    String result;
    delete[] result.data;
    result.length = newLen;
    result.data = new char[newLen + 1];
    std::strcpy(result.data, data);
    std::strcat(result.data, other.data);
    return result;
}

bool String::empty() const
{
    return length == 0;
}

std::ostream& operator<<(std::ostream& os, const String& str)
{
    return os << str.data;
}
