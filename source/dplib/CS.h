
#pragma once


#undef EnterCriticalSection
#define EnterCriticalSection CheckedEnterCriticalSection

#undef LeaveCriticalSection
#define LeaveCriticalSection CheckedLeaveCriticalSection

class IDeadlockListener;

void CheckedEnterCriticalSection(CRITICAL_SECTION*);
void CheckedLeaveCriticalSection(CRITICAL_SECTION*);
void SetDeadlockDetectionListener(IDeadlockListener* listener);