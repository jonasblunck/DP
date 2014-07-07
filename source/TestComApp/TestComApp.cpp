// ADO101.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TestComApp.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <direct.h>
#define GetCurrentDir _getcwd

#include <iostream>
using namespace std;

#ifdef ENVIRONMENT64
	#import "c:\program files (x86)\common files\system\ado\msado28.tlb" no_namespace rename( "EOF", "A_EOF" ) 
#else
	#import "c:\program files\common files\system\ado\msado28.tlb" no_namespace rename( "EOF", "A_EOF" ) 
#endif

bool DemoAdo(_bstr_t strConnectionString)
{
	HRESULT hr = ::CoInitialize(NULL);
	if (FAILED(hr))
	{
		return false;
	}

	_ConnectionPtr pConnection;
	hr = pConnection.CreateInstance(__uuidof(Connection));
	if (FAILED(hr))
	{
		return false;
	}

	try
	{
		pConnection->Open(strConnectionString, _T(""), _T(""), adOpenUnspecified);

		_CommandPtr pCommand(__uuidof(Command));
		pCommand->ActiveConnection = pConnection;
		pCommand->CommandText = "SELECT CSTR(NOW()) as testDate";

		_RecordsetPtr pRecordSet(__uuidof(Recordset));
		pRecordSet->PutRefSource(pCommand);

		_variant_t vNull(DISP_E_PARAMNOTFOUND, VT_ERROR); 

		pRecordSet->Open(vNull, vNull, adOpenDynamic, adLockOptimistic, adCmdText);

		char szTimeStamp[64] = { 0 };
		if (!pRecordSet->A_EOF)
		{
			_Recordset **ptrResults = NULL;
			pRecordSet->QueryInterface(__uuidof(_Recordset),(void **) ptrResults);

			_variant_t vField(_T("testDate"));
			_variant_t vResult;
			vResult = pRecordSet->GetFields()->GetItem(vField)->Value;
			_bstr_t strTimeStamp(vResult);
			strncpy(szTimeStamp, (char*) strTimeStamp, 63);
			if (szTimeStamp > 0)
			{
				char szFeedback[256] = { 0 };
                sprintf(szFeedback, "SQL timestamp is: %s", szTimeStamp);
				cout << endl << szFeedback;
			}
		}

		pRecordSet->Close();
		pConnection->Close();
	}
	catch (_com_error& exception)
	{
		::CoUninitialize();
		return false;
	}

	::CoUninitialize();
	return true;
}

char* GetFullPath(char * partialPath)
{
	char full[_MAX_PATH];
	if (_fullpath(full, partialPath, _MAX_PATH) != NULL)
	{

		return full;
	}
	else
		return NULL;
}

char * GetConnectionString()
{
	char cCurrentPath[4096];
	GetCurrentDir(cCurrentPath, sizeof(cCurrentPath));
	strcat(cCurrentPath, "\\..\\bin\\test.mdb");
	char* abPath = GetFullPath(cCurrentPath);
	char connString[4096];
	sprintf(connString, "Provider = Microsoft.ACE.OLEDB.12.0; Data Source = %s; Persist Security Info=False;", abPath);
	return &connString[0];
}

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	char * connString = GetConnectionString();
	cout << "Connection String: " << connString;

	//HINSTANCE h = LoadLibrary(L"DPInfiltrator.dll");
	//ATLASSERT(NULL != h);

	DemoAdo(connString);

	return nRetCode;
}
