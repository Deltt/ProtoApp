#pragma once
#ifndef R_TREE_H
#define R_TREE_H

#include <vector>
#include <cfloat>
#include "raylib.h"


const int MAX_CHILDREN = 8;

struct RTree
{

    Node* root;

    RTree();

};

struct alignas(64) Node
{
    Node* parent;
    void* children[MAX_CHILDREN];
    float bb_min_x, bb_min_y, bb_max_x, bb_max_y;
	unsigned int object_indices[MAX_CHILDREN];
    unsigned int count;
    bool is_leaf;
};

struct alignas(32) Entry
{
    Node* parent;
    float min_x, min_y, max_x, max_y;
    unsigned int object_index;
};

#endif