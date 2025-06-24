#include "canvas_manager.hpp"

CanvasManager::CanvasManager()
{

}

CanvasManager::~CanvasManager() = default;

CanvasManager& CanvasManager::getInstance()
{
    static CanvasManager instance;
    return instance;
}