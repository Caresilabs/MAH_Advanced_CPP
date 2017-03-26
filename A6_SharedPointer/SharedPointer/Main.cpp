#define _CRTDBG_MAP_ALLOC
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG
//#include <stdlib.h>
//#include <crtdbg.h>

#include <cassert>

#include <iostream>
using std::cout;
using std::cin;

#define VG

#include "SmartPtr.h"
#ifdef VG
#include "WeakPtr.h"
#endif VF

struct C {
	float value;
	C( float value ) :value( value ) { };
};

void TestG() {
	//-	Konstruktor som tar:	
	//	o	inget	G
	//	o	En SharedPtr	G
	//	o	En pekare	G


	SharedPtr<C> sp11;
	assert( !sp11 );
	assert(sp11.Invariant());
	SharedPtr<C> p15( nullptr );
	assert( !p15 );
	assert(p15.Invariant());
	SharedPtr<C> sp12( new C( 12 ) );
	assert( sp12 );
	assert(sp12.Invariant());
	SharedPtr<C> sp13( sp11 );
	assert( !sp13 );

	assert( sp12.Unique() );
	assert(sp12.Invariant());
	SharedPtr<C> sp14( sp12 );
	assert( sp14 );
	assert( !sp12.Unique() );
	assert(sp12.Invariant());


	//-	Destruktor	G
	//It will test itself
	//-	Tilldelning fr�n en	
	//	o	En SharedPtr	G
	sp14 = sp12;
	assert( sp14 );

	sp14 = sp14;
	assert( sp14 );

	//-	J�mf�relse med (== och <)
	SharedPtr<C> sp31( new C( 31 ) );
	//	o	En SharedPtr	G
	assert( sp11 == nullptr );
	assert( sp11 < sp12 );
	assert( !(sp12 < sp11) );
	assert( sp14 == sp12 );
	assert( !(sp14 == sp31) );
	assert( (sp14 < sp31) || (sp31 < sp14) );

	assert(sp11.Invariant());

	//get, * och ->

	SharedPtr<C> sp41( new C( 41 ) );
	SharedPtr<C> sp42( new C( 42 ) );
	assert( (sp41->value) == (sp41.Get()->value) );
	assert( (sp41->value) != (sp42.Get()->value) );
	assert( &(*sp41) == (sp41.Get()) );

	//move
	SharedPtr<C> sp51( std::move( sp41 ) );
	assert( sp51->value == 41 );
	assert( !sp41 );

	sp51.Reset();
	assert( !sp51 );
}


#ifdef VG
void TestVG() {
	//Weak pointer skall ha det som det st�r VG p� nedan
	//-	Konstruktor som tar:		
	//	o	inget	G	VG
	//	o	En SharedPtr	G	VG
	//	o	En WeakPtr	VG	VG

	WeakPtr<C> wp11;
	assert( wp11.Expired() );
	assert(wp11.Invariant());
	SharedPtr<C> sp12( new C( 12 ) );
	WeakPtr<C> wp13( wp11 );
	assert( wp13.Expired() );
	assert(wp13.Invariant());
	WeakPtr<C> wp14( sp12 );
	assert(wp14.Invariant());
	assert( !wp14.Expired() );

	SharedPtr<C> sp17( wp14 );
	assert( sp17 );

	//-	Destruktor	G	VG
	//	It will test itself
	//-	Tilldelning fr�n en		
	//	o	En SharedPtr	G	VG
	//	o	En WeakPtr			VG
	WeakPtr<C> wp15;
	wp14 = wp11;
	assert(wp14.Invariant());
	assert( wp14.Expired() );

	SharedPtr<C> sp33( new C( 33 ) );
	wp14 = sp33;
	assert( !wp14.Expired() );
	wp14 = wp14;
	assert( !wp14.Expired() );
	assert(wp14.Invariant());

	sp33.Reset();
	assert( !sp33 );
	assert( wp14.Expired() );

	//Shared(weak)
	try {
		SharedPtr<C> slask( wp14 );
	} catch ( const char* const except ) {
		assert( except == "std::bad_weak_ptr" );
	}

	//-	funktioner:		
	//	o	lock()		VG
	auto sp51 = wp11.Lock();
	assert( !sp51 );

	SharedPtr<C>  sp55( new C( 55 ) );
	wp14 = sp55;
	sp51 = wp14.Lock();
	assert(wp14.Invariant());
	assert( sp51 );
	////	o	expired()		VG	Redan testat

	//move
	SharedPtr<C> sp61( std::move( sp51 ) );
	assert( sp61->value == 55 );
	assert( !sp51 );

	sp51 = std::move( sp61 );
	sp51 = std::move( sp51 );
	assert( sp51->value == 55 );
}
#endif VG


int main() {
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	std::locale::global( std::locale( "swedish" ) );

	TestG();

#ifdef  VG
	TestVG();
#endif //  VG

	SharedPtr<int> sp(new int(5));
	WeakPtr<int> wp(sp);
	sp.Reset();
	wp.Expired();
	wp.Invariant();
	cin.get();
}

