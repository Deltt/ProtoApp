#pragma once
#ifndef CANVAS_RENDERER_H
#define CANVAS_RENDERER_H

#include "raylib.h"

class CanvasRenderer
{
	public:
		static CanvasRenderer& getInstance();

		CanvasRenderer(const CanvasRenderer&) = delete;
		CanvasRenderer& operator=(const CanvasRenderer&) = delete;

		RenderTexture2D canvas_texture;
		RenderTexture2D menu_texture;
		bool request_canvas_update;
		int last_screen_width;
		int last_screen_height;
		int canvas_updates {0};
		int drawn_elements;
		Font font_pragmatica_10;
		Font font_pragmatica_20;
		const Color BACKGROUND_COLOR {200, 200, 200, 255};

		void process();
		void handleWindowResize(int& p_last_screen_width, int& p_last_screen_height);
		void resizeCanvas(int p_resize_width, int p_resize_height);
		void updateCanvas(Camera2D& p_camera);
		void updateMenu();
		void drawPass();
		void loadFonts();
		void drawCanvasNodes();
		void drawDebugInfo();
		

	private:
		CanvasRenderer();
		~CanvasRenderer();
};

#endif