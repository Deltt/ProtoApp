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

void DataManager::initializeData()
{
	canvas_items.reserve(512);
	addNode(CanvasNode{0.0f, 0.0f, 300.0f, 300.0f});
}

void DataManager::clearData()
{
	canvas_items.clear();
}

const std::vector<std::optional<CanvasNode>>& DataManager::getCanvasNodes() const
{
	return canvas_items;
}

const boost::geometry::index::rtree<Entry, boost::geometry::index::quadratic<32>>& DataManager::getTree() const
{
	return canvas_spatial_tree;
}

size_t DataManager::addNode(CanvasNode&& p_node)
{
	size_t node_index;

	if(!free_canvas_item_indices.empty())
	{
		size_t i = free_canvas_item_indices.top();
		free_canvas_item_indices.pop();
		canvas_items[i] = std::move(p_node);
		node_index = i;
	}
	else
	{
		canvas_items.push_back(std::move(p_node));
		node_index = canvas_items.size() - 1;
	}

	Box b {{p_node.rect.x, p_node.rect.y}, {p_node.rect.x + p_node.rect.width, p_node.rect.y + p_node.rect.height}};
	canvas_spatial_tree.insert(std::make_pair(b, node_index));
	
	return node_index;
}