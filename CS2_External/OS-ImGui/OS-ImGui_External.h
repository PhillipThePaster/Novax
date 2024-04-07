#pragma once
#include "OS-ImGui_Base.h"

/****************************************************
* Copyright (C)	: Liv
* @file			: OS-ImGui_External.h
* @author		: Liv
* @email		: 1319923129@qq.com
* @version		: 1.0
* @date			: 2023/6/18	11:21
****************************************************/

namespace OSImGui
{
	class OSImGui_External : public OSImGui_Base
	{
	private:
		WindowType Type = NEW;
	public:
		ID3D11Device* getDevice();

		void NewWindow(std::string WindowName, Vec2 WindowSize, std::function<void()> CallBack);
		void AttachAnotherWindow(std::string DestWindowName, std::string DestWindowClassName, std::function<void()> CallBack);
	private:
		void MainLoop();
		bool UpdateWindowData();
		bool CreateMyWindow();
		bool PeekEndMessage();
	};
}