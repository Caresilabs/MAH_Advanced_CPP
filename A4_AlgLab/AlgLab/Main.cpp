#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <forward_list>

using namespace std;


template <class T>
void genContainerData( T& v ) {

	iota( std::begin( v ), std::end( v ), rand() % 256 );
	random_shuffle( std::begin( v ), std::end( v ) );
}

template <class T>
void print( T& cont ) {
	for ( auto it = std::begin( cont ); it != std::end( cont ); ++it )
		cout << *it << ' ';

	cout << "\n";
}

void Uppg1() {
	// 1A
	cout << "1A\n";
	vector<int> vecA( 12 );
	genContainerData( vecA );
	print( vecA );
	sort( std::begin( vecA ), std::end( vecA ) );
	print( vecA );
	cout << "\n";

	// 1B
	cout << "1B\n";
	int vecB[12];
	genContainerData( vecB );
	print( vecB );
	sort( std::begin( vecB ), std::end( vecB ) );
	print( vecB );
	cout << "\n";

	// 1C
	cout << "1C\n";
	vector<int> vecC( 12 );
	genContainerData( vecC );
	print( vecC );
	sort( std::rbegin( vecC ), std::rend( vecC ) );
	print( vecC );
	cout << "\n";

	// 1D
	cout << "1D\n";
	int vecD[12];
	genContainerData( vecD );
	print( vecD );
	sort( std::begin( vecD ), std::end( vecD ), []( int i1, int i2 ) { return i2 < i1; } );
	print( vecD );
	cout << "\n";
}

void Uppg2() {
	cout << "\n2A\n";
	vector<int> vecA( 12 );
	genContainerData( vecA );
	print( vecA );

	auto endRemove = remove_if( vecA.begin(), vecA.end(), []( int i ) {  return i % 2 == 0;  } );
	vecA.erase( endRemove, vecA.end() );
	print( vecA );
}

template <class ForwardIterator>
void ForwardSort( ForwardIterator begin, ForwardIterator end ) {
	if ( begin == end )
		return;

	ForwardIterator second = begin; ++second;
	ForwardIterator innerEnd = end;

	for ( auto i = begin; i != end; ++i ) {
		ForwardIterator prev = begin;

		for ( auto j = second; j != innerEnd; ++j ) {
			if ( *j < *prev ) {
				swap( *prev, *j );
			}
			prev = j;
		}
		innerEnd = prev;
	}
}

void Uppg3() {
	cout << "\n3A\n";
	forward_list<int> list( 12 );
	for ( auto it = std::begin( list ); it != std::end( list ); ++it)
		*it = rand() % 256;

	print( list );
	ForwardSort( std::begin( list ), std::end( list ) );
	print( list );
}

int main() {
	srand( (unsigned)time( NULL ) );

	Uppg1();
	Uppg2();
	Uppg3();

	system( "PAUSE" );
	return 0;
}