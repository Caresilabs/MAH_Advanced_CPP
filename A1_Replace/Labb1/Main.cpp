#include <stdio.h>
#include <iostream>
#include "StringHelper.h"

int main() {
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	const int strSize = 128;

	char str[strSize];
	char search[strSize];
	char replace[strSize];

	while ( true ) {

		printf( "Enter a string:\n" );
		std::cin.getline( str, strSize );

		printf( "Enter a search word:\n" );
		std::cin.getline( search, strSize );

		printf( "Enter a replace word:\n" );
		std::cin.getline( replace, strSize );

		char* resultString = StringHelper().Replace( str, search, replace );

		if ( resultString != nullptr ) {
			printf( "Your new array: %s\n\n", resultString );
			delete[] resultString;
		} else {
			printf( "Your new array: %s\n\n", str );
		}

		printf( "Run again? (y/n)\n" );
		std::cin.getline( str, strSize );

		if ( *str == 'n' ) {
			break;
		}

		printf( "\n" );
	}

	return 0;
}