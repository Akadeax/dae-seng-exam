#pragma once
#include "Color.h"
#include "Vectors.h"
#include <memory>

class PainterBinding
{
public:
	static void FillWindowRect(Color color);

	static void SetColor(Color color);
	static void SetFont(Font* fontPtr);
	static void DrawLine(Vector2l start, Vector2l end);

	static void DrawRect(Vector2l topLeft, Vector2l bottomRight);
	static void FillRect(Vector2l topLeft, Vector2l bottomRight, int opacity);

	static void DrawRoundRect(Vector2l topLeft, Vector2l bottomRight, int radius);
	static void FillRoundRect(Vector2l topLeft, Vector2l bottomRight, int radius);
	static void DrawOval(Vector2l topLeft, Vector2l bottomRight);
	static void FillOval(Vector2l topLeft, Vector2l bottomRight, int opacity);
	static void DrawArc(Vector2l topLeft, Vector2l bottomRight, int startDegree, int angle);
	static void FillArc(Vector2l topLeft, Vector2l bottomRight, int startDegree, int angle);
	static void DrawString(const tstring& text, Vector2l topLeft);
	static void DrawStringSized(const tstring& text, Vector2l topLeft, Vector2l bottomRight);

	static void DrawBitmap(const Bitmap* bitmapPtr, Vector2l topLeft);
	static void DrawBitmapSourced(const Bitmap* bitmapPtr, Vector2l topLeft, Vector2l sourceTopLeft, Vector2l sourceBottomRight);

	static void DrawPolygon(std::vector<Vector2l> points, bool close);
	static void FillPolygon(std::vector<Vector2l> points, bool close);


	static std::unique_ptr<Bitmap> CreateBitmap(const tstring& filename, bool createAlphaChannel);
	static std::unique_ptr<Font> CreateFontRef(const tstring& fontName, bool bold, bool italic, bool underline, int size);
};
