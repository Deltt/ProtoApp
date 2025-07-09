#pragma once
#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include <vector>
#include <optional>
#include <stack>
#include <boost/geometry.hpp>
#include <boost/geometry/index/rtree.hpp>
#include "canvas_node.hpp"

using Point = boost::geometry::model::point<float, 2, boost::geometry::cs::cartesian>;
using Box = boost::geometry::model::box<Point>;
using Entry = std::pair<Box, unsigned int>;


class DataManager
{
	public:
		static DataManager& getInstance();

		DataManager(const DataManager&) = delete;
		DataManager& operator=(const DataManager&) = delete;

		void initializeData();
		void clearData();

		const std::vector<std::optional<CanvasNode>>& getCanvasNodes() const;
		const boost::geometry::index::rtree<Entry, boost::geometry::index::quadratic<32>>& getTree() const;

		size_t addNode(CanvasNode&& p_node);
		std::vector<int> queryRect(Rectangle p_rect);

	private:
		DataManager();
		~DataManager();

		std::vector<std::optional<CanvasNode>> canvas_items;
		std::stack<size_t> free_canvas_item_indices;
		boost::geometry::index::rtree<Entry, boost::geometry::index::quadratic<32>> canvas_spatial_tree;
};

#endif