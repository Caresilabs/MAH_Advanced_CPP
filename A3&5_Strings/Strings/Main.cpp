#include <iostream>
#include "String.h"

#include "StringIttTest.h"

// Simple Test. More in Unit Tests
int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//String str;
	//str = "HelloFooBar";
	//str.Resize(5);
	//str.Resize(8);

	//for ( auto it = str.begin(); it != str.end(); ++it ) {
	//	std::cout << *it;
	//}


	std::locale::global( std::locale( "swedish" ) );

	TestIttInAlg();
	TestRevIttInAlg();
	TestFörGodkäntItt();

	system("PAUSE");
	return 0;
}