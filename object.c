//
//  object.c
//  GravitySim
//
//  Created by Krzysztof Gabis on 24.01.2013.
//  Copyright (c) 2013 Krzysztof Gabis. All rights reserved.

#include <math.h>
#include <stdlib.h>
#include "object.h"
#include "build_config.h"

Object object_add(Object a, Object b) {
    GS_FLOAT mass = a.mass + b.mass;
    Point2D position = point2d_add(point2d_multiply(a.position, a.mass / mass),
                             point2d_multiply(b.position, b.mass / mass));
    Point2D speed = point2d_add(point2d_multiply(a.speed, a.mass / mass),
                                point2d_multiply(b.speed, b.mass / mass));
    return object_make(position, speed, mass);
}

Object object_make(Point2D position, Point2D speed, GS_FLOAT mass) {
    Object obj;
    obj.position = position;
    obj.speed = speed;
    obj.mass = mass;
    return obj;
}

Object object_make_random(RectangleD bounds, GS_FLOAT max_speed, GS_FLOAT max_mass) {
    Point2D position = point2d_make_random(bounds);
    Point2D speed;
    speed.x = (((GS_FLOAT)rand()/(GS_FLOAT)RAND_MAX) - 0.5) * 2 * max_speed;
    speed.y = (((GS_FLOAT)rand()/(GS_FLOAT)RAND_MAX) - 0.5) * 2 * max_speed;
    GS_FLOAT mass = ((GS_FLOAT)rand()/(GS_FLOAT)RAND_MAX) * max_mass;
    return object_make(position, speed, mass);
}

Object object_make_random_in_ellipse(RectangleD bounds, GS_FLOAT max_speed, GS_FLOAT max_mass) {
    Point2D position = point2d_make_random_in_circle(bounds);
    Point2D speed;
    speed.x = (((GS_FLOAT)rand()/(GS_FLOAT)RAND_MAX) - 0.5) * 2 * max_speed;
    speed.y = (((GS_FLOAT)rand()/(GS_FLOAT)RAND_MAX) - 0.5) * 2 * max_speed;
    GS_FLOAT mass = ((GS_FLOAT)rand()/(GS_FLOAT)RAND_MAX) * max_mass;
    return object_make(position, speed, mass);
}

Object object_zero() {
    return object_make(point2d_zero(), point2d_zero(), 0.0);
}

Point2D object_calculate_force(Object a, Object b) {
    Point2D dr;
    GS_FLOAT r, f;
    dr = point2d_sub(b.position, a.position);
    r = (point2d_length(dr) + SOFT_CONST);
    f = G_CONST * b.mass / SQUARE(r); //fastPow(r, GFACTOR);
    return point2d_multiply(dr, f/r);
}

void object_update_position(Object *object, GS_FLOAT dt) {
    Point2D dr = point2d_multiply(object->speed, dt);
    object->position = point2d_add(object->position, dr);
}
