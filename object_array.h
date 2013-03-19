//
//  object_array.h
//  GravitySim
//
//  Created by Krzysztof Gabis on 25.01.2013.
//  Copyright (c) 2013 Krzysztof Gabis. All rights reserved.
//

#ifndef GravitySim_object_array_h
#define GravitySim_object_array_h

#include "object.h"
#include "basic_types.h"

typedef struct {
    Object *objects;
    size_t len;
    size_t capacity;
} ObjectArray;

ObjectArray* objectarray_init_empty(size_t capacity);
void objectarray_dealloc(ObjectArray *array);
void objectarray_remove_object_at(ObjectArray *array, size_t i);
void objectarray_add(ObjectArray *array, Object object);


#endif
