#include "dyarray.h"

int dyarray_count(void* arr) {
	return arr == NULL ? 0 : (((int*)(arr)-2)[1]);
}

int dyarray_size(void* arr) {
	return arr == NULL ? 0 : (((int*)(arr)-2)[0]);
}

void* dyarray_grow(void* arr, int count, int itemsz)
{
	int header_sz = sizeof(int) * 2; // two int, one for count, one for capacity
	int needed_sz = dyarray_count(arr) + count;
	int curr_sz = dyarray_size(arr);
	assert(0 < count && 0 < itemsz);
	if (arr == NULL) {
		int raw_sz = itemsz * count + header_sz;
		int* p = malloc(raw_sz);
		p[0] = needed_sz; // 0 for size
		p[1] = needed_sz; // 1 for count
		return p + 2;
	}
	else if (curr_sz <= needed_sz) {
		int dbl_sz = 2 * curr_sz;
		int sz = dbl_sz > needed_sz ? dbl_sz : needed_sz;
		int raw_sz = itemsz * sz + header_sz;
		int* p = realloc((int*)(arr)-2, raw_sz);
		p[0] = sz;
		p[1] = needed_sz;
		return p + 2;
	}

	((int*)(arr)-2)[1] = needed_sz;

	return arr;
}

void dyarray_release(void* arr) {
	if (arr != NULL) {
		int* p = ((int*)(arr)) - 2;
		free(p);
	}
}