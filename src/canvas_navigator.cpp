#include "canvas_navigator.hpp"

//CanvasNavigator::CanvasNavigator() = default;
CanvasNavigator::CanvasNavigator()
{
	canvas_bounds = {1920, 1080};
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

void CanvasNavigator::process()
{
	navigate();
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
		float min_zoom = 0.125f;
		float max_zoom = 20.0f;

		Vector2 mouse_world_position_pre_zoom = GetScreenToWorld2D(GetMousePosition(), canvas_camera);

		canvas_camera.zoom += wheel_scroll * canvas_camera.zoom * 0.05f;
		canvas_camera.zoom = Clamp(canvas_camera.zoom, min_zoom, max_zoom);

		Vector2 mouse_world_position_post_zoom = GetScreenToWorld2D(GetMousePosition(), canvas_camera);

		zoom_modifier = 1.0f / canvas_camera.zoom;

		request_canvas_update = true;

		if(canvas_camera.zoom == max_zoom) return;
		if(canvas_camera.zoom == min_zoom) return;

		if(wheel_scroll>0) {
			Vector2 mouse_delta = Vector2Subtract(mouse_world_position_post_zoom, mouse_world_position_pre_zoom);
			canvas_camera.target = Vector2Subtract(canvas_camera.target, mouse_delta);
		}
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

		request_canvas_update = true;
	}
}