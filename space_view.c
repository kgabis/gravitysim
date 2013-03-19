//
//  space_view.c
//  GravitySim
//
//  Created by Krzysztof Gabis on 24.01.2013.
//  Copyright (c) 2013 Krzysztof Gabis. All rights reserved.
//

#include "space_view.h"
#include "drawing.h"
#include <GL/glfw.h>
#include "build_config.h"

SpaceView * spaceview_init(RectangleD bounds) {
    SpaceView *view = (SpaceView*)malloc(sizeof(SpaceView));
    if (!view) {
        return NULL;
    }
    view->screen = screen_init(bounds.size.x, bounds.size.y);
    if (!view->screen) {
        free(view);
        return NULL;
    }
    return view;
}

void spaceview_clear(SpaceView *view) {    
    screen_fill(view->screen, RGB_WHITE);
}

void spaceview_draw_objects(SpaceView *view, ObjectArray *objects) {
    size_t i;
    Point2D pos;
    for (i = 0; i < objects->len; i++) {
        pos = objects->objects[i].position;
#if DRAW_SOLID
        draw_set_pixel(view->screen, pos.x, pos.y, RGB_BLACK);
#elif DRAW_BIG
        draw_rectangle(view->screen, rectanglei_make(pos.x, pos.y, 3, 3), RGB_BLACK);
#elif DRAW_DARKEN
        draw_darken_pixel_bw(view->screen, pos.x, pos.y, DARKEN_STEP);
#endif
    }
}

void spaceview_display(SpaceView *view) {
    screen_display(view->screen);
}

void spaceview_draw_quadtree(SpaceView *view, QuadTree *tree) {
    for (int i = 0; i < 4; i++) {
        if (tree->children[i]) {
            spaceview_draw_quadtree(view, tree->children[i]);
        }
    }
    draw_empty_rectangle(view->screen, tree->bounds, RGB_BLUE);
}

void spaceview_dealloc(SpaceView *view) {
    screen_dealloc(view->screen);
    free(view);
}