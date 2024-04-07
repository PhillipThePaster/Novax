#include "Offsets.h"
#include "Cheats.h"
#include "Utils/Format.hpp"
#include <iostream>
#include <iomanip>
#include <Shlobj.h>
#include <KnownFolders.h>
#include <Windows.h>
#include <filesystem>

#pragma comment(lib, "user32.lib")


using namespace std;

namespace filesys = std::filesystem;	
int main(){
	ShowWindow(GetConsoleWindow(), SW_SHOW);
	//this is really unsecure not for a paid cheat just for a simple auth
	std::vector<std::string> validUUIDs = {
		"D6454ACFA-7666-2511-A8E3-2CF05D94A640",
		"DAD6245FA-A68A-3415-A38E-D8BBC1172A57",
		"DA4B2DE2B-9A5B-154F-AC2D-AC2B834309B7",
		"D67C11B3D-2CA0-0EAF-FBE1-5811222B4F44"
	};

	std::string uuid;
	FILE* pipe = _popen("wmic csproduct get uuid", "r");

	if (pipe) {
		char buffer[128];
		while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
			uuid += buffer;
		}
		_pclose(pipe);
	}

	uuid.erase(std::remove_if(uuid.begin(), uuid.end(), [](char c) {
		return !isxdigit(c) && c != '-';
	}), uuid.end());

	std::cout << uuid + "\n";

	std::cout << "Build: " << (std::find(validUUIDs.begin(), validUUIDs.end(), uuid) != validUUIDs.end() ? "Admin" : "Beta") << std::endl;
	Config::adconf = std::find(validUUIDs.begin(), validUUIDs.end(), uuid) != validUUIDs.end();

		auto ProcessStatus = ProcessMgr.Attach("cs2.exe");

		if (ProcessStatus != StatusCode::SUCCEED || !Offset::UpdateOffsets() || !gGame.InitAddress()) {
			std::cout << "[ERROR] ";
			if (!Offset::UpdateOffsets())
				std::cout << "Failed to update offsets." << std::endl;
			else if (!gGame.InitAddress())
				std::cout << "Failed to call InitAddress()." << std::endl;
			else
				std::cout << "Failed to attach process, StatusCode:" << ProcessStatus << std::endl;
			goto END;
		}

		try {
			Gui.AttachAnotherWindow("Counter-Strike 2", "SDL_app", Cheats::Run);
		}
		catch (const OSImGui::OSException& e) {
			std::cout << e.what() << std::endl;
		}

	END:
		system("pause");
		return 0;
	
}
