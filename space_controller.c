//
//  space_controller.c
//  GravitySim
//
//  Created by Krzysztof Gabis on 24.01.2013.
//  Copyright (c) 2013 Krzysztof Gabis. All rights reserved.
//

#include "space_controller.h"
#include "build_config.h"

SpaceController* spacecontroller_init(SimulationConfig config) {
    SpaceController *controller = (SpaceController*)malloc(sizeof(SpaceController));
    if (!controller) {
        return NULL;
    }
    controller->model = spacemodel_init_galaxies(config.model_bounds, config.view_bounds,
                                                 config.galaxies_n, config.objects_n, config.galaxy_size);
    if (!controller->model) {
        free(controller);
        return NULL;
    }
    controller->view = spaceview_init(config.view_bounds);
    if (!controller->view) {
        free(controller->model);
        free(controller);
        return NULL;
    }
    return controller;
}

void spacecontroller_update(SpaceController *c, GS_FLOAT dt) {
    static GS_FLOAT last_update_time = 0.0;
    spacemodel_update(c->model, dt);
    last_update_time += dt;
    if (last_update_time >= (1.0 / MAX_FPS)) {
        spaceview_clear(c->view);
        spaceview_draw_objects(c->view, c->model->objects);
#if DRAW_QUADS
        spaceview_draw_quadtree(c->view, c->model->tree);
#endif
#if PRINT_FPS
        printf("FPS: %.1f\n", 1.0 / last_update_time);
#endif
        spaceview_display(c->view);
        last_update_time = 0.0;
    }
}

void spacecontroller_dealloc(SpaceController *controller) {
    spaceview_dealloc(controller->view);
    spacemodel_dealloc(controller->model);
    free(controller);
}
