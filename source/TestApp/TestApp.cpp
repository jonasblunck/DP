// TestApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <MsXml.h>

//
// calls made on COM objects here should be 
void DoCOMWork()
{
  VARIANT_BOOL vt;
  CComPtr<IXMLDOMDocument> sp;
  if (SUCCEEDED(sp.CoCreateInstance(__uuidof(DOMDocument))))
  {
    sp->load(CComVariant("NO_SUCH_FILE"), &vt);
    sp->hasChildNodes(&vt);
  }
}

int _tmain(int argc, _TCHAR* argv[])
{
  //
  // instead of having DPInfiltrator being pushed into the process, I'm loading it my self
  //
  HINSTANCE h = LoadLibrary(L"DPInfiltrator.dll"); 
  ATLASSERT(NULL != h);

  {
    CoInitialize(0);

    DoCOMWork(); 
  
    CoUninitialize();
  }

  //
  // give process some time to send of all trace data to listener
  //
  Sleep(1000);

  return 0;
}
