//
//  object_array.c
//  GravitySim
//
//  Created by Krzysztof Gabis on 25.01.2013.
//  Copyright (c) 2013 Krzysztof Gabis. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "object_array.h"

ObjectArray* objectarray_init_empty(size_t capacity) {
    ObjectArray *array = (ObjectArray*)malloc(sizeof(ObjectArray));
    if (!array) {
        return NULL;
    }
    array->objects = (Object*)malloc(capacity * sizeof(Object));
    if (!array->objects) {
        free(array);
        return NULL;
    }
    array->capacity = capacity;
    array->len = 0;
    return array;
}

void objectarray_add(ObjectArray *array, Object object) {
    if (array->len >= array->capacity) {
        size_t new_capacity = array->capacity * 2;
        Object* realloc_ptr = realloc(array->objects, new_capacity * sizeof(Object));
        if (realloc_ptr == NULL) {
            fprintf(stderr, "Realloc error in ObjectArray.\n");
            return; //no erro handling here
        }
        array->objects = realloc_ptr;
        array->capacity = new_capacity;
    }
    array->objects[array->len] = object;
    array->len++;
}

void objectarray_dealloc(ObjectArray *array) {
    free(array->objects);
    free(array);
}

void objectarray_remove_object_at(ObjectArray *array, size_t i) {
    if (i != array->len) {
        array->objects[i] = array->objects[array->len - 1];
    }
    array->len--;
}
