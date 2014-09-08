//
//  space_model.c
//  GravitySim
//
//  Created by Krzysztof Gabis on 24.01.2013.
//  Copyright (c) 2013 Krzysztof Gabis. All rights reserved.
//

#include "space_model.h"
#include <stdlib.h>

void spacemodel_remove_objects_outside_bounds(SpaceModel *m);

SpaceModel* spacemodel_init_empty(RectangleD bounds, size_t capacity) {
    SpaceModel *m = (SpaceModel*)malloc(sizeof(SpaceModel));
    if (m == NULL) {
        return NULL;
    }
    m->bounds = bounds;
    m->tree = quadtree_init(m->bounds);
    if (m->tree == NULL) {
        free(m);
        return NULL;
    }
    m->objects = objectarray_init_empty(capacity);
    if (m->objects == NULL) {
        quadtree_dealloc(m->tree);
        free(m);
        return NULL;
    }
    quadtree_add_objects(m->tree, m->objects);
    return m;
}

SpaceModel* spacemodel_init_galaxies(RectangleD bounds, RectangleD galaxies_bounds, size_t n_galaxies,
                                     size_t objects_per_galaxy, GS_FLOAT galaxy_size) {
    SpaceModel *m = spacemodel_init_empty(bounds, objects_per_galaxy * n_galaxies);
    if (m == NULL) {
        return NULL;
    }
    Point2D galaxy_pos;
    size_t i;
    for (i = 0; i < n_galaxies; i++) {
        galaxy_pos.x =  ((GS_FLOAT)rand()/(GS_FLOAT)RAND_MAX) * (galaxies_bounds.size.x - galaxy_size);
        galaxy_pos.y =  ((GS_FLOAT)rand()/(GS_FLOAT)RAND_MAX) * (galaxies_bounds.size.y - galaxy_size);
        spacemodel_add_galaxy(m, galaxy_pos, galaxy_size, objects_per_galaxy);
    }
    m->bounds = bounds;
    quadtree_add_objects(m->tree, m->objects);
    return m;
}

void spacemodel_add_galaxy(SpaceModel *m, Point2D position, GS_FLOAT size, size_t n) {
    size_t i;
    Point2D delta_pos, direction, speed_vector;
    GS_FLOAT distance;
    Object new_object;
    RectangleD bounds = rectangled_make(position.x, position.y, size, size);
    for (i = 0; i < n; i++) {
        new_object = object_make_random_in_ellipse(bounds, 0.0, MAX_MASS);
        delta_pos = point2d_sub(new_object.position, bounds.middle);
        direction = point2d_unit(delta_pos);
        distance = point2d_length(delta_pos);
        speed_vector = point2d_multiply(direction, distance); //yeah, that's primitive
        new_object.speed = point2d_rotate_90_ccw(speed_vector);
        objectarray_add(m->objects, new_object);
    }
}

void spacemodel_remove_objects_outside_bounds(SpaceModel *m) {
    size_t i;
    for (i = 0; i < m->objects->len; i++) {
        if (!point2d_is_in_rectangled(m->objects->objects[i].position, m->bounds)) {
            objectarray_remove_object_at(m->objects, i);
            i--;
        }
    }
}

void spacemodel_update(SpaceModel *m, GS_FLOAT dt) {
    size_t i;
#ifdef CONST_TIME
    dt = CONST_TIME;
#endif
    quadtree_apply_to_objects(m->tree, m->objects, dt);
    for (i = 0; i < m->objects->len; i++) {
        object_update_position(&m->objects->objects[i], dt);
    }
    spacemodel_remove_objects_outside_bounds(m);
    quadtree_dealloc(m->tree);
    m->tree = quadtree_init(m->bounds);
    quadtree_add_objects(m->tree, m->objects);
}

void spacemodel_dealloc(SpaceModel *m) {
    objectarray_dealloc(m->objects);
    quadtree_dealloc(m->tree);
    free(m);
}


