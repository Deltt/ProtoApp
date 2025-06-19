#include "canvas_navigator.hpp"

//CanvasNavigator::CanvasNavigator() = default;
CanvasNavigator::CanvasNavigator()
{
	canvas_bounds = {1000, 1000};
    canvas_camera = { 0 };
	canvas_camera.target = (Vector2){ 0, 0 };
    canvas_camera.offset = (Vector2){ 1920 * 0.5f, 1080 * 0.5f };
    canvas_camera.rotation = 0.0f;
    canvas_camera.zoom = 1.0f;

	zoom_modifier = 1.0f;
	request_canvas_update = true;
}

CanvasNavigator::~CanvasNavigator() = default;

CanvasNavigator& CanvasNavigator::getInstance() {
    static CanvasNavigator instance;
    return instance;
}

Vector2 CanvasNavigator::getWorldMousePosition()
{
	return GetScreenToWorld2D(GetMousePosition(), canvas_camera);
}

void CanvasNavigator::navigate()
{
	zoom();
	pan();
}

void CanvasNavigator::zoom()
{
	float wheel_scroll = GetMouseWheelMove();

	if (wheel_scroll != 0) {
		canvas_camera.zoom += wheel_scroll * canvas_camera.zoom * 0.05f;
		if (canvas_camera.zoom < 0.1f) canvas_camera.zoom = 0.1f;
		if (canvas_camera.zoom > 5.0f) canvas_camera.zoom = 5.0f;
		zoom_modifier = 1.0f / canvas_camera.zoom;

		request_canvas_update = true;
	}
}

void CanvasNavigator::pan()
{
	bool wheel_pressed = IsMouseButtonDown(MOUSE_MIDDLE_BUTTON);
	Vector2 mouse_movement = GetMouseDelta();
	float pan_speed = 0.5f * zoom_modifier;
	mouse_movement *= pan_speed;

	if(wheel_pressed) {
		canvas_camera.target = Vector2Subtract(canvas_camera.target, mouse_movement);
		canvas_camera.target.x = Clamp(canvas_camera.target.x, -canvas_bounds.x, canvas_bounds.x);
		canvas_camera.target.y = Clamp(canvas_camera.target.y, -canvas_bounds.y, canvas_bounds.y);

		canvas_camera.target.x = roundf(canvas_camera.target.x);
		canvas_camera.target.y = roundf(canvas_camera.target.y);

		request_canvas_update = true;
	}
}

void CanvasNavigator::loadFonts()
{
	font[0] = LoadFontEx("../fonts/Pragmatica.ttf", 10, 0, 95);
}