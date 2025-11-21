#include "pch.h"
#include "ModuleInfo.h"
#include <windows.h>
#include <psapi.h>
#include <sstream>
#include <iomanip>

#pragma comment(lib, "version.lib")

static std::wstring GetFileVersion(const std::wstring& filePath)
{
    DWORD handle = 0;
    DWORD size = GetFileVersionInfoSizeW(filePath.c_str(), &handle);
    if (size == 0)
        return L"";

    std::vector<BYTE> buffer(size);
    if (!GetFileVersionInfoW(filePath.c_str(), handle, size, buffer.data()))
        return L"";

    VS_FIXEDFILEINFO* fileInfo = nullptr;
    UINT len = 0;
    if (!VerQueryValueW(buffer.data(), L"\\", (LPVOID*)&fileInfo, &len))
        return L"";

    std::wstringstream ss;
    ss << HIWORD(fileInfo->dwFileVersionMS) << L"."
       << LOWORD(fileInfo->dwFileVersionMS) << L"."
       << HIWORD(fileInfo->dwFileVersionLS) << L"."
       << LOWORD(fileInfo->dwFileVersionLS);
    return ss.str();
}

static std::wstring GetFileDateTime(const std::wstring& filePath)
{
    WIN32_FILE_ATTRIBUTE_DATA fileAttr;
    if (!GetFileAttributesExW(filePath.c_str(), GetFileExInfoStandard, &fileAttr))
        return L"";

    FILETIME localTime;
    FileTimeToLocalFileTime(&fileAttr.ftLastWriteTime, &localTime);

    SYSTEMTIME sysTime;
    FileTimeToSystemTime(&localTime, &sysTime);

    std::wstringstream ss;
    ss << std::setfill(L'0') << std::setw(4) << sysTime.wYear << L"-"
       << std::setw(2) << sysTime.wMonth << L"-"
       << std::setw(2) << sysTime.wDay << L" "
       << std::setw(2) << sysTime.wHour << L":"
       << std::setw(2) << sysTime.wMinute;
    return ss.str();
}

std::vector<ModuleInfo> GetLoadedModules()
{
    std::vector<ModuleInfo> modules;

    HANDLE hProcess = GetCurrentProcess();
    HMODULE hMods[1024];
    DWORD cbNeeded;

    if (EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded))
    {
        DWORD count = cbNeeded / sizeof(HMODULE);
        for (DWORD i = 0; i < count; i++)
        {
            wchar_t szModName[MAX_PATH];
            if (GetModuleFileNameExW(hProcess, hMods[i], szModName, MAX_PATH))
            {
                ModuleInfo info;
                info.filePath = szModName;

                // Extract filename from path
                const wchar_t* lastSlash = wcsrchr(szModName, L'\\');
                info.fileName = lastSlash ? (lastSlash + 1) : szModName;

                info.version = GetFileVersion(szModName);
                info.fileDate = GetFileDateTime(szModName);

                modules.push_back(info);
            }
        }
    }

    return modules;
}
