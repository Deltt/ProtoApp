#include "canvas_navigator.hpp"

//CanvasNavigator::CanvasNavigator() = default;
CanvasNavigator::CanvasNavigator()
{
    canvas_camera = { 0 };
	canvas_camera.target = (Vector2){ 0, 0 };
    canvas_camera.offset = (Vector2){ 0, 0 };
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
		Vector2 mouseWorldPosBeforeZoom = GetScreenToWorld2D(GetMousePosition(), canvas_camera);

		canvas_camera.zoom += wheel_scroll * canvas_camera.zoom * 0.05f;
		if (canvas_camera.zoom < 0.1f) canvas_camera.zoom = 0.1f;
		if (canvas_camera.zoom > 5.0f) canvas_camera.zoom = 5.0f;
		zoom_modifier = 1.0f / canvas_camera.zoom;

		Vector2 mouseWorldPosAfterZoom = GetScreenToWorld2D(GetMousePosition(), canvas_camera);

		canvas_camera.target.x += mouseWorldPosBeforeZoom.x - mouseWorldPosAfterZoom.x;
		canvas_camera.target.y += mouseWorldPosBeforeZoom.y - mouseWorldPosAfterZoom.y;

		request_canvas_update = true;
	}

}

void CanvasNavigator::pan()
{
	bool wheel_pressed = IsMouseButtonDown(MOUSE_MIDDLE_BUTTON);
	Vector2 mouse_movement = GetMouseDelta();

	if(wheel_pressed) {
		canvas_camera.offset = Vector2Add(canvas_camera.offset, mouse_movement);
		canvas_camera.offset.x = roundf(canvas_camera.offset.x);
		canvas_camera.offset.y = roundf(canvas_camera.offset.y);
		request_canvas_update = true;
	}
}

void CanvasNavigator::loadFonts()
{
	font[0] = LoadFontEx("../fonts/Pragmatica.ttf", 128, 0, 95);
}