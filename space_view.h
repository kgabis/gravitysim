//
//  space_view.h
//  GravitySim
//
//  Created by Krzysztof Gabis on 24.01.2013.
//  Copyright (c) 2013 Krzysztof Gabis. All rights reserved.
//

#ifndef GravitySim_space_view_h
#define GravitySim_space_view_h

#include <stdlib.h>

#include "object.h"
#include "screen.h"
#include "object_array.h"
#include "quad_tree.h"

typedef struct {
    Screen *screen;
} SpaceView;

SpaceView * spaceview_init(RectangleD bounds);
void spaceview_clear(SpaceView *view);
void spaceview_draw_objects(SpaceView *view, ObjectArray *objects);
void spaceview_draw_quadtree(SpaceView *view, QuadTree *tree);
void spaceview_dealloc(SpaceView *view);
void spaceview_display(SpaceView *view);
#endif
