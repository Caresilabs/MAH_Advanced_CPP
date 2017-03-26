#pragma once

#include "LinkedList.h"


template<class T>
Link<T>::Link() : next( nullptr ), prev( nullptr ) {
}

template<class T>
T* Link<T>::Next() {
	return dynamic_cast<T*>(next);
}

template<class T>
const T* Link<T>::Next() const {
	return dynamic_cast<T*>(next);
}

template<class T>
T* Link<T>::Prev() {
	return dynamic_cast<T*>(prev);
}

template<class T>
const T* Link<T>::Prev() const {
	return dynamic_cast<T*>(prev);
}

template<class T>
template <class Data>
T* Link<T>::InsertAfter( Data* toInsert ) {
	if ( !toInsert )
		return nullptr;

	T* newNode = new T( toInsert );
	newNode->prev = this;
	newNode->next = next;

	next->prev = newNode;

	next = newNode;
	return newNode;
}

template<class T>
template <class Data>
T* Link<T>::InsertBefore( Data* toInsert ) {
	if ( !toInsert )
		return nullptr;

	T* newNode = new T( toInsert );
	newNode->prev = prev;
	newNode->next = this;

	prev->next = newNode;

	prev = newNode;
	return newNode;
}

template<class T>
template<class Data>
Data* Link<T>::DeleteAfter() {
	auto toDelete = Next();
	if ( toDelete ) {

		next = toDelete->next;
		next->prev = this;

		Data* oldData = toDelete->data;
		delete toDelete;

		return oldData;
	}
	return nullptr;
}

template<class T>
template<class Data>
Data* Link<T>::DeleteBefore() {
	auto toDelete = Prev();
	if ( toDelete ) {

		prev = toDelete->prev;
		prev->next = this;

		Data* oldData = toDelete->data;
		delete toDelete;

		return oldData;
	}
	return nullptr;
}

template<class T>
template <class Data>
T* Link<T>::Find( const Data& searchFor ) {
	for ( auto node = Next(); node; node = node->Next() ) {
		if ( searchFor == **node )
			return node;
	}
	return nullptr;
}

template<class T>
template <class Data>
const T* Link<T>::Find(const Data& searchFor) const {
	for (auto node = Next(); node; node = node->Next()) {
		if (searchFor == **node)
			return node;
	}
	return nullptr;
}




template<class T>
Node<T>::Node( T* data ) : data( data ) {
}


template<class T>
List<T>::List() {
	next = this;
	prev = this;
}

template<class T>
T* List<T>::First() {
	return Next();
}

template<class T>
const T* List<T>::First() const {
	return Next();
}

template<class T>
T* List<T>::Last() {
	return Prev();
}

template<class T>
const T* List<T>::Last() const {
	return Prev();
}

template<class T>
template <class Data>
T* List<T>::InsertFirst( Data* item ) {
	return InsertAfter( item );
}

template<class T>
template <class Data>
T* List<T>::InsertLast( Data* item ) {
	return InsertBefore( item );
}


template<class T>
template <class Data>
Data* List<T>::PopFirst() {
	return DeleteAfter<Data>();
}

template<class T>
template <class Data>
Data* List<T>::PopLast() {
	return DeleteBefore<Data>();
}

template<class T>
std::ostream& List<T>::Print( std::ostream& cout ) {
	for ( auto node = First(); node; node = node->Next() ) {
		node->Print( cout ) << "\n";
	}

	return cout;
}

template<class T>
List<T>::~List() {
	for ( auto node = First(); node; ) {
		delete node->data;
		auto deleteNode = node;
		node = node->Next();
		delete deleteNode;
	}
}
