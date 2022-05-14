#include "pch.h"
#include "CppUnitTest.h"
#include "../Hashtable/biblio.h"
#include "../Hashtable/biblio.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace UnitTestHashtable
{
	TEST_CLASS(UnitTestHashtable)
	{
	public:

		TEST_METHOD(TestF1Number)
		{
			string str = "1142";
			Assert::IsTrue(Function1(str) == 497);
		}
		TEST_METHOD(TestF1Letters)
		{
			string str = "Gomel";
			Assert::IsTrue(Function1(str) == 1436);
		}

		TEST_METHOD(TestFindData)
		{
			string str1 = "1142", str2 = "Gomel";
			int Num = 10;
			Hash_table* Hash;
			Hash = new Hash_table[Num];
			Add(Hash, str1, str2);
			Assert::AreNotEqual(Find(Hash, str1), -1);
		}
		TEST_METHOD(TestF2Number)
		{
			string str = "1142";
			Assert::IsTrue(Function2(str) == 206);
		}
		TEST_METHOD(TestF2Letters)
		{
			string str = "Gomel";
			Assert::IsTrue(Function2(str) == 418);
		}

		TEST_METHOD(TestAddData)
		{
			string str1 = "1142", str2 = "Gomel";
			int Num = 10;
			Hash_table* Hash;
			Hash = new Hash_table[Num];
			Assert::IsTrue(Add(Hash, str1, str2) == "1142");
		}

		
		TEST_METHOD(TestDeleteData)
		{
			string str1 = "1142", str2 = "Gomel";
			int Num = 10;
			Hash_table* Hash;
			Hash = new Hash_table[Num];
			Add(Hash, str1, str2);
			Assert::IsTrue(Delete(Hash, str1) == "");
		}
		
	};
}
