#pragma once
#include "raylib.h"
#include <raymath.h>

class CanvasNavigator {
public:
    static CanvasNavigator& getInstance();

	Camera2D canvas_camera;
	float zoom_modifier;
	bool request_canvas_update;
	Font font[1];

    CanvasNavigator(const CanvasNavigator&) = delete;
    CanvasNavigator& operator=(const CanvasNavigator&) = delete;

	Vector2 getWorldMousePosition();
	void navigate();
	void zoom();
	void pan();
	void loadFonts();

private:
    CanvasNavigator();
    ~CanvasNavigator();
};