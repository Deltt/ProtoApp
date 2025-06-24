#include "data_manager.hpp"

DataManager::DataManager()
{
	initializeData();
}

DataManager::~DataManager() = default;

DataManager& DataManager::getInstance()
{
    static DataManager instance;
    return instance;
}

void DataManager::initializeData() {
	canvas_items.reserve(128);
	canvas_items.push_back(CanvasItem({0, 0, 400, 200}));
}

void DataManager::clearData() {
	canvas_items.clear();
}

const std::vector<CanvasItem>& DataManager::getCanvasItems() const {
	return canvas_items;
}