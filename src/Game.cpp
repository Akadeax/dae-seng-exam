//-----------------------------------------------------------------
// Main Game File
// C++ Source - Game.cpp - version v8_01
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Game.h"

#include <iostream>
#include "SetupContext.h"
#include "GameDefines.h"
#include "Vectors.h"
#include "Color.h"

#include "PainterBinding.h"
#include "EngineBinding.h"

//-----------------------------------------------------------------
// Game Member Functions
//-----------------------------------------------------------------

Game::Game()
	: state{ sol::c_call<decltype(&Game::Panic), &Game::Panic> }
{
}

Game::~Game()
{
	// nothing to destroy
}

void Game::Initialize()
{
	SetupBindings();
	AbstractGame::Initialize();

	std::string scriptName{ "lua/game.lua" };
	state.script_file(scriptName);

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
	sol::protected_function_result result{ luaDrawFunction.call() };
	if (!result.valid())
	{
		sol::error err = result;
		terr << _T("Paint error: ") << err.what() << '\n';
	}
}

void Game::Tick()
{
	float deltaTime = static_cast<float>(GAME_ENGINE->GetFrameDelay()) / 1000;
	sol::protected_function_result result{ luaUpdateFunction.call(deltaTime) };
	if (!result.valid())
	{
		sol::error err = result;
		terr << _T("Update error: ") << err.what() << '\n';
	}
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
	sol::protected_function_result result{ luaCheckKeyboardFunction.call() };
	if (!result.valid())
	{
		sol::error err = result;
		terr << _T("CheckKeyboard error: ") << err.what() << '\n';
	}
}

void Game::KeyPressed(TCHAR key)
{
	sol::protected_function_result result{ luaKeyPressedFunction.call(tstring{ key }) };
	if (!result.valid())
	{
		sol::error err = result;
		terr << _T("KeyPressed error: ") << err.what() << '\n';
	}
}

void Game::CallAction(Caller* callerPtr)
{
}

void Game::SetupBindings()
{
	state.open_libraries(sol::lib::base, sol::lib::math, sol::lib::string, sol::lib::debug, sol::lib::package);

	state["delta_time"] = static_cast<float>(GAME_ENGINE->GetFrameDelay()) / 1000;

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
		"draw_bitmap_scaled", &PainterBinding::DrawBitmapScaled,
		"draw_bitmap_sourced", &PainterBinding::DrawBitmapSourced,
		"draw_bitmap_sourced_scaled", &PainterBinding::DrawBitmapSourcedScaled,
		"draw_polygon", &PainterBinding::DrawPolygon,
		"fill_polygon", &PainterBinding::FillPolygon
	);

	state.new_usertype<Bitmap>(
		"BitmapRef",
		"new", &PainterBinding::CreateBitmap,
		"get_size", &PainterBinding::GetBitmapSize
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
		"go_windowed", &EngineBinding::GoWindowed,
		"make_timer", &EngineBinding::MakeTimer
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
		"print", &Vector2<Vector2l_t>::Print,
		"distance2", &Vector2<Vector2l_t>::Distance2
	);
	state.new_usertype<Vector2f>(
		"Vector2f",
		sol::constructors<Vector2f(), Vector2l(Vector2f_t, Vector2f_t)>{},
		"x", &Vector2<Vector2f_t>::x,
		"y", &Vector2<Vector2f_t>::y,
		"print", &Vector2<Vector2f_t>::Print,
		"distance2", &Vector2<Vector2f_t>::Distance2
	);

	sol::table colorsTable{ state.create_named_table("Colors") };
	{ // scope so it's collapsable
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
		colorsTable["DARK_GRAY"] = Color(32, 32, 32);
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
	}

	sol::table keysTable{ state.create_named_table("Keys") };
	{
		keysTable["ESCAPE"] = tstring{ static_cast<char>(VK_ESCAPE) };
		keysTable["RETURN"] = tstring{ static_cast<char>(VK_RETURN) };
		keysTable["SPACE"] = tstring{ static_cast<char>(VK_SPACE) };
		keysTable["DELETE"] = tstring{ static_cast<char>(VK_DELETE) };
		keysTable["SHIFT"] = tstring{ static_cast<char>(VK_SHIFT) };
		keysTable["BACK"] = tstring{ static_cast<char>(VK_BACK) };
		keysTable["TAB"] = tstring{ static_cast<char>(VK_TAB) };
	}

	state.new_usertype<Color>(
		"Color",
		sol::constructors<Color(Color_t, Color_t, Color_t)>{},
		"r", &Color::r,
		"g", &Color::g,
		"b", &Color::b
	);
}

void Game::Panic(sol::optional<tstring> maybe_msg)
{
	if (!maybe_msg.has_value()) return;

	tcout << "Lua error: " << maybe_msg.value() << '\n';
}
