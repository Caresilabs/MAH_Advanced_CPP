#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Strings/String.h"


#define Invariant(X) (X.Data()==nullptr || *X.Data() == *X.Data()) && X.Size() >= 0 && X.Size() <= X.Capacity() && X[X.Size()] == '\0'


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{		
	TEST_CLASS(StringTest)
	{
	public:
		
		TEST_METHOD(TestCreateEmpty)
		{
			String myString;

			Assert::AreEqual(myString.Size(), 0);
			Assert::AreEqual(myString.Capacity(), 0);

			Assert::IsTrue(myString[0] == '\0');

			Assert::IsTrue(Invariant(myString));
		}


		TEST_METHOD(TestBasic)
		{
			String myString("Hello _ World !"); //15

			Assert::AreEqual(myString.Size(), 15);
			Assert::AreNotEqual(myString.Capacity(), 0);

			Assert::IsTrue(Invariant(myString));
		}

		TEST_METHOD(TestEqual)
		{
			String myString("Hello there! 2017");
			String myString2("Hello there! 2017");
			String myString3 = myString2;

			Assert::IsTrue(myString == myString2);
			Assert::IsTrue(myString == myString3);

			Assert::IsTrue(Invariant(myString));
		}


		TEST_METHOD(TestNotEqual)
		{
			String myString("Hello there! 2016");
			String myString2("Hello there! 2017");
			String myString3 = myString2;

			Assert::IsFalse(myString == myString2);
			Assert::IsFalse(myString == myString3);

			Assert::IsTrue(Invariant(myString));
		}

		TEST_METHOD(TestOutOfRangeException)
		{
			String myString("Hello there! 2017");
			
			try {
				auto chr = myString.At(17);
				Assert::Fail();
			}
			catch (std::out_of_range& e) {
			
			}

			Assert::IsTrue(Invariant(myString));
		}

		TEST_METHOD(TestConstIndex)
		{
			const String myString("hello world foo!");

			const char& c1 = myString.At(2);
			const char& c2 = myString[3];

			Assert::IsTrue(Invariant(myString));
		}

		TEST_METHOD(TestReserve) 
		{
			String myString("hello world!");
			myString.Reserve(42);

			Assert::IsTrue(myString.Capacity() == 42);

			Assert::IsTrue(Invariant(myString));
		}

		TEST_METHOD(TestShrinkToFit)
		{
			String myString("H");
			myString += "ej";
			myString += " foo";
			myString += " bar";

			myString.ShrinkToFit();

			Assert::IsTrue(myString.Capacity() == myString.Size());

			Assert::IsTrue(Invariant(myString));
		}

		TEST_METHOD(TestPushBack)
		{
			String myString("H");
			myString.PushBack('e');
			myString.PushBack('j');
			myString.PushBack('s');
			myString.PushBack('a');
			myString.PushBack('n');

			Assert::IsTrue(myString == "Hejsan");

			Assert::IsTrue(Invariant(myString));
		}

		TEST_METHOD(TestStringAdd)
		{
			String myString;
			myString = String("Foo") + String("Bar") + "Today";

			Assert::IsTrue(myString == "FooBarToday");

			Assert::IsTrue(Invariant(myString));
		}

		TEST_METHOD(TestResize)
		{
			String myString;
			myString = "HelloFooBar";
			myString.Resize(5);

			Assert::IsTrue(myString == "Hello");

			myString.Resize(8);
			Assert::IsTrue(myString.Size() == 8);

			Assert::IsTrue(Invariant(myString));
		}

		TEST_METHOD(TestPushBackNull)
		{
			String myString;
			myString.PushBack('\0');
			Assert::IsTrue(myString.Size() == 1);

			Assert::IsTrue(Invariant(myString));
		}

		TEST_METHOD(TestStringAddToItself)
		{
			String myString("HelloThere");
			myString += String("Foo") + String("Bar") + "Today";

			Assert::IsTrue(myString == "HelloThereFooBarToday");

			Assert::IsTrue(Invariant(myString));
		}

		TEST_METHOD(TestOllesPushbackReallocation) 
		{
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

			String str("hej");
			Assert::IsTrue(str.Size() <= str.Capacity());


			//If VG we try to take 20 empty places: (size+1 < capacity)
			//we push_back one more until it is more then 20 places left (or sting to big)
			while (str.Size() + 20 >= str.Capacity() && str.Size() < 1000)
				str.PushBack('A' + rand() % 32);
			Assert::IsTrue(str.Size() < 1000);	//If this fail it prbably the case that capacity is increased with a constant.


			auto internalBuf = str.Data();
			auto cap = str.Capacity();
			auto siz = str.Size();
			int i;
			for (i = siz + 1; i <= cap; ++i) {
				str.PushBack(char(i) + 'a');
				Assert::IsTrue(internalBuf == str.Data());
				Assert::IsTrue(cap == str.Capacity());
				Assert::IsTrue(i == str.Size());
			}
			str.PushBack(char(i));
			Assert::IsTrue(internalBuf != str.Data());
			Assert::IsTrue(cap < str.Capacity());
			Assert::IsTrue(i == str.Size());

			Assert::IsTrue(str.Size() != str.Capacity());
			internalBuf = str.Data();
			cap = str.Capacity();
			siz = str.Size();
			str.ShrinkToFit();
			Assert::IsTrue(internalBuf != str.Data());
			Assert::IsTrue(str.Size() == str.Capacity());
			Assert::IsTrue(i == str.Size());

			Assert::IsTrue(Invariant(str));
		}


		TEST_METHOD(TestOllesGodkantString) 
		{
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

			//-	String()
			String str0;
			String str00("");
			Assert::IsTrue(str0 == str00);
			//str0 != str00;
			
			//-	String(Sträng sträng)
			String s1("foo"); Assert::IsTrue(s1 == "foo");
			String str(s1); Assert::IsTrue(str == "foo");
			String s3("bar");  Assert::IsTrue(s3 == "bar");

			//-	~String() Kom ihåg destruktorn!
			delete new String("hej");

			//	-	operator =(Sträng sträng)
			Assert::IsTrue((str = s3) == s3);
			Assert::IsTrue((str = str) == s3);	//self assignment


			String str1("foo"), str2("bar"), str3("hej");
			str3 = str = str1;
			Assert::IsTrue(str3 == str);
			Assert::IsTrue(str1 == str);

			// operator bool

			Assert::IsTrue((bool)String("huj"));
			Assert::IsTrue(!(bool)String(""));

			//-	operator== 
			//testas överallt!


			//-	operator[](int i) som indexerar utan range check.
			str = "bar";
			str[-1]; str[1000];	//No error
			Assert::IsTrue(str[1] == 'a');
			str[1] = 'y';
			Assert::IsTrue(str[1] == 'y');

			const String sc(str);
			Assert::IsTrue(sc[1] == 'y');
			Assert::IsTrue(std::is_const<std::remove_reference< decltype(sc[1])>::type>::value); //Kolla att det blir en const resultat av indexering

																						 //-	push_back(char c) lägger till ett tecken sist.
			str = "bar";
			str.PushBack('a');
			Assert::IsTrue(str == "bara");

			Logger::WriteMessage(String("hej\n").Data());
			Logger::WriteMessage("Om det står hej på föregående rad så är TestFörGodkänt klar\n");
			//cout << String("hej\n");
			//cout << "Om det står hej på föregående rad så är TestFörGodkänt klar\n";

			Assert::IsTrue(Invariant(str));

		}


		TEST_METHOD(TestOllesValGodkantString) 
		{
			String str("bar");

			//-	at(int i) som indexerar med range check
			try {
				str.At(-1);
				Assert::Fail();
			}
			catch (std::out_of_range&) {};
			try {
				str.At(3);
				Assert::Fail();
			}
			catch (std::out_of_range&) {};

			//- at indexerar

			//-	at(int i) 
			str = "bar";
			Assert::IsTrue(str.At(1) == 'a');
			str.At(1) = 'y';
			Assert::IsTrue(str.At(1) == 'y');

			const String strC(str);
			Assert::IsTrue(strC.At(1) == 'y');
			Assert::IsTrue(std::is_const<std::remove_reference< decltype(strC.At(1))>::type>::value); //Kolla att det blir en const resultat av indexering

																							  // ConvertToChars
			const char* temp = strC.Data();
			Assert::IsTrue(strC.Size() == 3);
			Assert::IsTrue(std::memcmp(temp, strC.Data(), strC.Size()) == 0);
			Assert::IsTrue(temp[strC.Size()] == '\0');

			//	reserve()
			auto internalBuf = str.Data();
			auto cap = str.Capacity();
			auto siz = str.Size();

			str.Reserve(cap);
			Assert::IsTrue(internalBuf == str.Data());
			Assert::IsTrue(cap == str.Capacity());
			Assert::IsTrue(siz == str.Size());

			str.Reserve(cap + 1);
			Assert::IsTrue(internalBuf != str.Data());
			Assert::IsTrue(cap + 1 == str.Capacity());
			Assert::IsTrue(siz == str.Size());

			/////////////////
			//-	operator+=(Sträng sträng) som tolkas som konkatenering.
			//foo, bar, hej
			String str1("foo"), str2("bar"), str3("hej");
			((str = "xyz") += str1) += (str3 += str1);
			Assert::IsTrue(str3 == "hejfoo" && str == "xyzfoohejfoo" && str1 == "foo");

			//+= som får plats;
			str = "bar";
			str.Reserve(10);
			str += "foo";
			Assert::IsTrue(str == "barfoo");

			//+= som inte får plats;
			str.Reserve(10);
			str = "";
			int i;
			for (i = 0; str.Size() < str.Capacity(); ++i)
				str.PushBack('0' + i);
			str1 = "bar";
			str += str1;
			for (int k = 0; k < i; ++k)
				Assert::IsTrue(str[k] == '0' + k);
			Assert::IsTrue(str[i] == 'b');
			//+= Själv assignment	//Borde testa med att capacity tar slut!
			str = "foo";
			str += str;
			Assert::IsTrue(str == "foofoo");

			//-	operator+
			str = "bar";
			Assert::IsTrue(str + String("foo") == "barfoo");

			//move
			const char* strdata = str.Data();
			String mStr(std::move(str));
			Assert::IsTrue(strdata == mStr.Data());
			Assert::IsTrue(nullptr == str.Data());

			str = std::move(mStr);
			Assert::IsTrue(strdata == str.Data());
			Assert::IsTrue(nullptr == mStr.Data());

		
			Logger::WriteMessage("\nTestFörVälGodkänt klar\n");
			

			Assert::IsTrue(Invariant(str));
		}

	};
}