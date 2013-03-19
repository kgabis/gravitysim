//
//  drawing.h
//  GravitySim
//
//  Created by Krzysztof Gabis on 23.01.2013.
//  Copyright (c) 2013 Krzysztof Gabis. All rights reserved.
//

#ifndef GravitySim_drawing_h
#define GravitySim_drawing_h

#include "screen.h"
#include "basic_types.h"

void draw_darken_pixel(Screen *screen, int x, int y, float step);
void draw_darken_pixel_bw(Screen *screen, int x, int y, float step);
void draw_lighten_pixel(Screen *screen, int x, int y, float step);
void draw_set_pixel(Screen *screen, int x, int y, RGBColor color);
RGBColor draw_get_pixel(Screen *screen, int x, int y);
void draw_rectangle(Screen *screen, RectangleI rect, RGBColor color);
void draw_empty_rectangle(Screen *screen, RectangleD rect, RGBColor color);

#endif
