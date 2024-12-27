#pragma once
#include <cstdint>
#include <windows.h>
#include "GameEngine.h"

typedef uint8_t Color_t;

class Color
{
public:
	Color_t r{}, g{}, b{};

	Color() {}
	Color(Color_t r, Color_t g, Color_t b);

	COLORREF ToWinType()
	{
		return RGB(r, g, b);
	}
};
