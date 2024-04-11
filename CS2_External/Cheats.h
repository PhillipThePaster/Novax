#pragma once
#pragma comment(lib, "winmm.lib")

#include "Game.h"
#include "Entity.h"
#include "Utils/keys.cpp"
#include "Utils/Watermarkshit.hpp"
#include "font/IconsFontAwesome5.h"
#include "..\CS2_External\Hitsounds\Sounds.h"

#include "AimBot.hpp"
#include "TriggerBot.hpp"
#include "MenuConfig.hpp"
#include <Windows.h>
#include <cmath>
#include "xorstr.h"
#include <vector>
#include <string>
#include <sstream>
#include <thread>


namespace Cheats{
	void Menu();
	void Run();

	inline std::string GetUsername()
	{
		wchar_t username[256];
		DWORD buffer_size = sizeof(username) / sizeof(username[0]);

		if (GetUserName(username, &buffer_size) && wcstombs_s(nullptr, nullptr, 0, username, _TRUNCATE) == 0)
		{
			return std::string(username, username + wcslen(username));
		}

		return "";
	}

	static inline std::wstring STR2LPCWSTR(const std::string& str)
	{
		int size = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
		std::wstring result(size, L'\0');
		MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &result[0], size);
		return result;
	}
}
