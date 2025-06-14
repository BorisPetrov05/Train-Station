#pragma once
#include <iostream>
#include <cstring>
#define _CRT_SECURE_NO_WARNINGS

class String 
{
private:
    char* data;
    size_t length;

    void copyFrom(const String& other) 
    {
        length = other.length;
        data = new char[length + 1];
        std::strcpy(data, other.data);
    }

public:
    String() : data(new char[1] { '\0' }), length(0) {}

    String(const char* str) 
    {
        length = std::strlen(str);
        data = new char[length + 1];
        std::strcpy(data, str);
    }

    String(const String& other) 
    {
        copyFrom(other);
    }

    String& operator=(const String& other) 
    {
        if (this != &other) {
            delete[] data;
            copyFrom(other);
        }
        return *this;
    }

    ~String() 
    {
        delete[] data;
    }

    const char* c_str() const { return data; }
    size_t size() const { return length; }

    bool operator==(const String& other) const 
    {
        return std::strcmp(data, other.data) == 0;
    }

    bool operator!=(const String& other) const 
    {
        return !(*this == other);
    }

    String operator+(const String& other) const 
    {
        size_t newLen = length + other.length;
        char* newData = new char[newLen + 1];
        std::strcpy(newData, data);
        std::strcat(newData, other.data);
        String result(newData);
        delete[] newData;
        return result;
    }

    friend std::ostream& operator<<(std::ostream& os, const String& str) 
    {
        return os << str.data;
    }

    bool empty() const
    {
        return length == 0;
    }
};