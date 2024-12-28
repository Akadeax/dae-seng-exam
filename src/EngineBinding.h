#pragma once
#include "GameDefines.h"

class EngineBinding
{
public:
	static bool IsKeyPressed(tstring key);
	static void Quit();
	static void GoFullscreen();
	static void GoWindowed();
};
