#pragma once
#include "GameDefines.h"
#include "sol/sol.hpp"

class EngineBinding
{
public:
	static bool IsKeyPressed(tstring key);
	static void Quit();
	static void GoFullscreen();
	static void GoWindowed();
	static void MakeTimer(float seconds, sol::function function, bool repeats);
};
