//
//  graphic_types.h
//  GravitySim
//
//  Created by Krzysztof Gabis on 23.01.2013.
//  Copyright (c) 2013 Krzysztof Gabis. All rights reserved.
//

#ifndef GravitySim_graphic_types_h
#define GravitySim_graphic_types_h

#define RGB_WHITE rgbcolor_make(1.0, 1.0, 1.0)
#define RGB_BLACK rgbcolor_make(0.0, 0.0, 0.0)
#define RGB_RED rgbcolor_make(1.0, 0.0, 0.0)
#define RGB_GREEN rgbcolor_make(0.0, 1.0, 0.0)
#define RGB_BLUE rgbcolor_make(0.0, 0.0, 1.0)

#define SQUARE(x) ((x)*(x))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

#include "build_config.h"
#include <math.h>

typedef struct {
    int x;
    int y;
} PointI;

typedef struct {
    PointI origin;
    PointI size;
} RectangleI;

typedef struct {
    GS_FLOAT x;
    GS_FLOAT y;
} Point2D;

typedef struct {
    Point2D origin;
    Point2D size;
    Point2D middle;
} RectangleD;

typedef struct {
    float red;
    float green;
    float blue;
} RGBColor;

double fastPow(double a, double b);
Point2D point2d_make_random(RectangleD bounds);
Point2D point2d_make_random_in_circle(RectangleD bounds);

// Functions to inline
static GS_INLINE PointI pointi_make(int x, int y) {
    PointI point;
    point.x = x;
    point.y = y;
    return point;
}

static GS_INLINE RectangleI rectanglei_make_with_points(PointI origin, PointI size) {
    RectangleI rect;
    rect.origin = origin;
    rect.size = size;
    return rect;
}

static GS_INLINE RectangleI rectanglei_make(int x1, int y1, int x2, int y2) {
    return rectanglei_make_with_points(pointi_make(x1, y1), pointi_make(x2, y2));
}

static GS_INLINE Point2D point2d_make(GS_FLOAT x, GS_FLOAT y) {
    Point2D point;
    point.x = x;
    point.y = y;
    return point;
}

static GS_INLINE Point2D point2d_zero() {
    return point2d_make(0.0, 0.0);
}

static GS_INLINE Point2D point2d_add(Point2D a, Point2D b) {
    return point2d_make(a.x + b.x, a.y + b.y);
}

static GS_INLINE Point2D point2d_sub(Point2D a, Point2D b) {
    return point2d_make(a.x - b.x, a.y - b.y);
}

static GS_INLINE Point2D point2d_multiply(Point2D a, GS_FLOAT x) {
    return point2d_make(a.x * x, a.y * x);
}

static GS_INLINE int point2d_is_in_rectangled(Point2D point, RectangleD rect) {
    return point.x >= rect.origin.x
        && point.x < (rect.size.x + rect.origin.x)
        && point.y >= rect.origin.y
        && point.y < (rect.size.y + rect.origin.y);
}

static GS_INLINE Point2D point2d_rotate_90_ccw(Point2D p) {
    return point2d_make(-p.y, p.x);
}

static GS_INLINE  GS_FLOAT point2d_length(Point2D p) {
    return sqrt((p.x * p.x) + (p.y * p.y));
}

static GS_INLINE  Point2D point2d_unit(Point2D p) {
    return point2d_multiply(p, 1.0 / point2d_length(p));
}

static GS_INLINE int point2d_nquad_of_rectangled(Point2D p, RectangleD r) {
    return ((p.y >= r.middle.y) << 1) | (p.x >= r.middle.x);
}

static GS_INLINE RectangleD rectangled_make_with_point2ds(Point2D origin, Point2D size) {
    RectangleD rect;
    rect.origin = origin;
    rect.size = size;
    rect.middle = point2d_make(origin.x + (size.x / 2), origin.y + (size.y / 2));
    return rect;
}

static GS_INLINE RectangleD rectangled_make(GS_FLOAT x, GS_FLOAT y, GS_FLOAT size_x, GS_FLOAT size_y) {
    return rectangled_make_with_point2ds(point2d_make(x, y),
                                         point2d_make(size_x, size_y));
}

static GS_INLINE RectangleD rectangled_nquad(RectangleD rect, int quarter) {
    Point2D start = rect.origin;
    Point2D end = point2d_add(rect.origin, rect.size);
    Point2D quarter_size = point2d_multiply(point2d_sub(end, rect.origin), 0.5);
    Point2D middle = rect.middle;
    switch (quarter) {
        case 0:
            return rectangled_make_with_point2ds(start, quarter_size);
        case 1:
            return rectangled_make(middle.x, start.y, quarter_size.x, quarter_size.y);
        case 2:
            return rectangled_make(start.x, middle.y, quarter_size.x, quarter_size.y);
        case 3: default:
            return rectangled_make_with_point2ds(middle, quarter_size);
    }
}

static GS_INLINE RGBColor rgbcolor_make(float red, float green, float blue) {
    RGBColor color;
    color.red = red;
    color.green = green;
    color.blue = blue;
    return color;
}

#endif
