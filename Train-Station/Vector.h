#pragma once
#include <stdexcept>

template<typename T>
class Vector {
private:
    T* data;
    size_t capacity;
    size_t length;

    void resize(size_t newCapacity) 
    {
        T* newData = new T[newCapacity];
        for (size_t i = 0; i < length; ++i)
            newData[i] = data[i];
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    Vector() : data(new T[4]), capacity(4), length(0) {}

    Vector(const Vector& other) : data(new T[other.capacity]), capacity(other.capacity), length(other.length) 
    {
        for (size_t i = 0; i < length; ++i)
            data[i] = other.data[i];
    }

    Vector& operator=(const Vector& other) 
    {
        if (this != &other) 
        {
            delete[] data;
            capacity = other.capacity;
            length = other.length;
            data = new T[capacity];
            for (size_t i = 0; i < length; ++i)
                data[i] = other.data[i];
        }
        return *this;
    }

    ~Vector() 
    {
        delete[] data;
    }

    void push_back(const T& value) 
    {
        if (length == capacity)
            resize(capacity * 2);
        data[length++] = value;
    }

    void pop_back() {
        if (length > 0) --length;
    }

    T& operator[](size_t index) 
    {
        if (index >= length) throw std::out_of_range("Index out of range");
        return data[index];
    }

    const T& operator[](size_t index) const 
    {
        if (index >= length) throw std::out_of_range("Index out of range");
        return data[index];
    }

    size_t size() const { return length; }
    bool empty() const { return length == 0; }
    void clear() { length = 0; }

    T* begin() { return data; }
    T* end() { return data + length; }
    const T* begin() const { return data; }
    const T* end() const { return data + length; }

    bool contains(const T& value) const 
    {
        for (size_t i = 0; i < length; ++i) 
        {
            if (data[i] == value) return true;
        }
        return false;
    }

    void erase(size_t index) 
    {
        if (index >= length) throw std::out_of_range("Index out of range");
        for (size_t i = index; i < length - 1; ++i)
            data[i] = data[i + 1];
        --length;
    }
};
