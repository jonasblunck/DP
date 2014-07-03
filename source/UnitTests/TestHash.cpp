#include "stdafx.h"
#include "hash.h"

#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(testHash)
{
  int a = 10;
  int b = 11;

  TEST_METHOD(Hash_ab_Equal)
  {
	  Assert::AreEqual(Hash(a, b), Hash(a, b));
  }

  TEST_METHOD(Hash_ba_Equal)
  {
	  Assert::AreEqual(Hash(b, a), Hash(b, a));
  }

  TEST_METHOD(Hash_aa_Equal)
  {
	  Assert::AreEqual(Hash(a, a), Hash(a, a));
  }

  TEST_METHOD(Hash_ab_ba_NotEqual)
  {
	  Assert::AreNotEqual(Hash(a, b), Hash(b, a));
  }
};