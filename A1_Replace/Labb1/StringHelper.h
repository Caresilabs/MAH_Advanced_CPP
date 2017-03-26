#pragma once

#include <crtdbg.h>

#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif

class StringHelper {
public:
	StringHelper() = default;

	char* Replace( const char* str, const char* searchFor, const char* changeTo );

	int StringLength( const char* str );

	int Count( const char* str, const char* searchFor );

};

