//
//  graphic_types.c
//  GravitySim
//
//  Created by Krzysztof Gabis on 23.01.2013.
//  Copyright (c) 2013 Krzysztof Gabis. All rights reserved.
//

#include <stdlib.h>

#include "basic_types.h"
#include "build_config.h"

double fastPow(double a, double b) {
    union {
        double d;
        int x[2];
    } u = { a };
    u.x[1] = (int)(b * (u.x[1] - 1072632447) + 1072632447);
    u.x[0] = 0;
    return u.d;
}

void cartesian_to_polar(Point2D p,  GS_FLOAT *r, GS_FLOAT *theta) {
    *r = sqrt(SQUARE(p.x) + SQUARE(p.y));
    *theta = atan(p.y / p.x);
}

Point2D polar_to_cartesian(GS_FLOAT r, GS_FLOAT theta) {
    Point2D p;
    p.x = r * cos(theta);
    p.y = r * sin(theta);
    return p;
}

Point2D point2d_make_random(RectangleD bounds) {
    Point2D point;
    point.x = ((GS_FLOAT)rand()/(GS_FLOAT)RAND_MAX) * bounds.size.x;
    point.y = ((GS_FLOAT)rand()/(GS_FLOAT)RAND_MAX) * bounds.size.y;
    point = point2d_add(point, bounds.origin);
    return point;
}

Point2D point2d_make_random_in_circle(RectangleD b) {
    GS_FLOAT r = ((GS_FLOAT)rand()/(GS_FLOAT)RAND_MAX);
    GS_FLOAT radius = MIN(b.size.x, b.size.y) * r * 0.5;
    GS_FLOAT theta = ((GS_FLOAT)rand()/(GS_FLOAT)RAND_MAX) * 2 * 3.1415;
    Point2D p = polar_to_cartesian(radius, theta);
    if (b.size.x > b.size.y) {
        GS_FLOAT ratio = b.size.x / b.size.y;
        p.x *= ratio;
    } else {
        GS_FLOAT ratio = b.size.y / b.size.x;
        p.y *= ratio;
    }
    Point2D middle = point2d_add(b.origin, point2d_multiply(b.size, 0.5));
    p = point2d_add(p, middle);
    return p;
}

