#include "stdafx.h"
#include "hash.h"

void testHash()
{
  int a = 10;
  int b = 11;

  DPUNIT_EQUAL(Hash(a, b), Hash(a, b));
  DPUNIT_EQUAL(Hash(b, a), Hash(b, a));

  DPUNIT_EQUAL(Hash(a, a), Hash(a, a));
  
  DPUNIT_ISTRUE(Hash(a, b) != Hash(b, a));
}