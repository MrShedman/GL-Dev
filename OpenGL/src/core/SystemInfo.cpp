
#include "SystemInfo.h"

CpuInfo::CpuInfo(void)
:
m_nCpuUsage(-1),
interval(seconds(1.f))
{
	ZeroMemory(&m_ftPrevSysKernel, sizeof(FILETIME));
	ZeroMemory(&m_ftPrevSysUser, sizeof(FILETIME));

	ZeroMemory(&m_ftPrevProcKernel, sizeof(FILETIME));
	ZeroMemory(&m_ftPrevProcUser, sizeof(FILETIME));

}

short CpuInfo::getUsage()
{
	short nCpuCopy = m_nCpuUsage;

	if (!EnoughTimePassed())
	{
		return nCpuCopy;
	}

	FILETIME ftSysIdle, ftSysKernel, ftSysUser;
	FILETIME ftProcCreation, ftProcExit, ftProcKernel, ftProcUser;

	if (!GetSystemTimes(&ftSysIdle, &ftSysKernel, &ftSysUser) || 
		!GetProcessTimes(GetCurrentProcess(), &ftProcCreation, &ftProcExit, &ftProcKernel, &ftProcUser))
	{
		return nCpuCopy;
	}
		
	ULONGLONG ftSysKernelDiff = SubtractTimes(ftSysKernel, m_ftPrevSysKernel);
	ULONGLONG ftSysUserDiff = SubtractTimes(ftSysUser, m_ftPrevSysUser);

	ULONGLONG ftProcKernelDiff = SubtractTimes(ftProcKernel, m_ftPrevProcKernel);
	ULONGLONG ftProcUserDiff = SubtractTimes(ftProcUser, m_ftPrevProcUser);

	ULONGLONG nTotalSys = ftSysKernelDiff + ftSysUserDiff;
	ULONGLONG nTotalProc = ftProcKernelDiff + ftProcUserDiff;

	if (nTotalSys > 0)
	{
		m_nCpuUsage = static_cast<short>((100 * nTotalProc) / nTotalSys);
	}

	m_ftPrevSysKernel = ftSysKernel;
	m_ftPrevSysUser = ftSysUser;
	m_ftPrevProcKernel = ftProcKernel;
	m_ftPrevProcUser = ftProcUser;

	nCpuCopy = m_nCpuUsage;

	std::cout << "CPU usage: " << nCpuCopy << "%" << std::endl;
	return nCpuCopy;
}

ULONGLONG CpuInfo::SubtractTimes(const FILETIME& ftA, const FILETIME& ftB)
{
	LARGE_INTEGER a, b;
	a.LowPart = ftA.dwLowDateTime;
	a.HighPart = ftA.dwHighDateTime;

	b.LowPart = ftB.dwLowDateTime;
	b.HighPart = ftB.dwHighDateTime;

	return a.QuadPart - b.QuadPart;
}

bool CpuInfo::EnoughTimePassed()
{
	if (intervalClock.getElapsedTime() > interval)
	{
		intervalClock.restart();
		return true;
	}
	else
	{
		return false;
	}
}