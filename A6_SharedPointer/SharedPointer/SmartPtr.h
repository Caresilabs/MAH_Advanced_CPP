#pragma once

#include "WeakPtr.h"

template <typename T>
class SharedPtr {

	typedef WeakPtr<T> __weakPtr;

	T*		ptr;
	int*		smartCounter;
	int*		weakCounter;

	void	Release();

public:
	friend class __weakPtr;

	SharedPtr( T* newPtr = nullptr );
	SharedPtr( const SharedPtr& rhs );
	SharedPtr( SharedPtr&& rhs );
	SharedPtr( const __weakPtr& rhs );

	void			Reset( T* newPtr = nullptr );
	T*			Get();
	bool			Unique();

	bool			Invariant();

	SharedPtr& operator=( const SharedPtr& rhs );
	SharedPtr& operator=( SharedPtr&& rhs );
	SharedPtr& operator=( const __weakPtr& rhs );

	T& operator*();
	T* operator->();

	operator T*() { return ptr; }
	explicit operator bool() { return ptr != nullptr; }

	~SharedPtr();

};

template<typename T>
inline void SharedPtr<T>::Release() {
	if ( ptr ) {
		--*smartCounter;

		if ( *smartCounter == 0 ) {
			delete ptr;

			if ( *weakCounter == 0 ) {
				delete smartCounter;
				delete weakCounter;
			}
		}
	}

	ptr = nullptr;
	smartCounter = nullptr;
	weakCounter = nullptr;
}

template<typename T>
SharedPtr<T>::SharedPtr( T* newPtr ) : ptr( newPtr ), weakCounter( nullptr ), smartCounter( nullptr ) {
	if ( ptr ) {
		smartCounter = new int( 1 );
		weakCounter = new int( 0 );
	}
}

template<typename T>
SharedPtr<T>::SharedPtr( const SharedPtr& rhs ) : ptr( rhs.ptr ), smartCounter( rhs.smartCounter ), weakCounter( rhs.weakCounter ) {
	if ( ptr ) {
		++*smartCounter;
	}
}

template<typename T>
SharedPtr<T>::SharedPtr( SharedPtr&& rhs ) : ptr( nullptr ), smartCounter( nullptr ), weakCounter( nullptr ) {
	std::swap( ptr, rhs.ptr );
	std::swap( smartCounter, rhs.smartCounter );
	std::swap( weakCounter, rhs.weakCounter );
}

template<typename T>
SharedPtr<T>::SharedPtr( const __weakPtr& rhs ) : ptr( rhs.ptr ), smartCounter( rhs.smartCounter ), weakCounter( rhs.weakCounter ) {
	if ( ptr ) {
		if ( *rhs.smartCounter == 0 )
			throw "std::bad_weak_ptr";

		++*smartCounter;
	}
}

template<typename T>
inline void SharedPtr<T>::Reset( T* newPtr ) {
	Release();

	if ( newPtr ) {
		ptr = newPtr;
		smartCounter = new int( 1 );
		weakCounter = new int( 0 );
	}
}

template<typename T>
inline T* SharedPtr<T>::Get() {
	return ptr;
}

template<typename T>
inline bool SharedPtr<T>::Unique() // Bool am i unique
{
	return *smartCounter == 1;
}

template<typename T>
inline bool SharedPtr<T>::Invariant()
{
	return ((ptr && smartCounter && weakCounter) || (!ptr && !smartCounter && !weakCounter));
}

template<typename T>
inline SharedPtr<T>& SharedPtr<T>::operator=( const SharedPtr& rhs ) {
	if ( ptr != rhs.ptr ) {
		Release();

		if ( rhs.ptr ) {
			ptr = rhs.ptr;
			smartCounter = rhs.smartCounter;
			++*smartCounter;
			weakCounter = rhs.weakCounter;
		}
	}

	return *this;
}

template<typename T>
inline SharedPtr<T>& SharedPtr<T>::operator=( SharedPtr&& rhs ) {
	if ( ptr == rhs.ptr )
		return *this;

	Release();

	std::swap( ptr, rhs.ptr );
	std::swap( smartCounter, rhs.smartCounter );
	std::swap( weakCounter, rhs.weakCounter );

	return *this;
}

template<typename T>
inline SharedPtr<T>& SharedPtr<T>::operator=( const __weakPtr& rhs ) {
	if ( ptr == rhs.ptr )
		return *this;

	if ( ptr ) {
		if ( *rhs.smartCounter == 0 )
			throw "std::bad_weak_ptr";

		++*smartCounter;
	}
	return *this;
}

template<typename T>
inline T& SharedPtr<T>::operator*() {
	return *ptr;
}

template<typename T>
inline T* SharedPtr<T>::operator->() {
	return ptr;
}

template<typename T>
inline SharedPtr<T>::~SharedPtr() {
	Release();
}
