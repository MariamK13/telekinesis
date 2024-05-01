#ifndef VECTOR_H_
#define VECTOR_H_

#include <iostream>
#include "myallocator.h"

template <typename T, typename MyAllocator = MyAllocator<T>>
class Vector {
public:
    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = std::size_t;
    using pointer = value_type*;
    using const_pointer = const value_type*;

public:
	class const_iterator {
		friend class Vector<value_type, MyAllocator>;
	private:
		pointer ptr_;
	protected:
		explicit const_iterator(pointer ptr);
	public:
		//default, copy, move ctors, dtor
		const_iterator();
		const_iterator(const const_iterator& lhv);
		const_iterator(const_iterator&& rhv);
		~const_iterator();
		
		const_iterator& operator=(const const_iterator& lhv);
		const_iterator& operator=(const_iterator&& rhv);
		
		const_reference operator*();
		const_pointer operator->();
		
		const_iterator operator+(size_type val) const;
		const_iterator& operator+=(size_type val);
		const_iterator operator-(size_type val) const;
		const_iterator& operator-=(size_type val);
		const_iterator& operator++();
		const_iterator operator++(int);
		const_iterator& operator--();
		const_iterator operator--(int);
		
		const_reference operator[](size_type index) const;
		
		bool operator==(const const_iterator& lhv)const;
		bool operator!=(const const_iterator& lhv)const;
		bool operator<(const const_iterator& lhv)const;
		bool operator>(const const_iterator& lhv)const;
		bool operator<=(const const_iterator& lhv)const;
		bool operator>=(const const_iterator& lhv)const;		
	};
public:
	class iterator : public const_iterator{
	friend class Vector<value_type, MyAllocator>;
		protected:
				explicit iterator(pointer ptr);
		public:

	};

   
  
	Vector ();
	Vector (size_type size);
	Vector (size_type size, value_type val = 0);
	Vector (const Vector& lhv);
	Vector (Vector&& rhv);
	size_type operator[](size_type index);
	Vector operator=(const Vector& lhv);
	Vector operator=(Vector&& rhv);
	void realloc (size_type size);
	void reserve();
	void push_back(value_type val);
	void pop_back();
	size_type Vsize();
	size_type Vcap();
	void print();
	void shrink_to_fit();
	void insert(value_type val, size_type pos);
	void erase(size_type pos);
	reference at(size_type pos);
	void clear();
	bool empty();
	~Vector();
private: 
	size_type m_size;
	size_type m_cap;
	pointer m_ptr;
};

template <typename T, typename MyAllocator>
std::ostream& operator << (std::ostream& out, Vector<T, MyAllocator>& ob);

#include "vector.hpp"

#endif

