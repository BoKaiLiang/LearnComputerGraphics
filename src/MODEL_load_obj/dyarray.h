#ifndef _DYARRAY_H_
#define _DYARRAY_H_

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define dyarray_push(arr, val)						\
do {												\
	(arr) = dyarray_grow((arr), 1, sizeof(*(arr))); \
	(arr)[dyarray_count(arr) - 1] = (val);			\
} while(0)

#define dyarray_last(arr) (arr)[dyarray_count(arr) - 1]
#define dyarray_pop(arr) ((((int*)(arr)-2)[1])--, (arr)[(((int*)(arr)-2)[1])])

int dyarray_count(void* arr);

int dyarray_size(void* arr);

void* dyarray_grow(void* arr, int count, int itemsz);

void dyarray_release(void* arr);

#endif // _DYARRAY_H_