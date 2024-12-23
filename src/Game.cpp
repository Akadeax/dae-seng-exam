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

	SetupContext setupContext{ TEXT("Default Name"), 800, 600 };
	auto luaSetupFn{ state["setup"] };
	if(luaSetupFn.valid())
	{
		auto setupResult = luaSetupFn(setupContext);
		if(!setupResult.valid())
		{
			const sol::error err = setupResult;
			throw std::exception(err.what());
		}
	}

	GAME_ENGINE->SetTitle(setupContext.getWindowTitle());

	GAME_ENGINE->SetWidth(setupContext.getWindowWidth());
	GAME_ENGINE->SetHeight(setupContext.getWindowHeight());
	GAME_ENGINE->SetFrameRate(50);

	// Set the keys that the game needs to listen to
	//tstringstream buffer;
	//buffer << _T("KLMO");
	//buffer << (char) VK_LEFT;
	//buffer << (char) VK_RIGHT;
	//GAME_ENGINE->SetKeyList(buffer.str());
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
	// Insert paint code
}

void Game::Tick()
{
	// Insert non-paint code that needs to execute each tick
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
}

void Game::KeyPressed(TCHAR key)
{
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

	state.new_usertype<Vector2l>(
		"Vector2l",
		sol::constructors<Vector2l(Vector2l_t, Vector2l_t)>{},
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

	// state.new_usertype<Painter>(
	// 	"Painter",
	// 	"draw_rectangle", &Painter::DrawRectangle
	// );

	state.new_usertype<SetupContext>(
        "SetupContext",
        "set_window_size", &SetupContext::setWindowSize,
        "set_window_title", &SetupContext::setWindowTitle,
        "get_window_title", &SetupContext::getWindowTitle,
        "get_window_width", &SetupContext::getWindowWidth,
        "get_window_height", &SetupContext::getWindowHeight
    );
}
