#pragma once
#ifndef CANVAS_NAVIGATOR_H
#define CANVAS_NAVIGATOR_H

#include "raylib.h"

class CanvasNavigator
{
	public:
		static CanvasNavigator& getInstance();

		CanvasNavigator(const CanvasNavigator&) = delete;
		CanvasNavigator& operator=(const CanvasNavigator&) = delete;

		Vector2 canvas_bounds;
		Camera2D canvas_camera;
		float zoom_modifier;

		void process();
		Vector2 getWorldMousePosition();
		void navigate();
		void zoom();
		void pan();
		

	private:
		CanvasNavigator();
		~CanvasNavigator();
};

#endif