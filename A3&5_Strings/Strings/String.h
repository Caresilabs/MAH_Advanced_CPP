#pragma once

#define _CRTDBG_MAP_ALLOC
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

#include "crtdbg.h"

// TYPE
#define It2


#ifdef It2
#include "StringIterators2.h"
#else
#include "StringIterators.h"
#endif // It2

class String
{
private:
	const float growFactor = 1.75f;

	char* data;
	unsigned int capacity;
	unsigned int length;

	String(size_t reserve);

	inline void MakeSpaceAndCopy(const char* src, size_t len, size_t cap);
	
	inline void swap(String& rhs);

public:

#ifdef It2
	typedef PtrIterator<char>				iterator;
	typedef ReversePtrIterator<char>			reverse_iterator;
	typedef PtrIterator<const char>			const_iterator;
	typedef ReversePtrIterator<const char>	const_reverse_iterator;
#else
	typedef PtrIterator<char, false>			iterator;
	typedef PtrIterator<char, true>			reverse_iterator;
	typedef PtrIterator<const char, false>	const_iterator;
	typedef PtrIterator<const char, true>	const_reverse_iterator;
#endif // It2

	String();
	String(const String& rhs);
	String(String&& rhs);
	String(const char* cstr);

	String& operator=(const String& rhs);
	String& operator=(String&& rhs);
	String& operator=(const char* cstr);
	String& operator=(char ch);

	char& At(size_t i);
	const char& At(size_t i) const;

	inline char& operator[](size_t i);
	inline const char& operator[](size_t i) const;

	inline void PushBack(char c);

	void ShrinkToFit();
	void Reserve(size_t size);
	void Resize(size_t n);
	
	int Capacity() const;
	int Size() const;
	const char* Data() const;

	iterator begin();
	iterator end();

	const_iterator cbegin() const;
	const_iterator cend() const;

	reverse_iterator rbegin();
	reverse_iterator rend();

	const_reverse_iterator crbegin() const;
	const_reverse_iterator crend() const;

	String& operator+=(const String& other);
	String& operator+=(const char* cstr);

	explicit operator bool();

	friend String operator+(const String& lhs, const String& rhs);
	friend bool operator==(const String& lhs, const String& rhs);

	friend std::ostream& operator<<( std::ostream& cout, const String& str ) {
		cout << str.Data();
		return cout;
	}

	~String();
};

char& String::operator[](size_t i)
{
	return data[i];
}

const char& String::operator[](size_t i) const
{
	return data[i];
}

void String::PushBack(char c)
{
	
	if (length == capacity)
		MakeSpaceAndCopy(data, length, (length + 1) * growFactor); // Grow

	data[length] = c;
	++length;
	data[length] = '\0';
}


