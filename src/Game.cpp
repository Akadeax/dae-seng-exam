//-----------------------------------------------------------------
// Main Game File
// C++ Source - Game.cpp - version v8_01
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Game.h"
#include "SetupContext.h"
#include "Vectors.h"
#include "Color.h"

#include "PainterBinding.h"
#include "EngineBinding.h"

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


	luaCheckKeyboardFunction();
}

void Game::KeyPressed(TCHAR key)
{
	luaKeyPressedFunction(tstring{ key });
}

void Game::CallAction(Caller* callerPtr)
{
	// Insert the code that needs to execute when a Caller (= Button, TextBox, Timer, Audio) executes an action
}

void Game::SetupBindings()
{
	state.open_libraries(sol::lib::base);

	state.new_usertype<PainterBinding>(
		"Painter",
		"fill_window_rect", &PainterBinding::FillWindowRect,
		"set_color", &PainterBinding::SetColor,
		"set_font", &PainterBinding::SetFont,

		"draw_line", &PainterBinding::DrawLine,
		"draw_rect", &PainterBinding::DrawRect,
		"fill_rect", &PainterBinding::FillRect,
		"draw_round_rect", &PainterBinding::DrawRoundRect,
		"fill_round_rect", &PainterBinding::FillRoundRect,
		"draw_oval", &PainterBinding::DrawOval,
		"fill_oval", &PainterBinding::FillOval,
		"draw_arc", &PainterBinding::DrawArc,
		"fill_arc", &PainterBinding::FillArc,
		"draw_string", &PainterBinding::DrawString,
		"draw_string_sized", &PainterBinding::DrawStringSized,
		"draw_bitmap", &PainterBinding::DrawBitmap,
		"draw_bitmap_sourced", &PainterBinding::DrawBitmapSourced,
		"draw_polygon", &PainterBinding::DrawPolygon,
		"fill_polygon", &PainterBinding::FillPolygon
	);

	state.new_usertype<Bitmap>(
		"BitmapRef",
		"new", &PainterBinding::CreateBitmap
	);

	state.new_usertype<Font>(
		"FontRef",
		"new", &PainterBinding::CreateFontRef
	);

	state.new_usertype<EngineBinding>(
		"Engine",
		"is_key_pressed", &EngineBinding::IsKeyPressed,
		"quit", &EngineBinding::Quit,
		"go_fullscreen", &EngineBinding::GoFullscreen,
		"go_windowed", &EngineBinding::GoWindowed
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
	);
}
