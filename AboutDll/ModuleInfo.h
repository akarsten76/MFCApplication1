#pragma once

#include <vector>
#include <string>

struct ModuleInfo
{
	std::wstring fileName;
	std::wstring filePath;
	std::wstring version;
	std::wstring fileDate;
};

std::vector<ModuleInfo> GetLoadedModules();
