#include "PainterBinding.h"

void PainterBinding::FillWindowRect(Color color)
{
	GAME_ENGINE->FillWindowRect(color.ToWinType());
}

void PainterBinding::SetColor(Color color)
{
	GAME_ENGINE->SetColor(color.ToWinType());
}

void PainterBinding::SetFont(Font* fontPtr)
{
	GAME_ENGINE->SetFont(fontPtr);
}

void PainterBinding::DrawLine(Vector2l start, Vector2l end)
{
	GAME_ENGINE->DrawLine(start.x, start.y, end.x, end.y);
}

void PainterBinding::DrawRect(Vector2l topLeft, Vector2l bottomRight)
{
	GAME_ENGINE->DrawRect(topLeft.x, topLeft.y, bottomRight.x, bottomRight.y);
}

void PainterBinding::FillRect(Vector2l topLeft, Vector2l bottomRight, int opacity)
{
	GAME_ENGINE->FillRect(topLeft.x, topLeft.y, bottomRight.x, bottomRight.y, opacity);
}

void PainterBinding::DrawRoundRect(Vector2l topLeft, Vector2l bottomRight, int radius)
{
	GAME_ENGINE->DrawRoundRect(topLeft.x, topLeft.y, bottomRight.x, bottomRight.y, radius);
}

void PainterBinding::FillRoundRect(Vector2l topLeft, Vector2l bottomRight, int radius)
{
	GAME_ENGINE->FillRoundRect(topLeft.x, topLeft.y, bottomRight.x, bottomRight.y, radius);
}

void PainterBinding::DrawOval(Vector2l topLeft, Vector2l bottomRight)
{
	GAME_ENGINE->DrawOval(topLeft.x, topLeft.y, bottomRight.x, bottomRight.y);
}

void PainterBinding::FillOval(Vector2l topLeft, Vector2l bottomRight, int opacity)
{
	GAME_ENGINE->FillOval(topLeft.x, topLeft.y, bottomRight.x, bottomRight.y, opacity);
}

void PainterBinding::DrawArc(Vector2l topLeft, Vector2l bottomRight, int startDegree, int angle)
{
	GAME_ENGINE->DrawArc(topLeft.x, topLeft.y, bottomRight.x, bottomRight.y, startDegree, angle);
}

void PainterBinding::FillArc(Vector2l topLeft, Vector2l bottomRight, int startDegree, int angle)
{
	GAME_ENGINE->FillArc(topLeft.x, topLeft.y, bottomRight.x, bottomRight.y, startDegree, angle);
}

void PainterBinding::DrawString(const tstring &text, Vector2l topLeft)
{
	GAME_ENGINE->DrawString(text, topLeft.x, topLeft.y);
}

void PainterBinding::DrawStringSized(const tstring &text, Vector2l topLeft, Vector2l bottomRight)
{
	GAME_ENGINE->DrawString(text, topLeft.x, topLeft.y, bottomRight.x, bottomRight.y);
}

void PainterBinding::DrawBitmap(const Bitmap *bitmapPtr, Vector2l topLeft)
{
	GAME_ENGINE->DrawBitmap(bitmapPtr, topLeft.x, topLeft.y);
}

void PainterBinding::DrawBitmapSourced(const Bitmap *bitmapPtr, Vector2l topLeft, Vector2l sourceTopLeft, Vector2l sourceBottomRight)
{
	RECT src;
	src.left = sourceTopLeft.x;
	src.top = sourceTopLeft.y;
	src.bottom = sourceBottomRight.y;
	src.right = sourceBottomRight.x;

	GAME_ENGINE->DrawBitmap(bitmapPtr, topLeft.x, topLeft.y, src);
}

void PainterBinding::DrawPolygon(std::vector<Vector2l> points, bool close)
{
	std::vector<POINT> winPoints{ points.size() };
	std::transform(points.begin(), points.end(), winPoints.begin(), [](Vector2l point)
	{
		POINT winPoint;
		winPoint.x = point.x;
		winPoint.y = point.y;
		return winPoint;
	});

	GAME_ENGINE->DrawPolygon(winPoints.data(), points.size(), close);
}

void PainterBinding::FillPolygon(std::vector<Vector2l> points, bool close)
{
	std::vector<POINT> winPoints{ points.size() };
	std::transform(points.begin(), points.end(), winPoints.begin(), [](Vector2l point)
	{
		POINT winPoint;
		winPoint.x = point.x;
		winPoint.y = point.y;
		return winPoint;
	});

	GAME_ENGINE->FillPolygon(winPoints.data(), points.size(), close);
}

std::unique_ptr<Bitmap> PainterBinding::CreateBitmap(const tstring& filename, bool createAlphaChannel)
{
	try
	{
		return std::make_unique<Bitmap>(filename, createAlphaChannel);
	}
	catch (const FileNotFoundException& e)
	{
		return nullptr;
	}
}

std::unique_ptr<Font> PainterBinding::CreateFontRef(const tstring &fontName, bool bold, bool italic, bool underline, int size)
{
	return std::make_unique<Font>(fontName, bold, italic, underline, size);
}
