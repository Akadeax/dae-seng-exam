//-----------------------------------------------------------------
// Main Game File
// C++ Source - Game.cpp - version v8_01
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Game.h"
#include "SetupContext.h"
#include "Painter.h"
#include "Vectors.h"
#include "Color.h"

//-----------------------------------------------------------------
// Game Member Functions
//-----------------------------------------------------------------

Game::Game()
{
	// nothing to create
}

Game::~Game()
{
	// nothing to destroy
}

void Game::Initialize()
{
	SetupBindings();
	AbstractGame::Initialize();

	std::string scriptName{ "lua/script.lua" };

	state.safe_script_file(scriptName);

	SetupContext setupContext{ TEXT("Default Name"), Vector2l{ 600, 600 }, TEXT("WASD") };

	sol::function luaSetupFunction{ state["setup"] };
	if(luaSetupFunction.valid())
	{
		auto setupResult = luaSetupFunction(setupContext);
		if(!setupResult.valid())
		{
			const sol::error err = setupResult;
			throw std::exception(err.what());
		}
	}

	GAME_ENGINE->SetTitle(setupContext.windowTitle);
	GAME_ENGINE->SetWidth(setupContext.windowSize.x);
	GAME_ENGINE->SetHeight(setupContext.windowSize.y);
	GAME_ENGINE->SetFrameRate(50);
	GAME_ENGINE->SetKeyList(setupContext.listenKeyList);


	luaDrawFunction = state["draw"];
	if (!luaDrawFunction.valid())
	{
		throw LuaFunctionInvalid{};
	}

	luaUpdateFunction = state["update"];
	if (!luaUpdateFunction.valid())
	{
		throw LuaFunctionInvalid{};
	}

	luaCheckKeyboardFunction = state["check_keyboard"];
	if (!luaCheckKeyboardFunction.valid())
	{
		throw LuaFunctionInvalid{};
	}

	luaKeyPressedFunction = state["key_pressed"];
	if (!luaKeyPressedFunction.valid())
	{
		throw LuaFunctionInvalid{};
	}
}

void Game::Start()
{
	// Insert code that needs to execute (once) at the start of the game, after the game window is created
}

void Game::End()
{
	// Insert code that needs to execute when the game ends
}

void Game::Paint(RECT rect) const
{
	luaDrawFunction();
}

void Game::Tick()
{
	luaUpdateFunction();
}

void Game::MouseButtonAction(bool isLeft, bool isDown, int x, int y, WPARAM wParam)
{
	// Insert code for a mouse button action

	/* Example:
	if (isLeft == true && isDown == true) // is it a left mouse click?
	{
		if ( x > 261 && x < 261 + 117 ) // check if click lies within x coordinates of choice
		{
			if ( y > 182 && y < 182 + 33 ) // check if click also lies within y coordinates of choice
			{
				GAME_ENGINE->MessageBox(_T("Clicked."));
			}
		}
	}
	*/
}

void Game::MouseWheelAction(int x, int y, int distance, WPARAM wParam)
{
	// Insert code for a mouse wheel action
}

void Game::MouseMove(int x, int y, WPARAM wParam)
{
	// Insert code that needs to execute when the mouse pointer moves across the game window

	/* Example:
	if ( x > 261 && x < 261 + 117 ) // check if mouse position is within x coordinates of choice
	{
		if ( y > 182 && y < 182 + 33 ) // check if mouse position also is within y coordinates of choice
		{
			GAME_ENGINE->MessageBox("Mouse move.");
		}
	}
	*/
}

void Game::CheckKeyboard()
{
	// Here you can check if a key is pressed down
	// Is executed once per frame

	/* Example:
	if (GAME_ENGINE->IsKeyDown(_T('K'))) xIcon -= xSpeed;
	if (GAME_ENGINE->IsKeyDown(_T('L'))) yIcon += xSpeed;
	if (GAME_ENGINE->IsKeyDown(_T('M'))) xIcon += xSpeed;
	if (GAME_ENGINE->IsKeyDown(_T('O'))) yIcon -= ySpeed;
	*/

	luaCheckKeyboardFunction();
}

void Game::KeyPressed(TCHAR key)
{
	luaKeyPressedFunction(tstring{ key });
	// DO NOT FORGET to use SetKeyList() !!

	// Insert code that needs to execute when a key is pressed
	// The function is executed when the key is *released*
	// You need to specify the list of keys with the SetKeyList() function

	/* Example:
	switch (key)
	{
	case _T('K'): case VK_LEFT:
		GAME_ENGINE->MessageBox("Moving left.");
		break;
	case _T('L'): case VK_DOWN:
		GAME_ENGINE->MessageBox("Moving down.");
		break;
	case _T('M'): case VK_RIGHT:
		GAME_ENGINE->MessageBox("Moving right.");
		break;
	case _T('O'): case VK_UP:
		GAME_ENGINE->MessageBox("Moving up.");
		break;
	case VK_ESCAPE:
		GAME_ENGINE->MessageBox("Escape menu.");
	}
	*/
}

void Game::CallAction(Caller* callerPtr)
{
	// Insert the code that needs to execute when a Caller (= Button, TextBox, Timer, Audio) executes an action
}

void Game::SetupBindings()
{
	state.open_libraries(sol::lib::base);

	state.new_usertype<Painter>(
		"Painter",
		"fill_window_rect", &Painter::FillWindowRect,
		"set_color", &Painter::SetColor,
		"draw_line", &Painter::DrawLine
	);

	// This is POD
	state.new_usertype<SetupContext>(
        "SetupContext",
        "get_window_size", [](const SetupContext* self) -> Vector2l { return self->windowSize; },
        "set_window_size", [](SetupContext* self, Vector2l windowSize){ self->windowSize = windowSize; },

        "get_window_title", [](const SetupContext* self) -> tstring { return self->windowTitle; },
        "set_window_title", [](SetupContext* self, const tstring& title){ self->windowTitle = title; },

        "get_listen_keys", [](const SetupContext* self) -> tstring { return self->listenKeyList; },
        "set_listen_keys", [](SetupContext* self, const tstring& listenKeys){ self->listenKeyList = listenKeys; }
    );

	state.new_usertype<Vector2l>(
		"Vector2l",
		sol::constructors<Vector2l(), Vector2l(Vector2l_t, Vector2l_t)>{},
		"x", &Vector2<Vector2l_t>::x,
		"y", &Vector2<Vector2l_t>::y,
		"print", &Vector2<Vector2l_t>::Print
	);
	state.new_usertype<Vector2f>(
		"Vector2f",
		sol::constructors<Vector2f(), Vector2l(Vector2f_t, Vector2f_t)>{},
		"x", &Vector2<Vector2f_t>::x,
		"y", &Vector2<Vector2f_t>::y,
		"print", &Vector2<Vector2f_t>::Print
	);

	sol::table colorsTable{ state.create_named_table("Colors") };
	colorsTable["BLACK"] = Color(0, 0, 0);
	colorsTable["WHITE"] = Color(255, 255, 255);
	colorsTable["RED"] = Color(255, 0, 0);
	colorsTable["GREEN"] = Color(0, 255, 0);
	colorsTable["BLUE"] = Color(0, 0, 255);
	colorsTable["YELLOW"] = Color(255, 255, 0);
	colorsTable["CYAN"] = Color(0, 255, 255);
	colorsTable["MAGENTA"] = Color(255, 0, 255);
	colorsTable["GRAY"] = Color(128, 128, 128);
	colorsTable["LIGHT_GRAY"] = Color(211, 211, 211);
	colorsTable["DARK_GRAY"] = Color(64, 64, 64);
	colorsTable["ORANGE"] = Color(255, 165, 0);
	colorsTable["PINK"] = Color(255, 192, 203);
	colorsTable["PURPLE"] = Color(128, 0, 128);
	colorsTable["BROWN"] = Color(139, 69, 19);
	colorsTable["LIME"] = Color(50, 205, 50);
	colorsTable["OLIVE"] = Color(128, 128, 0);
	colorsTable["MAROON"] = Color(128, 0, 0);
	colorsTable["NAVY"] = Color(0, 0, 128);
	colorsTable["TEAL"] = Color(0, 128, 128);
	colorsTable["GOLD"] = Color(255, 215, 0);
	colorsTable["SILVER"] = Color(192, 192, 192);
	colorsTable["BEIGE"] = Color(245, 245, 220);
	colorsTable["TURQUOISE"] = Color(64, 224, 208);
	colorsTable["INDIGO"] = Color(75, 0, 130);
	colorsTable["VIOLET"] = Color(238, 130, 238);
	colorsTable["SALMON"] = Color(250, 128, 114);
	colorsTable["CORAL"] = Color(255, 127, 80);
	colorsTable["CHOCOLATE"] = Color(210, 105, 30);
	colorsTable["KHAKI"] = Color(240, 230, 140);
	colorsTable["PLUM"] = Color(221, 160, 221);
	colorsTable["TAN"] = Color(210, 180, 140);
	colorsTable["AQUA"] = Color(0, 255, 255);
	colorsTable["FUCHSIA"] = Color(255, 0, 255);
	colorsTable["SEA_GREEN"] = Color(46, 139, 87);
	colorsTable["LAVENDER"] = Color(230, 230, 250);
	colorsTable["CRIMSON"] = Color(220, 20, 60);
	colorsTable["MINT"] = Color(189, 252, 201);
	colorsTable["SKY_BLUE"] = Color(135, 206, 235);
	colorsTable["PEACH"] = Color(255, 218, 185);

	state.new_usertype<Color>(
		"Color",
		sol::constructors<Color(Color_t, Color_t, Color_t)>{},
		"r", &Color::r,
		"g", &Color::g,
		"b", &Color::b

		// "BLACK", Color(0, 0, 0),
        // "WHITE", Color(255, 255, 255),
        // "RED", Color(255, 0, 0),
        // "GREEN", Color(0, 255, 0),
        // "BLUE", Color(0, 0, 255),
        // "YELLOW", Color(255, 255, 0),
        // "CYAN", Color(0, 255, 255),
        // "MAGENTA", Color(255, 0, 255),
        // "GRAY", Color(128, 128, 128),
        // "LIGHT_GRAY", Color(211, 211, 211),
        // "DARK_GRAY", Color(64, 64, 64),
        // "ORANGE", Color(255, 165, 0),
        // "PINK", Color(255, 192, 203),
        // "PURPLE", Color(128, 0, 128),
        // "BROWN", Color(139, 69, 19),
        // "LIME", Color(50, 205, 50),
        // "OLIVE", Color(128, 128, 0),
        // "MAROON", Color(128, 0, 0),
        // "NAVY", Color(0, 0, 128),
        // "TEAL", Color(0, 128, 128),
        // "GOLD", Color(255, 215, 0),
        // "SILVER", Color(192, 192, 192),
        // "BEIGE", Color(245, 245, 220),
        // "TURQUOISE", Color(64, 224, 208),
        // "INDIGO", Color(75, 0, 130),
        // "VIOLET", Color(238, 130, 238),
        // "SALMON", Color(250, 128, 114),
        // "CORAL", Color(255, 127, 80),
        // "CHOCOLATE", Color(210, 105, 30),
        // "KHAKI", Color(240, 230, 140),
        // "PLUM", Color(221, 160, 221),
        // "TAN", Color(210, 180, 140),
        // "AQUA", Color(0, 255, 255),
        // "FUCHSIA", Color(255, 0, 255),
        // "SEA_GREEN", Color(46, 139, 87),
        // "LAVENDER", Color(230, 230, 250),
        // "CRIMSON", Color(220, 20, 60),
        // "MINT", Color(189, 252, 201),
        // "SKY_BLUE", Color(135, 206, 235),
        // "PEACH", Color(255, 218, 185)
	);
}
