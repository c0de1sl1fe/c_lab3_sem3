#pragma once
#include <string>
#include <memory>


namespace Internal {
	struct GraphicsInternals;
}


class Graphics
{
	struct Color {
		int R, G, B;
	};

	std::unique_ptr<Internal::GraphicsInternals> _internals;
public:
	Graphics(size_t w = 500, size_t h = 500);
	void DrawLine(float x1, float y1, float x2, float y2, Color color = { 0,0,0 });
	void DrawRectangle(float x1, float y1, float x2, float y2, Color color = { 0,0,0 });
	void DrawSquare(float x, float y, float a = 10, Color color = { 0,0,0 });
	~Graphics();
};

