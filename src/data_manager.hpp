#pragma once
#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include <vector>
#include "canvas_item.hpp"

class DataManager
{
	public:
		static DataManager& getInstance();

		DataManager(const DataManager&) = delete;
		DataManager& operator=(const DataManager&) = delete;

		void initializeData();
		void clearData();
		const std::vector<CanvasItem>& getCanvasItems() const;

	private:
		DataManager();
		~DataManager();

		std::vector<CanvasItem> canvas_items;
};


#endif