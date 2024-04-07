#pragma once
#include "..\OS-ImGui\imgui\imgui.h"
#include "GlobalVars.hpp"
#include "..\MenuConfig.hpp"
#include <iostream>
#include <Windows.h>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <sstream> 


namespace Watermark {
    inline void Render() noexcept {
        if (Config::WaterMark) {
            auto draw_list = ImGui::GetForegroundDrawList();

            static float FrameRate = ImGui::GetIO().Framerate;
            FrameRate = ImGui::GetIO().Framerate;

            wchar_t username[256];
            DWORD buffer_size = sizeof(username) / sizeof(username[0]);
            if (GetUserName(username, &buffer_size)) {
                char narrowUsername[256];
                size_t charsConverted = 0;
                if (wcstombs_s(&charsConverted, narrowUsername, sizeof(narrowUsername), username, _TRUNCATE) == 0) {
                    if (Config::WaterMark) {
                        std::string watermark;
                        if (Config::watermarkcheat) watermark += "Novax";
                        if (Config::watermarkcheat && Config::watermarkuser)
                            watermark += " | ";
                        if (Config::watermarkuser) watermark += narrowUsername;
                        if (Config::watermarktime) {
                            auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
                            std::tm tm_local;
                            localtime_s(&tm_local, &now);
                            std::ostringstream timeStream;
                            timeStream << std::put_time(&tm_local, " | %H:%M:%S");
                            watermark += timeStream.str();
                        }
                        if (Config::watermarkfps) watermark += " | " + std::to_string(static_cast<int>(FrameRate));
                        if (Config::watermarkbuild) watermark += " | " + std::string(Config::adconf ? "Admin" : "Beta");
                        auto watermark_size = ImGui::CalcTextSize(watermark.c_str());
                        draw_list->AddRectFilled(ImVec2(6, 4), ImVec2((4 * 2) + watermark_size.x + 6, 6), Config::Accent);
                        draw_list->AddRectFilled(ImVec2(6, 6), ImVec2((4 * 2) + watermark_size.x + 6, 25), IM_COL32(40, 40, 40, 200));
                        draw_list->AddText(ImVec2(10, 8), ImColor(255, 255, 255, 255), watermark.c_str());
                    }
                }
            }
        }
    }
}








