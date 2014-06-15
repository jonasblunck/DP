#include "stdafx.h"
#include "GuidHelpers.h"

// Kim Gräsman implemented these for me :-)

bool operator < (GUID guid1, GUID guid2) 
{
	LONG* p1 = (LONG*)&guid1;
	LONG* p2 = (LONG*)&guid2;
	int n = 0;

	while (*p1 == *p2 && (n < 4))
	{
		p1++;
		p2++;
		n++;
	}

	return (n < 4 && (*p1 < *p2));
}

bool operator > (GUID guid1, GUID guid2) 
{
	LONG* p1 = (LONG*)&guid1;
	LONG* p2 = (LONG*)&guid2;
	int n = 0;

	while (*p1 == *p2 && (n < 4))
	{
		p1++;
		p2++;
		n++;
	}

	return (n < 4 && (*p1 > *p2));
}