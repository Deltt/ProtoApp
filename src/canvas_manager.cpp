#include "canvas_manager.hpp"

//CanvasManager::CanvasManager() = default;
CanvasManager::CanvasManager()
{

}

CanvasManager::~CanvasManager() = default;

CanvasManager& CanvasManager::getInstance() {
    static CanvasManager instance;
    return instance;
}