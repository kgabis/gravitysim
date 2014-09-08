//
//  QuadTree.h
//  GravitySim
//
//  Created by Krzysztof Gabis on 24.01.2013.
//  Copyright (c) 2013 Krzysztof Gabis. All rights reserved.
//

#ifndef GravitySim_QuadTree_h
#define GravitySim_QuadTree_h

#include "basic_types.h"
#include "object.h"
#include "object_array.h"

typedef struct quadtree_t {
    struct quadtree_t *children[4];
    RectangleD bounds;
    Object com;
    Object *object;
    char has_children;
} QuadTree;

QuadTree* quadtree_init(RectangleD bounds);
void quadtree_add_objects(QuadTree *tree, ObjectArray *objects);
void quadtree_apply_to_objects(QuadTree *tree, ObjectArray *objects, GS_FLOAT dt);
void quadtree_dealloc(QuadTree *tree);

#endif
