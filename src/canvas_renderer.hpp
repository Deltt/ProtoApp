#pragma once
#ifndef CANVAS_RENDERER_H
#define CANVAS_RENDERER_H

#include "raylib.h"
#include <raymath.h>
#include "globals.hpp"

class CanvasRenderer {
public:
    static CanvasRenderer& getInstance();

    CanvasRenderer(const CanvasRenderer&) = delete;
    CanvasRenderer& operator=(const CanvasRenderer&) = delete;

	RenderTexture2D canvas_texture;
	int last_screen_width;
    int last_screen_height;
	int canvas_updates {0};
	Font font[1];
	const Color BACKGROUND_COLOR {220, 220, 220, 255};

	void process();
	void handleWindowResize(int& last_screen_width, int& last_screen_height);
	void resizeCanvas(int resize_width, int resize_height);
	void updateCanvas(Camera2D& camera);
	void drawCanvas();
	void loadFonts();
	void drawCanvasItems();
	

private:
    CanvasRenderer();
    ~CanvasRenderer();
};

#endif