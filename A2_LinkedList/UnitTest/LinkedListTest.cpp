#include "stdafx.h"

#include "CppUnitTest.h"
#include "../LinkedList/LinkedList.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
	TEST_CLASS( LinkedListTest ) {
public:

	TEST_METHOD( TestInsertLast ) {

		float answers[] = { 4, 8, 16, 14 };

		List<Node<float>> list;
		list.InsertLast( new float( 4 ) );
		list.InsertLast( new float( 8 ) );
		list.InsertLast( new float( 16 ) );
		list.InsertLast( new float( 14 ) );

		auto node = list.First();
		for ( int i = 0; i < 4; ++i ) {
			const float& t = **node;
			Assert::AreEqual( t, answers[i] );
			node = node->Next();
		}

	}

	TEST_METHOD( TestInsertFirst ) {

		float answers[] = { 20, -1, 15, 100 };

		List<Node<float>> list;
		list.InsertFirst( new float( 100 ) );
		list.InsertFirst( new float( 15 ) );
		list.InsertFirst( new float( -1 ) );
		list.InsertFirst( new float( 20 ) );

		auto node = list.First();
		for ( int i = 0; i < 4; ++i ) {
			const float& t = **node;
			Assert::AreEqual( t, answers[i] );
			node = node->Next();
		}

	}

	TEST_METHOD( TestInsertFirstAndLast ) {

		float answers[] = { 7, 2, 30, 22, 42 };

		List<Node<float>> list;
		list.InsertLast( new float( 30 ) );
		list.InsertFirst( new float( 2 ) );
		list.InsertFirst( new float( 7 ) );
		list.InsertLast( new float( 22 ) );
		list.InsertLast( new float( 42 ) );

		auto node = list.First();
		for ( int i = 0; i < 5; ++i ) {
			const float& t = **node;
			Assert::AreEqual( t, answers[i] );
			node = node->Next();
		}

	}


	TEST_METHOD( TestReverseTraversal ) {

		float answers[] = { 22, 30, 2, 7 };

		List<Node<float>> list;
		list.InsertLast( new float( 30 ) );
		list.InsertFirst( new float( 2 ) );
		list.InsertFirst( new float( 7 ) );
		list.InsertLast( new float( 22 ) );

		int i = 0;
		for ( auto n = list.Last(); n; n = n->Prev() ) {
			Assert::AreEqual( **n, answers[i] );
			++i;
		}

	}

	TEST_METHOD( TestInsertNull ) {

		List<Node<float>> list;
		float* noData = nullptr;

		list.InsertLast( noData );
		list.InsertFirst( noData );

		auto node = list.First();
		Assert::IsFalse( node );

		node = list.Last();
		Assert::IsFalse( node );


	}


	TEST_METHOD( TestConstReverseTraversal ) {

		float answers[] = { 22, 30, 2, 7 };

		List<Node<float>> list;
		list.InsertLast( new float( 30 ) );
		list.InsertFirst( new float( 2 ) );
		list.InsertFirst( new float( 7 ) );
		list.InsertLast( new float( 22 ) );

		const List<Node<float>>& cList = list;

		int i = 0;
		for ( auto n = cList.Last(); n; n = n->Prev() ) {
			Assert::AreEqual( **n, answers[i] );
			++i;
		}

	}

	TEST_METHOD( TestPopLast ) {

		List<Node<float>> list;
		list.InsertLast( new float( 42 ) );
		list.InsertFirst( new float( 11 ) );
		list.InsertFirst( new float( 1002 ) );
		list.InsertLast( new float( 52 ) );

		float* data = list.PopLast<float>();
		Assert::AreEqual( *data, 52.f );

		delete data;
	}

	TEST_METHOD( TestPopFirst ) {

		List<Node<float>> list;
		list.InsertLast( new float( 52 ) );
		list.InsertFirst( new float( 21 ) );
		list.InsertFirst( new float( 1602 ) );
		list.InsertLast( new float( 1290 ) );

		float* data = list.PopFirst<float>();
		Assert::AreEqual( *data, 1602.f );

		delete data;
	}

	TEST_METHOD( TestPopMiddle ) {

		List<Node<float>> list;

		// -52 574 512 12
		list.InsertLast( new float( 512 ) );
		list.InsertFirst( new float( 574 ) );
		list.InsertLast( new float( 12 ) );
		list.InsertFirst( new float( -52 ) );
		list.InsertLast( new float( 1252 ) );

		for ( auto n = list.Last(); n; n = n->Prev() ) {
			if ( **n == 574 ) {
				float* data = n->DeleteAfter<float>();

				Assert::IsTrue( data );
				Assert::AreEqual( *data, 512.f );
				delete data;
			}
		}

	}

	TEST_METHOD( TestDeleteEmpty ) {

		List<Node<float>> list;

		auto node = list.PopFirst<float>();
		Assert::IsNull( node );

		node = list.PopLast<float>();
		Assert::IsNull( node );
	}

	TEST_METHOD( TestFind ) {

		List<Node<float>> list;

		// -52 574 512 12
		list.InsertLast( new float( 512 ) );
		list.InsertFirst( new float( 574 ) );
		list.InsertLast( new float( 325 ) );
		list.InsertLast( new float( -52 ) );
		list.InsertLast( new float( 1252 ) );

		const Node<float>* data = list.Find( 325.f );

		// Null check
		Assert::IsTrue( data );

		Assert::AreEqual( 325.f, **data );

	}

	TEST_METHOD( TestOllesCheck ) {

		List<Node<float>> list;

		list.InsertLast( new float( 125 ) );
		list.InsertFirst( new float( -15 ) );
		list.InsertLast( new float( 25 ) );
		list.InsertFirst( new float( -2 ) );
		list.InsertLast( new float( 1222 ) );
		list.InsertFirst( new float( -124 ) );
		list.InsertFirst( new float( 42 ) );

		const Node<float>* node = list.First(), *nextNode = node->Next();
		do {
			Assert::IsTrue( node->Next() == nextNode && nextNode->Prev() == node );

			node = nextNode;
			nextNode = nextNode->Next();

		} while ( node && nextNode );
	}

	TEST_METHOD( TestOllesTest ) {

		List<Node<float>> myList;
		myList.InsertFirst( new float( 5 ) );
		myList.InsertFirst( new float( 4 ) );

		const Node<float>* node3 = myList.InsertFirst( new float( 3 ) );
		myList.InsertFirst( new float( 2 ) );
		myList.InsertFirst( new float( 1 ) );
		myList.InsertFirst( new float( 5 ) );
		myList.InsertFirst( new float( 4 ) );
		myList.InsertFirst( new float( 3 ) );
		myList.InsertFirst( new float( 2 ) );
		myList.InsertFirst( new float( 1 ) );

		node3->Next();
		Node<float>* temp2 = myList.Find<float>( 2 );
		Node<float>* temp3 = temp2->Find<float>( 1 );
		
		float* temp5 = temp3->DeleteAfter<float>();   //ta bort andra 2:an
		Assert::AreEqual( *temp5, 2.f );
		delete temp5;

		Node<float>* tmpx = myList.Find( 5 );
		delete tmpx->DeleteAfter<float>();

		tmpx = myList.Find( 3 );
		tmpx = tmpx->Find( 3 );
		tmpx->InsertBefore( new float( 2.f ) )->InsertBefore( new float( 1.f ) );

		float* ptr;
		Assert::AreEqual( *(ptr = myList.PopFirst<float>()), 1.f );
		delete ptr;

		Assert::AreEqual( *(ptr = myList.PopFirst<float>()), 2.f );
		delete ptr;

		Assert::AreEqual( *(ptr = myList.PopFirst<float>()), 3.f );
		delete ptr;

		Assert::AreEqual( *(ptr = myList.PopFirst<float>()), 4.f );
		delete ptr;

		Assert::AreEqual( *(ptr = myList.PopFirst<float>()), 5.f );
		delete ptr;

		Assert::AreEqual( *(ptr = myList.PopFirst<float>()), 1.f );
		delete ptr;

		Assert::AreEqual( *(ptr = myList.PopFirst<float>()), 2.f );
		delete ptr;

		Assert::AreEqual( *(ptr = myList.PopFirst<float>()), 3.f );
		delete ptr;

		Assert::AreEqual( *(ptr = myList.PopFirst<float>()), 4.f );
		delete ptr;

		Assert::AreEqual( *(ptr = myList.PopFirst<float>()), 5.f );
		delete ptr;

		Assert::IsNull( myList.PopFirst<float>() );
		Assert::IsNull( myList.PopFirst<float>() );

	}

	};
}