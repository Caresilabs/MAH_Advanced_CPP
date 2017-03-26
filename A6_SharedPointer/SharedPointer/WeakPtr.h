#pragma once

template <typename T>
class SharedPtr;

template <typename T>
class WeakPtr {
	T*		ptr;
	int*		smartCounter;
	int*		weakCounter;

	void		Release();

public:
	friend class SharedPtr<T>;

	WeakPtr();
	WeakPtr( const WeakPtr& rhs );
	WeakPtr( const SharedPtr<T>& rhs );

	WeakPtr& operator=( const WeakPtr& rhs );
	WeakPtr& operator=( const SharedPtr<T>& rhs );

	SharedPtr<T>		Lock();
	bool				Expired();
	
	bool				Invariant();
	

	~WeakPtr();
};

template<typename T>
inline void WeakPtr<T>::Release() {
	if ( smartCounter ) {
		--*weakCounter;
		if ( *weakCounter == 0 && *smartCounter == 0 ) {
			delete weakCounter;
			delete smartCounter;
		}
	}
	ptr = nullptr;
	smartCounter = nullptr;
	weakCounter = nullptr;
}

template<typename T>
inline WeakPtr<T>::WeakPtr() : ptr( nullptr ), smartCounter( nullptr ), weakCounter( nullptr ) {
}

template<typename T>
inline WeakPtr<T>::WeakPtr( const WeakPtr& rhs ) : ptr( rhs.ptr ), smartCounter( rhs.smartCounter ), weakCounter( rhs.weakCounter ) {
	if ( ptr ) {
		++*weakCounter;
	}
}

template<typename T>
inline WeakPtr<T>::WeakPtr( const SharedPtr<T>& rhs ) : ptr( rhs.ptr ), smartCounter( rhs.smartCounter ), weakCounter( rhs.weakCounter ) {
	if ( ptr ) {
		++*weakCounter;
	}
}

template<typename T>
inline WeakPtr<T>& WeakPtr<T>::operator=( const WeakPtr& rhs ) {
	if ( smartCounter != rhs.smartCounter ) {
		Release();

		ptr = rhs.ptr;
		smartCounter = rhs.smartCounter;
		weakCounter = rhs.weakCounter;

		if ( ptr ) {
			++*weakCounter;
		}
	}
	return *this;
}

template<typename T>
inline WeakPtr<T>& WeakPtr<T>::operator=( const SharedPtr<T>& rhs ) {
	if ( smartCounter != rhs.smartCounter) {
		Release();
		ptr = rhs.ptr;
		smartCounter = rhs.smartCounter;
		weakCounter = rhs.weakCounter;
	}

	if ( ptr ) {
		++*weakCounter;
	}
	return *this;
}

template<typename T>
inline SharedPtr<T> WeakPtr<T>::Lock() {
	return SharedPtr<T>( *this );
}

template<typename T>
inline bool WeakPtr<T>::Expired() {
	return !smartCounter || *smartCounter == 0;
}

template<typename T>
inline bool WeakPtr<T>::Invariant()
{
	return ((ptr && *weakCounter != 0) || (!smartCounter && !weakCounter));
}

template<typename T>
inline WeakPtr<T>::~WeakPtr() {
	Release();
}
