//
//  QuadTree.c
//  GravitySim
//
//  Created by Krzysztof Gabis on 24.01.2013.
//  Copyright (c) 2013 Krzysztof Gabis. All rights reserved.
//

#include <stdbool.h>
#include <stdlib.h>
#include "quad_tree.h"
#include "build_config.h"

static void quadtree_add_object(QuadTree *tree, Object *object);

QuadTree* quadtree_init(RectangleD bounds) {
    QuadTree *tree = (QuadTree*)malloc(sizeof(QuadTree));
    if (!tree) {
        return NULL;
    }
    tree->bounds = bounds;
    for (int i = 0; i < 4; i++) {
        tree->children[i] = NULL;
    }
    tree->object = NULL;
    tree->has_children = 0;
    tree->com = object_zero();
    return tree;
}

void quadtree_add_object(QuadTree *tree, Object *object) {
    int q;
    if (!tree) {
        return;
    }
    if (tree->has_children) {
        q = point2d_nquad_of_rectangled(object->position, tree->bounds);
        if (tree->children[q]) {
            quadtree_add_object(tree->children[q], object);
        } else {
            tree->children[q] = quadtree_init(rectangled_nquad(tree->bounds, q));
            quadtree_add_object(tree->children[q], object);
        }
        tree->com = object_add(tree->com, *object);
    } else {
        if (tree->object) {
            q = point2d_nquad_of_rectangled(object->position, tree->bounds);
            if (!tree->children[q]) {
                tree->children[q] = quadtree_init(rectangled_nquad(tree->bounds, q));
            }
            quadtree_add_object(tree->children[q], object);
            
            q = point2d_nquad_of_rectangled(tree->object->position, tree->bounds);
            if (!tree->children[q]) {
                tree->children[q] = quadtree_init(rectangled_nquad(tree->bounds, q));
            }
            quadtree_add_object(tree->children[q], tree->object);
            
            tree->has_children = 1;
            tree->object = NULL;
            tree->com = object_add(tree->com, *object);
        } else {
            tree->object = object;
            tree->com = *object;
        }
    }
}

Point2D quadtree_get_force_on_object(QuadTree *tree, Object *object) {
    GS_FLOAT s, d;
    Point2D dr, result = point2d_zero();    
    if (!tree->has_children) {
        if (tree->object != object) {
            result = object_calculate_force(*object, tree->com);
        }
    } else {
        s = MAX(tree->bounds.size.x, tree->bounds.size.y);
        dr = point2d_sub(object->position, tree->com.position);
        d = point2d_length(dr);
        if ((s/d) < SD_TRESHOLD) {
            result = object_calculate_force(*object, tree->com);
        } else {
            result = point2d_zero();
            for (int i = 0; i < 4; i++) {
                if (tree->children[i] != NULL) {
                    result = point2d_add(result,
                                         quadtree_get_force_on_object(tree->children[i], object));
                }
            }
        }
    }
    return result;
}

void quadtree_apply_to_objects(QuadTree *tree, ObjectArray *objects, GS_FLOAT dt) {
    size_t i;
    Object *object;
    for (i = 0; i < objects->len; i++) {
        object = &objects->objects[i];
        Point2D acc = quadtree_get_force_on_object(tree, object);
        Point2D dv = point2d_multiply(acc, dt);
        object->speed = point2d_add(object->speed, dv);
    }    
}

void quadtree_add_objects(QuadTree *tree, ObjectArray *objects) {
    size_t i;
    for (i = 0; i < objects->len; i++) {
        if (point2d_is_in_rectangled(objects->objects[i].position, tree->bounds)) {
            quadtree_add_object(tree, &objects->objects[i]);
        }
    }
}

void quadtree_dealloc(QuadTree *tree) {
    for (int i = 0; i < 4; i++) {
        if (tree->children[i]) {
            quadtree_dealloc(tree->children[i]);
        }
    }
    free(tree);
}


