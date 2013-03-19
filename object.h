//
//  object.h
//  GravitySim
//
//  Created by Krzysztof Gabis on 24.01.2013.
//  Copyright (c) 2013 Krzysztof Gabis. All rights reserved.
//

#ifndef GravitySim_object_h
#define GravitySim_object_h

#include <stdbool.h>
#include "basic_types.h"

typedef struct {
    Point2D position;
    Point2D speed;
    GS_FLOAT mass;
} Object;

Object object_add(Object a, Object b);
Object object_make(Point2D position, Point2D speed, GS_FLOAT mass);
Object object_make_random(RectangleD bounds, GS_FLOAT max_speed, GS_FLOAT max_mass);
Object object_make_random_in_ellipse(RectangleD bounds, GS_FLOAT max_speed, GS_FLOAT max_mass);
Object object_zero();
Point2D object_calculate_force(Object a, Object b);
void object_update_position(Object *object, GS_FLOAT dt);

#endif
