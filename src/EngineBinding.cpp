#include "EngineBinding.h"
#include "GameEngine.h"

bool EngineBinding::IsKeyPressed(tstring key)
{
	return GAME_ENGINE->IsKeyDown(key[0]);
}

void EngineBinding::Quit()
{
	GAME_ENGINE->Quit();
}

void EngineBinding::GoFullscreen()
{
	GAME_ENGINE->GoFullscreen();
}

void EngineBinding::GoWindowed()
{
	GAME_ENGINE->GoWindowedMode();
}
