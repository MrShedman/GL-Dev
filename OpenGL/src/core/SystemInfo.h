#pragma once

#include <Windows.h>
#include <psapi.h>
#include <iostream>
#include "window\Time.h"
#include "window\Clock.h"

class CpuInfo
{
public:
	CpuInfo();
	
	short getUsage();

private:

	ULONGLONG SubtractTimes(const FILETIME& ftA, const FILETIME& ftB);
	bool EnoughTimePassed();

	//system total times
	FILETIME m_ftPrevSysKernel;
	FILETIME m_ftPrevSysUser;
			
	//process times
	FILETIME m_ftPrevProcKernel;
	FILETIME m_ftPrevProcUser;
			
	short m_nCpuUsage;
	ULONGLONG m_dwLastRun;
	volatile LONG m_lRunCount;

	const Time interval;
	Clock intervalClock;
};