#ifndef SIMPLE_ARRAY_H
#define SIMPLE_ARRAY_H

#include <stdexcept> //size_t, std::out_of_range
#include <iterator> // std::iterator, std::input_iterator_tag

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
        m_data = new T[size];
    }
	
    //Copy Constructor
    SimpleArray(const SimpleArray& arr)
    : m_size(arr.m_size)
    {
	m_data = new T[m_size];
	//Memory copy
    }
    
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

    //Capacity
    const size_t size() const noexcept {
        return m_size;
    }

    const bool empty() const noexcept {
        return m_size == 0;
    }
    
    constexpr size_t max_size() noexcept {
		return ~(0U);
    }
	
    //Iteratoren
    Iterator begin() noexcept {
	return Iterator(m_data);
    }

    const Iterator begin() const noexcept {
	return Iterator(m_data);
    }

private:
    size_t m_size;
    T* m_data;
};

}

#endif
