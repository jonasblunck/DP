#include "stdafx.h"
#define _IMAGEHLP_
#include <atlhttp.h>
#include "StringParser.h"
#include "MsdnScraper.h"

void testMsdnScraper()
{
  CString url;
  CString parameters;

  // 
  // test CoCreateInstance
  DPUNIT_ISTRUE(MsdnScraper::FindMsdnURL("CoCreateInstance", url));
  DPUNIT_ISTRUE(MsdnScraper::FindParameters("CoCreateInstance", url, parameters));
  DPUNIT_STR_EQUAL("REFCLSID, LPUNKNOWN, DWORD, REFIID, LPVOID*", parameters);

  // 
  // test socket
  DPUNIT_ISTRUE(MsdnScraper::FindMsdnURL("socket", url));
  DPUNIT_ISTRUE(MsdnScraper::FindParameters("socket", url, parameters));
  DPUNIT_STR_EQUAL("int, int, int", parameters);

  // 
  // test lstrlen
  DPUNIT_ISTRUE(MsdnScraper::FindMsdnURL("lstrlen", url));
  DPUNIT_ISTRUE(MsdnScraper::FindParameters("lstrlen", url, parameters));
//  DPUNIT_STR_EQUAL("LPCTSTR", parameters);

}