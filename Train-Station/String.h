#pragma once
#include <iostream>
#include <cstring>

class String 
{
private:
    char* data;
    size_t length;

    void copyFrom(const String& other);

public:
    String();

    String(const char* str);

    String(const String& other);

    String& operator=(const String& other);

    ~String();

    const char* c_str() const;
    size_t size() const;

    bool operator==(const String& other) const;

    bool operator!=(const String& other) const;

    String operator+(const String& other) const;

    friend std::ostream& operator<<(std::ostream& os, const String& str);

    bool empty() const;
};