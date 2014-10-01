
#include "core\FileSystem.h"

#include <Shlobj.h>
#include <CommDlg.h>
#include <ShellAPI.h>
#include <Knownfolders.h>

#include "window\Utilities.h"

std::string getAppPath()
{
	wchar_t appPath[MAX_PATH] = L"";

	// fetch the path of the executable
	::GetModuleFileName(0, appPath, sizeof(appPath)-1);

	// get a pointer to the last occurrence of the windows path separator
	wchar_t *appDir = wcsrchr(appPath, L'\\');

	if (appDir)
	{
		++appDir;

		// this shouldn't be null but one never knows
		if (appDir)
		{
			// null terminate the string
			*appDir = 0;
		}
	}

	return Util::ws2s(std::wstring(appPath));
}

std::string getUserPath()
{
	wchar_t path[MAX_PATH];

	if (SUCCEEDED(SHGetFolderPathW(NULL, CSIDL_PROFILE, NULL, 0, path)))
	{
		return Util::ws2s(path);
	}
	else
	{
		return std::string();
	}
}

std::string getOpenFilePath(HWND hwnd, const std::string& initialPath, std::vector<std::string> extensions)
{
	OPENFILENAMEW ofn;       // common dialog box structure
	wchar_t szFile[MAX_PATH];       // buffer for file name

	// Initialize OPENFILENAME
	::ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFile = szFile;

	// Set lpstrFile[0] to '\0' so that GetOpenFileName does not
	// use the contents of szFile to initialize itself.
	//
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);

	std::wstring ext;

	if (extensions.empty())
	{
		ofn.lpstrFilter = L"All\0*.*\0";
	}
	else
	{
		ext += L"Supported Types";
		ext += L'\0';

		for (std::vector<std::string>::const_iterator strIt = extensions.begin(); strIt != extensions.end(); ++strIt)
		{
			ext += L"*.";
			ext += Util::s2ws(*strIt);

			// append a semicolon to all but the last extensions
			if (strIt + 1 != extensions.end())
			{
				ext += L';';
			}
			else
			{
				ext += L'\0';
			}
		}

		ext += L'\0';

		ofn.lpstrFilter = ext.c_str();
	}

	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;

	if (initialPath.empty())
	{
		ofn.lpstrInitialDir = NULL;
	}
	else
	{
		ofn.lpstrInitialDir = Util::s2ws(initialPath).c_str();//initialPathStr;
	}

	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Display the Open dialog box.
	if (::GetOpenFileNameW(&ofn) == TRUE)
	{
		return Util::ws2s(ofn.lpstrFile);
	}
	else
	{
		return std::string();
	}
}