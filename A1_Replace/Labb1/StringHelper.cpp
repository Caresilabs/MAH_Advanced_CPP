#include "StringHelper.h"

char* StringHelper::Replace( const char* str, const char* searchFor, const char* changeTo ) {
	
	// 1. Find String length
	int strLength = StringLength( str );
	int searchForLength = StringLength( searchFor );
	int changeToLength = StringLength( changeTo );

	if ( searchForLength == 0 )
		return nullptr;

	// 2. Find the number of occourances of @searchFor in @str
	int foundCount = Count( str, searchFor );

	// 3. Find the new size and init the array
	int newSize = strLength + foundCount * (changeToLength - searchForLength);
	char* result = new char[newSize + 1];
	result[newSize] = '\0';


	const char* searchIterator = searchFor;
	char* resultIterator = result;
	char* foundPointer = nullptr;

	// 4. Loop thorugh the old string and fill it into the new array
	for ( const char* i = str; *i != '\0'; ++i ) {
		
		// Fill the new array.
		if ( *resultIterator  != '\0' )
			*(resultIterator++) = *i;

		if ( *searchIterator == *i ) {
			if ( foundPointer == nullptr )
				foundPointer = resultIterator - 1;

			// Keep searching if the search still matches the string sequence.
			++searchIterator;
		} else {
			// Reset search if we don't find a match.
			searchIterator = searchFor;
		}

		if ( *(searchIterator) == '\0' ) {
			// We found a FULL match!

			// Reset result to new end
			resultIterator = foundPointer + changeToLength;

			// Replace
			const char* replaceIterator = changeTo;
			for ( int j = 0; j < changeToLength; ++j ) {
				*(foundPointer++) = *(replaceIterator++);
			}

			// Reset
			searchIterator = searchFor;
			foundPointer = nullptr;

		}
	}

	return result;
}

int StringHelper::StringLength( const char* str ) {
	int length = 0;
	for ( const char* i = str; *i != '\0'; ++i )
		++length;

	return length;
}

int StringHelper::Count( const char* str, const char* searchFor ) {
	int count = 0;

	const char* searchIterator = searchFor;
	for ( ; *str != '\0'; ++str ) {

		if ( *searchIterator == *str ) {
			// Keep searching if the search still matches the string sequence.
			++searchIterator;
		} else {
			// Reset search if we don't find a match.
			searchIterator = searchFor;
		}

		if ( *(searchIterator) == '\0' ) {
			// If the string is ended, add one to counter.
			searchIterator = searchFor;
			++count;
		} 

	}

	return count;
}
