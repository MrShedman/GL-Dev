#pragma once

#include <string>
#include <vector>

#include <Windows.h>

std::string getAppPath();

std::string getUserPath();

std::string getOpenFilePath(HWND hwnd, const std::string& initialPath, std::vector<std::string> extensions);