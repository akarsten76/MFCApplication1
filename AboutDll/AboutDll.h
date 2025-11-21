#pragma once

#ifdef ABOUTDLL_EXPORTS
#define ABOUTDLL_API __declspec(dllexport)
#else
#define ABOUTDLL_API __declspec(dllimport)
#endif

extern "C" ABOUTDLL_API void ShowAboutDialog(HWND hParent);
