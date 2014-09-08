//
//  build_config.h
//  GravitySim
//
//  Created by Krzysztof Gabis on 25.01.2013.
//  Copyright (c) 2013 Krzysztof Gabis. All rights reserved.
//

#ifndef GravitySim_build_config_h
#define GravitySim_build_config_h

#define MAX_FPS 23.0

#define WINDOW_W 600
#define WINDOW_H 600
#define BORDER 200
#define WINDOW_BOUNDS rectangled_make(0, 0, WINDOW_W, WINDOW_H)
#define MODEL_BOUNDS rectangled_make(-BORDER, -BORDER, WINDOW_W+BORDER, WINDOW_H+BORDER)

#define GS_INLINE inline
#define GS_FLOAT  float

#define CONST_TIME 0.1
#define OBJECT_NUM 1000
#define GALAXY_NUM 4
#define GALAXY_SIZE 100
#define G_CONST 10.5
#define SOFT_CONST 1.0

#define DRAW_SOLID  0
#define DRAW_BIG    0
#define DRAW_DARKEN 1
#define DARKEN_STEP 0.3

#define DRAW_QUADS   0
#define PRINT_FPS    0

#define MAX_SPEED 10.00
#define MAX_MASS 10.0
#define SD_TRESHOLD 1.0

#endif
