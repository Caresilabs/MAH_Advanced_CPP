#pragma once

#include <crtdbg.h>
#include <ostream>
#include <assert.h>

#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif

// Forward Declaration
template <class T> class List;

template <class T>
class Link {
private:
	friend class List<T>;
	Link* next;
	Link* prev;

	virtual std::ostream& Print( std::ostream& cout ) const { return cout; }

public:
	Link();

	Link( const Link& ) = delete;
	Link& operator=( const Link& ) = delete;

	T* Next();
	const T* Next() const;

	T* Prev();
	const T* Prev() const;

	template <class Data>
	T* InsertAfter( Data* toInsert );

	template <class Data>
	T* InsertBefore( Data* toInsert );
	
	template<class Data>
	Data* DeleteAfter();

	template<class Data>
	Data* DeleteBefore();

	template <class Data>
	T* Find( const Data& searchFor );

	template <class Data>
	const T* Find(const Data& searchFor) const;

	virtual ~Link() = default;
};

template <class T>
class Node : public Link<Node<T>> {
public:

	Node( T* data );

	Node( const Node& ) = delete;
	Node& operator=( const Node& ) = delete;

	T* const data;

	const T& operator*() const { return *data; }

	virtual std::ostream& Print( std::ostream& cout ) const { cout << *data; return cout; }

};

template <class T>
class List : public Link<T> {

private:
	std::ostream& Print( std::ostream& cout );

public:
	List();

	List( const List& ) = delete;
	List& operator=( const List& ) = delete;

	T* First();
	const T* First() const;

	T* Last();
	const T* Last() const;

	template <class Data>
	T* InsertFirst( Data* item );

	template <class Data>
	T* InsertLast( Data* item );

	template <class Data>
	Data* PopFirst();

	template <class Data>
	Data* PopLast();

	friend std::ostream& operator<<( std::ostream& cout, List& list ) {
		return list.Print( cout );
	}

	~List();

};
