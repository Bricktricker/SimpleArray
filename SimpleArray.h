#ifndef SIMPLE_ARRAY_H
#define SIMPLE_ARRAY_H

#include <stdexcept> //size_t, std::out_of_range
#include <iterator> // std::iterator, std::input_iterator_tag
#include <algorithm> //std::copy

namespace ph{

template<class T>
class SimpleArray{
public:
    //Iterator
    class Iterator : public std::iterator<std::input_iterator_tag, T>{
    public:
	Iterator(T* x) :p(x) {}
  	Iterator(const Iterator& mit) : p(mit.p) {}
  	Iterator& operator++() {++p;return *this;}
  	Iterator operator++(int) {Iterator tmp(*this); operator++(); return tmp;}
  	bool operator==(const Iterator& rhs) const {return p==rhs.p;}
  	bool operator!=(const Iterator& rhs) const {return p!=rhs.p;}
  	T& operator*() {return *p;}
    private:
	T* p;
    };
	
    //Constructor
    explicit SimpleArray(const size_t size)
    : m_size(size), m_data(nullptr)
    {
	if(size > 0)
             m_data = new T[size];
    }
	
    //Copy Constructor
    SimpleArray(const SimpleArray& arr)
    : m_size(arr.m_size)
    {
	m_data = new T[m_size];
	std::copy(arr.m_data, arr.m_data + m_size, m_data);
    }
	
     //Assignment operator
     SimpleArray& operator=(SimpleArray other){
	swap(*this, other);
	return *this;
     }

     //move Constructor
     SimpleArray(SimpleArray&& other)
	:SimpleArray()
     {
	swap(*this, other);
     };
    
    //Destructor
    ~SimpleArray(){
        delete[] m_data;
    }

    //Element access
    T& at(const size_t pos){
        if(pos < m_size){
            return m_data[pos];
        }
        throw std::out_of_range("SimpleArray out of Range");
    }

    const T& at(const size_t pos) const {
        if(pos < m_size){
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
	
    T* data() noexcept {
        return m_data;
    }

    const T* data() const noexcept {
        return m_data;
    }

    //Capacity
    const size_t size() const noexcept {
        return m_size;
    }

    const bool empty() const noexcept {
        return m_size == 0;
    }
    
    constexpr size_t max_size() const noexcept {
	return ~(0U);
    }
	
    //Iteratoren
    Iterator begin() noexcept {
	return Iterator(m_data);
    }

    const Iterator begin() const noexcept {
	return Iterator(m_data);
    }

    Iterator end() noexcept {
        return Iterator(m_data + m_size);
    }

    const Iterator end() const noexcept {
        return Iterator(m_data + m_size);
    }
	
     //Modifieres
     //from: https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom
     friend void swap(SimpleArray& first, SimpleArray& second){
	     using std::swap;
	     swap(first.m_size, second.m_size);
	     swap(first.m_data, second.m_data);
     }
	
    void fill(const T& val){
        using std::fill;
        std::fill(begin(), end(), val);
    }

private:
    size_t m_size;
    T* m_data;
};

}

#endif
