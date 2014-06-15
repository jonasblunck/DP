// DPInfiltratorTests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

// global test success flag
bool s_unittest_success = true;

// forward declare test functions
void testDynamicHook();
void testDebugSymbols();
void testStringParser();
void testPipes();
void testCOM();
void testDeadlockDetection();
void testHash();
void testISC();
void testIPC();
void integrationTests();

int _tmain(int argc, _TCHAR* argv[])
{
  testDynamicHook();
  testISC();
  testDebugSymbols();
  testStringParser();
  testPipes();
  testCOM();
  testHash();
  testDeadlockDetection();
  testIPC();

//  integrationTests();

  return s_unittest_success ? 0 : 1;
}

