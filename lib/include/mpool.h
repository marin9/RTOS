#pragma once
#include "types.h"

void mpool_init(void *addr, uint size);
void* mpool_alloc1(uint size);
void* mpool_alloc2(uint size);
void* mpool_alloc4(uint size);
void* mpool_alloc8(uint size);
uint mpool_getfree();
