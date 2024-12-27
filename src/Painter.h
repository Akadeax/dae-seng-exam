#pragma once
#include "Color.h"
#include "Vectors.h"

class Painter
{
public:
	static void FillWindowRect(Color color);

	static void SetColor(Color color);
	static void DrawLine(Vector2l start, Vector2l end);
};
