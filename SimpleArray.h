#ifndef SIMPLE_ARRAY_H
#define SIMPLE_ARRAY_H

#include <cstddef>
#include <cstring>
#include <stdexcept>

namespace ph{

template<class T>
class SimpleArray{
public:
    explicit SimpleArray(const size_t _size)
    : m_size(_size), m_data(nullptr)
    {
        m_data = new T[_size];
        memset(m_data, 0, _size * sizeof(T));
    }

    ~SimpleArray(){
        delete[] m_data;
    }

    T& at(const size_t pos){
        if(pos &lt; size){
            return m_data[pos];
        }
        throw std::out_of_range("SimpleArray out of Range");
    }

    const T& at(const size_t pos) const {
        if(pos &lt; m_size){
            return m_data[pos];
        }
        throw std::out_of_range("SimpleArray out of Range");
    }

    T& operator[] (const size_t pos){
        return m_data[pos];
    }

    const T& operator[] (const size_t pos) const {
        return m_data[pos];
    }

    T& front() {
        return m_data[0];
    }

    const T& front() const {
        return m_data[0];
    }

    T& back() {
        return m_data[m_size - 1];
    }

    const T& back() const {
        return m_data[m_size - 1];
    }

    const size_t size() const noexcept {
        return m_size;
    }

    const bool empty() const noexcept {
        return m_size == 0;
    }

private:
    size_t m_size;
    T* m_data;
};


  
}

#endif
