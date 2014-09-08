//
//  space_model.h
//  GravitySim
//
//  Created by Krzysztof Gabis on 24.01.2013.
//  Copyright (c) 2013 Krzysztof Gabis. All rights reserved.
//

#ifndef GravitySim_space_model_h
#define GravitySim_space_model_h

#include <stdlib.h>
#include "object_array.h"
#include "object.h"
#include "quad_tree.h"

typedef struct {
    RectangleD bounds;
    ObjectArray *objects;
    QuadTree *tree;
} SpaceModel;

SpaceModel* spacemodel_init_empty(RectangleD bounds, size_t capacity);
SpaceModel* spacemodel_init_galaxies(RectangleD bounds, RectangleD galaxies_bounds, size_t n_galaxies,
                                     size_t objects_per_galaxy, GS_FLOAT galaxy_size);
void spacemodel_add_galaxy(SpaceModel *m, Point2D position, GS_FLOAT size, size_t n);
void spacemodel_update(SpaceModel *model, GS_FLOAT dt);
void spacemodel_dealloc(SpaceModel *model);

#endif
