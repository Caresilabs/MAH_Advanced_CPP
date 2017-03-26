#pragma once

#include <iterator>
#include <exception>

template <typename VType, bool Reverse>
class PtrIterator : public std::iterator<std::random_access_iterator_tag, VType> {
protected:
	VType* dataPointer;

public:

	PtrIterator() : dataPointer( nullptr ) {}
	PtrIterator( VType* ptr );

	PtrIterator( const PtrIterator& rhs );
	PtrIterator& operator=( const PtrIterator& rhs );

	VType& operator*() const;
	VType& operator[]( int i ) const;

	PtrIterator& operator--();
	PtrIterator& operator++();

	PtrIterator& operator-=( int i );
	PtrIterator& operator+=( int i );

	PtrIterator operator+( int i ) const;
	PtrIterator operator-( int i ) const;

	PtrIterator operator--( int );
	PtrIterator operator++( int );

	ptrdiff_t operator-( PtrIterator& rIt ) const;
	bool operator==( PtrIterator& rIt ) const;
	bool operator!=( PtrIterator& rIt ) const;
	bool operator<( PtrIterator& rIt ) const;
};


template<typename VType, bool Reverse>
inline PtrIterator<VType, Reverse>::PtrIterator( VType* ptr ) : dataPointer( ptr ) {
	if ( !dataPointer )
		std::exception( "A nullpointer was passed to the iterator." );

	dataPointer = ptr;
}

template<typename VType, bool Reverse>
inline PtrIterator<VType, Reverse>::PtrIterator( const PtrIterator<VType, Reverse>& rhs ) : dataPointer( rhs.dataPointer ) {
}

template<typename VType, bool Reverse>
inline PtrIterator<VType, Reverse>& PtrIterator<VType, Reverse>::operator=( const PtrIterator<VType, Reverse>& rhs ) {
	if ( this != &rhs ) {
		dataPointer = rhs.dataPointer;
	}
	return *this;
}

template<typename VType, bool Reverse>
inline VType& PtrIterator<VType, Reverse>::operator*() const {
	return *dataPointer;
}

template<typename VType, bool Reverse>
inline VType& PtrIterator<VType, Reverse>::operator[]( int i ) const {
	return dataPointer[Reverse ? -i : i];
}

template<typename VType, bool Reverse>
inline PtrIterator<VType, Reverse> PtrIterator<VType, Reverse>::operator+( int i ) const {
	auto copy = *this;
	copy += i;
	return copy;
}

template<typename VType, bool Reverse>
inline PtrIterator<VType, Reverse> PtrIterator<VType, Reverse>::operator-( int i ) const {
	auto copy = *this;
	copy -= i;
	return copy;
}

template<typename VType, bool Reverse>
inline PtrIterator<VType, Reverse>& PtrIterator<VType, Reverse>::operator--() {
	*this -= 1;
	return *this;
}

template<typename VType, bool Reverse>
inline PtrIterator<VType, Reverse>& PtrIterator<VType, Reverse>::operator++() {
	*this += 1;
	return *this;
}

template<typename VType, bool Reverse>
inline PtrIterator<VType, Reverse>& PtrIterator<VType, Reverse>::operator-=( int i ) {
	dataPointer -= Reverse ? -i : i;
	return *this;
}

template<typename VType, bool Reverse>
inline PtrIterator<VType, Reverse>& PtrIterator<VType, Reverse>::operator+=( int i ) {
	dataPointer += Reverse ? -i : i;
	return *this;
}

template<typename VType, bool Reverse>
inline PtrIterator<VType, Reverse> PtrIterator<VType, Reverse>::operator--( int ) {
	auto copy = *this;
	--*this;
	return copy;
}

template<typename VType, bool Reverse>
inline PtrIterator<VType, Reverse> PtrIterator<VType, Reverse>::operator++( int ) {
	auto copy = *this;
	++*this;
	return copy;
}

template<typename VType, bool Reverse>
inline ptrdiff_t PtrIterator<VType, Reverse>::operator-( PtrIterator& rIt ) const {
	return dataPointer - rIt.dataPointer;
}

template<typename VType, bool Reverse>
bool PtrIterator<VType, Reverse>::operator==( PtrIterator<VType, Reverse> & rIt ) const {
	return dataPointer == rIt.dataPointer;
}

template<typename VType, bool Reverse>
bool PtrIterator<VType, Reverse>::operator!=( PtrIterator<VType, Reverse> & rIt ) const {
	return dataPointer != rIt.dataPointer;
}

template<typename VType, bool Reverse>
bool PtrIterator<VType, Reverse>::operator<(  PtrIterator<VType, Reverse> & rIt ) const {
	return Reverse ? (rIt.dataPointer < dataPointer) : (dataPointer < rIt.dataPointer);
}

