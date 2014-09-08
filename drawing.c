//
//  drawing.c
//  GravitySim
//
//  Created by Krzysztof Gabis on 23.01.2013.
//  Copyright (c) 2013 Krzysztof Gabis. All rights reserved.
//

#include <stdio.h>
#include <GL/glfw.h>
#include "drawing.h"

void draw_darken_pixel_bw(Screen *screen, int x, int y, float step) {
    if (x < 0 ||
        y < 0 ||
        x >= screen->width ||
        y >= screen->height) {
        return;
    }
    float color = draw_get_pixel(screen, x, y).red;
    color = color - step;
    color = MAX(0, color);
    draw_set_pixel(screen, x, y, rgbcolor_make(color, color, color));
}

void draw_darken_pixel(Screen *screen, int x, int y, float step) {
    if (x < 0 ||
        y < 0 ||
        x >= screen->width ||
        y >= screen->height) {
        return;
    }
    RGBColor color = draw_get_pixel(screen, x, y);
    color.red = color.red - step;
    color.red = MAX(0, color.red);
    color.green = color.green - step;
    color.green = MAX(0, color.green);
    color.blue = color.blue - step;
    color.blue = MAX(0, color.blue);
    draw_set_pixel(screen, x, y, color);
}

void draw_lighten_pixel(Screen *screen, int x, int y, float step) {
    if (x < 0 ||
        y < 0 ||
        x >= screen->width ||
        y >= screen->height) {
        return;
    }
    RGBColor color = draw_get_pixel(screen, x, y);
    color.red = color.red + step;
    color.red = MIN(1.0, color.red);
    color.green = color.green + step;
    color.green = MIN(1.0, color.green);
    color.blue = color.blue + step;
    color.blue = MIN(1.0, color.blue);
    draw_set_pixel(screen, x, y, color);
}

GS_INLINE void draw_set_pixel(Screen *screen, int x, int y, RGBColor color) {
    if (x < 0 ||
        y < 0 ||
        x >= screen->width ||
        y >= screen->height) {
        return;
    }
    int index = y * screen->width + x;
    screen->pixels[index] = color;
}

GS_INLINE RGBColor draw_get_pixel(Screen *screen, int x, int y) {
    if (x < 0 ||
        y < 0 ||
        x >= screen->width ||
        y >= screen->height) {
        return RGB_WHITE;
    }
    int index = y * screen->width + x;
    return screen->pixels[index];
}

void draw_rectangle(Screen *screen, RectangleI r, RGBColor color) {
    for (int x = r.origin.x; x < r.origin.x + r.size.x; x++) {
        for (int y = r.origin.y; y < r.origin.y + r.size.y; y++) {
            draw_set_pixel(screen, x, y, color);
        }
    }
}

void draw_empty_rectangle(Screen *screen, RectangleD rect, RGBColor color) {
    int x, y;
    Point2D end = point2d_add(rect.origin, rect.size);
    for (x = rect.origin.x; x < end.x; x++) {
        draw_set_pixel(screen, x, rect.origin.y, color);
        draw_set_pixel(screen, x, end.y, color);
    }
    for (y = rect.origin.y; y < end.y; y++) {
        draw_set_pixel(screen, rect.origin.x, y, color);
        draw_set_pixel(screen, end.x, y, color);
    }

}
