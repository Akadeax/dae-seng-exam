#include "Painter.h"

void Painter::FillWindowRect(Color color)
{
	GAME_ENGINE->FillWindowRect(color.ToWinType());
}

void Painter::SetColor(Color color)
{
	GAME_ENGINE->SetColor(color.ToWinType());
}

void Painter::DrawLine(Vector2l start, Vector2l end)
{
	GAME_ENGINE->DrawLine(start.x, start.y, end.x, end.y);
}
