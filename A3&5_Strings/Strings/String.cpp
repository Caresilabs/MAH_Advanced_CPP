#include "String.h"
#include <string.h>
#include <stdexcept>
#include <memory>


// ==== Private ==== //

String::String(size_t reserve) : data(nullptr) 
{
	MakeSpaceAndCopy('\0', 0, reserve);
}

void String::MakeSpaceAndCopy(const char* src, size_t len, size_t cap)
{
	char* oldData = data;

	char* tempData = new char[cap + 1];

	memcpy(tempData, src, len);
	tempData[len] = '\0';
	// Set All unused to \0 --- memset(tempData + len, '\0', (cap - len) + 1);

	// Set members
	data = tempData;
	capacity = cap;
	length = len;

	// Delete old char array.
	if (oldData)
		delete[] oldData;
	
}

void String::swap(String& rhs)
{
	std::swap(data, rhs.data);
	std::swap( length, rhs.length );
	std::swap( capacity, rhs.capacity );
}


// ==== Public ==== //

String::String() : data(nullptr)
{
	MakeSpaceAndCopy('\0', 0, 0);
}

String::String(const String& rhs) : data(nullptr)
{
	MakeSpaceAndCopy(rhs.data, rhs.length, rhs.capacity);
}

String::String(String&& rhs) : data(nullptr) 
{
	swap(rhs);
}

String::String(const char* cstr) : data(nullptr)
{
	int len = strlen(cstr);
	MakeSpaceAndCopy(cstr, len, len);
}

String& String::operator=(const String& rhs)
{
	if (this == &rhs)
		return *this;

	if (capacity == 0 || rhs.length > capacity)
	{
		MakeSpaceAndCopy(rhs.data, rhs.length, rhs.capacity);
	}
	else
	{
		memcpy(data, rhs.data, rhs.length);
		length = rhs.length;
		data[length] = '\0';
	}

	return *this;
}

String& String::operator=(const char* cstr)
{
	int len = strlen(cstr);

	if (capacity == 0 || len > capacity)
	{
		MakeSpaceAndCopy(cstr, len, len);
	}
	else
	{
		memcpy(data, cstr, len);
		length = len;
		data[length] = '\0';
	}

	return *this;
}

String& String::operator=(String&& rhs)
{
	swap(rhs);

	delete[] rhs.data;
	rhs.length = 0;
	rhs.capacity = 0;
	rhs.data = nullptr;

	return *this;
}

String& String::operator=(char ch)
{
	if ( capacity == 0 ) 
	{
		MakeSpaceAndCopy( &ch, 1, 1 );
	}
	else 		
	{
		length = 1;
		data[0] = ch;
		data[length] = '\0';
	}

	return *this;
}

char& String::At(size_t i)
{
	if (i < length) 
		return data[i];
	else 
		throw std::out_of_range("The character is out of range!");
}

const char& String::At(size_t i) const
{
	if (i < length)
		return data[i];
	else
		throw std::out_of_range("The character is out of range!");
}

const char* String::Data() const
{
	return data;
}

int String::Size() const
{
	return length;
}

void String::Reserve(size_t size)
{
	if (size > capacity) 
		MakeSpaceAndCopy(data, length, size);
}

void String::Resize(size_t size)
{
	if (size == length)
		return;

	if (size <= capacity) 
	{
		if (size < length)
			memset(data + size, '\0',1);
		else
			memset(data + size, '\0', (size - length) + 1);
	}
	else
	{
		MakeSpaceAndCopy(data, length, size);
		memset(data + length, '\0', (size - length) + 1);
	}

	length = size;
}

int String::Capacity() const
{
	return capacity;
}

void String::ShrinkToFit()
{
	MakeSpaceAndCopy(data, length, length);
}

String::iterator String::begin() 
{
	return iterator( data );
}

String::iterator String::end()
{
	return iterator( data + length );
}

String::const_iterator String::cbegin() const
{
	return const_iterator( data );
}

String::const_iterator String::cend() const
{
	return const_iterator( data + length );
}

String::reverse_iterator String::rbegin()
{
	return reverse_iterator( data + length - 1);
}

String::reverse_iterator String::rend()
{ 
	return reverse_iterator( data - 1 );
}

String::const_reverse_iterator String::crbegin() const
{ 
	return const_reverse_iterator( data + length - 1 ); 
}

String::const_reverse_iterator String::crend() const
{ 
	return const_reverse_iterator( data - 1 ); 
}

String& String::operator+=(const String& other)
{
	if (length + other.length > capacity) 
	{
		MakeSpaceAndCopy(data, length, (length + other.length) * growFactor);
	}

	memcpy(data + length, other.data, other.length);
	length += other.length;
	data[length] = '\0';
	return *this;
}

String& String::operator+=(const char* cstr)
{
	int len = strlen(cstr);

	if (length + len > capacity) 
	{
		MakeSpaceAndCopy(data, length, (length + len) * growFactor);
	}

	memcpy(data + length, cstr, len);
	length += len;
	data[length] = '\0';
	return *this;
}

String::operator bool()
{
	return length != 0;
}

String operator+(const String& lhs, const String& rhs)
{
	String str(lhs.length + rhs.length);
	str += lhs;
	str += rhs;
	return str;
}

bool operator==(const String& lhs, const String& rhs)
{
	if (lhs.length != rhs.length)
		return false;

	char* ptr1 = lhs.data;
	char* ptr2 = rhs.data;

	for (int i = 0; i < lhs.length; ++i) 
	{
		if (ptr1[i] != ptr2[i])
			return false;
	}

	return true;
}

String::~String()
{
	delete[] data;
}
