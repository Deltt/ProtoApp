#pragma once
#ifndef CANVAS_MANAGER_H
#define CANVAS_MANAGER_H

class CanvasManager
{
	public:
		static CanvasManager& getInstance();

		CanvasManager(const CanvasManager&) = delete;
		CanvasManager& operator=(const CanvasManager&) = delete;

	private:
		CanvasManager();
		~CanvasManager();
};

#endif