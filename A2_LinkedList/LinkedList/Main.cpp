#include "LinkedList.hpp"

#include <iostream>

int main() {
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	List<Node<float>> list;

	list.InsertFirst( new float( 2 ) );
	list.InsertFirst( new float( 3 ) );
	list.InsertLast( new float( 4 ) );
	list.InsertLast( new float( 5 ) );

	const List<Node<float>>& listConst = list;

	list.Find(2.0)->InsertAfter(new float(19.f));
	auto a = listConst.Find(1.f)->data;// ->InsertAfter(new float(19.f));



	for ( auto n = list.First(); n; n = n->Next() ) {
		std::cout << **n << " ";
	}
	std::cout << "\n\n";

	std::cout << list;


	system( "PAUSE" );
	return 0;
}
