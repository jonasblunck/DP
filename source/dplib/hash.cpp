#include "stdafx.h"
#include "hash.h"

unsigned __int64 Hash(int lvalue, int rvalue)
{
  unsigned __int64 hash = 0;
  int b    = 378551; 
  int a    = 63689;
 
  hash = hash * a + lvalue;
  a = a * b;
  hash = hash * a + rvalue;
  
  return hash;
}

