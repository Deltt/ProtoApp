#include <r_tree.hpp>
#include <algorithm>
#include <stdexcept>

RTree::RTree()
{
	root = new Node{};
	root->count = 0;
	root->bb_min_x = root->bb_min_y = FLT_MAX;
	root->bb_max_x = root->bb_max_y = -FLT_MAX;
	root->parent = nullptr;
	root->is_leaf = true;
}