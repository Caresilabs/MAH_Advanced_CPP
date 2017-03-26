#pragma once

#include <iterator>
#include <exception>

template <typename IteratorType, typename VType>
class BasePtrIterator : public std::iterator<std::random_access_iterator_tag, VType> {
protected:
	VType* dataPointer;

public:

	BasePtrIterator() : dataPointer( nullptr ) { }
	BasePtrIterator( VType* ptr );
	BasePtrIterator( const IteratorType& rhs );

	IteratorType& operator=( const IteratorType& rhs );

	VType& operator*() const;
	VType& operator[]( int i ) const;

	IteratorType& operator--();
	IteratorType& operator++();

	IteratorType& operator-=( int i );
	IteratorType& operator+=( int i );

	IteratorType operator+( int i ) const;
	IteratorType operator-( int i ) const;

	// Postfix
	IteratorType operator--( int );
	IteratorType operator++( int );

	ptrdiff_t operator-( IteratorType& rIt ) const;
	bool operator==( IteratorType& rIt ) const;
	bool operator!=( IteratorType& rIt ) const;
	bool operator<( IteratorType& rIt ) const;
};


template <typename IteratorType, typename VType>
inline BasePtrIterator<IteratorType, VType>::BasePtrIterator( VType* ptr ) : dataPointer( ptr ) {
	if ( !dataPointer )
		std::exception( "A nullpointer was passed to the iterator." );

	dataPointer = ptr;
}

template <typename IteratorType, typename VType>
inline BasePtrIterator<IteratorType, VType>::BasePtrIterator( const IteratorType& rhs ) : dataPointer( rhs.dataPointer ) {
}

template <typename IteratorType, typename VType>
inline IteratorType& BasePtrIterator<IteratorType, VType>::operator=( const IteratorType& rhs ) {
	if ( this != &rhs ) {
		dataPointer = rhs.dataPointer;
	}
	return *this;
}

template <typename IteratorType, typename VType>
inline VType& BasePtrIterator<IteratorType, VType>::operator*() const {
	return *dataPointer;
}

template <typename IteratorType, typename VType>
inline VType& BasePtrIterator<IteratorType, VType>::operator[]( int i ) const {
	return dataPointer[i];//dataPointer[Reverse ? -i : i];
}

template <typename IteratorType, typename VType>
inline IteratorType BasePtrIterator<IteratorType, VType>::operator+( int i ) const {
	IteratorType copy( dataPointer );
	copy += i;
	return copy;
}

template <typename IteratorType, typename VType>
inline IteratorType BasePtrIterator<IteratorType, VType>::operator-( int i ) const {
	auto copy = *this;
	copy -= i;
	return copy;
}

template <typename IteratorType, typename VType>
inline IteratorType& BasePtrIterator<IteratorType, VType>::operator--() {
	*this -= 1;
	return static_cast<IteratorType&>(*this);
}

template <typename IteratorType, typename VType>
inline IteratorType& BasePtrIterator<IteratorType, VType>::operator++() {
	*this += 1;
	return static_cast<IteratorType&>(*this);
}

template <typename IteratorType, typename VType>
inline IteratorType& BasePtrIterator<IteratorType, VType>::operator-=( int i ) {
	dataPointer -= i;//Reverse ? -i : i;
	return static_cast<IteratorType&>(*this);
}

template <typename IteratorType, typename VType>
inline IteratorType& BasePtrIterator<IteratorType, VType>::operator+=( int i ) {
	dataPointer += i;	//Reverse ? -i : i;
	return static_cast<IteratorType&>(*this);
}

template <typename IteratorType, typename VType>
inline IteratorType BasePtrIterator<IteratorType, VType>::operator--( int ) {
	auto copy = *this;
	--dataPointer;
	return copy;
}

template <typename IteratorType, typename VType>
inline IteratorType BasePtrIterator<IteratorType, VType>::operator++( int ) {
	IteratorType copy( dataPointer );
	++dataPointer;
	return copy;
}

template <typename IteratorType, typename VType>
inline ptrdiff_t BasePtrIterator<IteratorType, VType>::operator-( IteratorType& rIt ) const {
	return abs( dataPointer - rIt.dataPointer );
}

template <typename IteratorType, typename VType>
bool BasePtrIterator<IteratorType, VType>::operator==( IteratorType& rIt ) const {
	return dataPointer == rIt.dataPointer;
}

template <typename IteratorType, typename VType>
bool BasePtrIterator<IteratorType, VType>::operator!=( IteratorType& rIt ) const {
	return dataPointer != rIt.dataPointer;
}

template <typename IteratorType, typename VType>
bool BasePtrIterator<IteratorType, VType>::operator<( IteratorType& rIt ) const {
	return  (dataPointer < rIt.dataPointer); //Reverse ? (rIt.dataPointer < dataPointer) : (dataPointer < rIt.dataPointer);
}

/// REVERSED

template <typename VType>
class PtrIterator : public BasePtrIterator<PtrIterator<VType>, VType> {
public:
	using BasePtrIterator::BasePtrIterator;
};

template <typename VType>
class ReversePtrIterator : public BasePtrIterator<ReversePtrIterator<VType>, VType> {
public:
	using BasePtrIterator::BasePtrIterator;

	using BasePtrIterator::operator-;

	VType& operator[]( int i ) const;

	ReversePtrIterator& operator--();
	ReversePtrIterator& operator++();

	ReversePtrIterator& operator-=( int i );
	ReversePtrIterator& operator+=( int i );

	ReversePtrIterator operator+( int i ) const;
	ReversePtrIterator operator-( int i ) const;

	// Postfix
	ReversePtrIterator operator--( int );
	ReversePtrIterator operator++( int );

	bool operator<( ReversePtrIterator& rIt ) const;

};


template <typename VType>
VType& ReversePtrIterator<VType>::operator[]( int i ) const {
	return dataPointer[-i];
}

template <typename VType>
ReversePtrIterator<VType>& ReversePtrIterator<VType>::operator--() {
	++dataPointer;
	return *this;
}

template <typename VType>
ReversePtrIterator<VType>& ReversePtrIterator<VType>::operator++() {
	--dataPointer;
	return *this;
}

template <typename VType>
ReversePtrIterator<VType>& ReversePtrIterator<VType>::operator-=( int i ) {
	dataPointer += i;
	return *this;
}

template <typename VType>
ReversePtrIterator<VType>& ReversePtrIterator<VType>::operator+=( int i ) {
	dataPointer -= i;
	return *this;
}

template <typename VType>
ReversePtrIterator<VType> ReversePtrIterator<VType>::operator+( int i ) const {
	return ReversePtrIterator<VType>( dataPointer - i );
}

template <typename VType>
ReversePtrIterator<VType> ReversePtrIterator<VType>::operator-( int i ) const {
	return ReversePtrIterator<VType>( dataPointer + i );
}

// Postfix
template <typename VType>
ReversePtrIterator<VType> ReversePtrIterator<VType>::operator--( int ) {
	ReversePtrIterator<VType> copy( dataPointer );
	++dataPointer;
	return copy;
}

template <typename VType>
ReversePtrIterator<VType> ReversePtrIterator<VType>::operator++( int ) {
	ReversePtrIterator<VType> copy( dataPointer );
	--dataPointer;
	return copy;
}

template <typename VType>
bool ReversePtrIterator<VType>::operator<( ReversePtrIterator<VType>& rIt ) const {
	return dataPointer > rIt.dataPointer;
}