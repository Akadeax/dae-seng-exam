//-----------------------------------------------------------------
// Main Game  File
// C++ Header - Game.h - version v8_01
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------

#include <optional>

#include "Resource.h"
#include "GameEngine.h"
#include "AbstractGame.h"
#include "sol/sol.hpp"
#include "Timer.h"

//-----------------------------------------------------------------
// Game Class
//-----------------------------------------------------------------
class Game : public AbstractGame, public Callable
{
public:
	//---------------------------
	// Constructor(s) and Destructor
	//---------------------------
	Game();

	virtual ~Game() override;

	//---------------------------
	// Disabling copy/move constructors and assignment operators
	//---------------------------
	Game(const Game& other)					= delete;
	Game(Game&& other) noexcept				= delete;
	Game& operator=(const Game& other)		= delete;
	Game& operator=(Game&& other) noexcept	= delete;

	//---------------------------
	// General Member Functions
	//---------------------------
	void Initialize			()															override;
	void Start				()															override;
	void End				()															override;
	void Paint				(RECT rect)	const											override;
	void Tick				()															override;
	void MouseButtonAction	(bool isLeft, bool isDown, int x, int y, WPARAM wParam)		override;
	void MouseWheelAction	(int x, int y, int distance, WPARAM wParam)					override;
	void MouseMove			(int x, int y, WPARAM wParam)								override;
	void CheckKeyboard		()															override;
	void KeyPressed			(TCHAR key)													override;

	void CallAction			(Caller* callerPtr)											override;

private:
	void SetupBindings();

	static void Panic(sol::optional<tstring> maybe_msg);

	// -------------------------
	// Datamembers
	// -------------------------
	sol::state state;

	// lua functions
	sol::function luaUpdateFunction;
	sol::function luaDrawFunction;
	sol::function luaCheckKeyboardFunction;
	sol::function luaKeyPressedFunction;
};
