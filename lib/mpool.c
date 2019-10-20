#include "mpool.h"

static char *start;
static char *end;


void mpool_init(void *addr, uint size){
	start=(char*)addr;
	end=(char*)addr+size;
}

void* mpool_alloc1(uint size){
	char *ret=start;

	if(size>(uint)(end-ret)){
		return 0;
	}

	start+=size;
	return ret;
}

void* mpool_alloc2(uint size){
	char *ret=start;
	ret+=2;
	ret=(char*)((uint)ret & 0xfffffffe);

	if(size>(uint)(end-ret)){
		return 0;
	}

	start=ret+size;
	return ret;
}

void* mpool_alloc4(uint size){
	char *ret=start;
	ret+=4;
	ret=(char*)((uint)ret & 0xfffffffc);

	if(size>(uint)(end-ret)){
		return 0;
	}

	start=ret+size;
	return ret;
}

void* mpool_alloc8(uint size){
	char *ret=start;
	ret+=8;
	ret=(char*)((uint)ret & 0xfffffff8);

	if(size>(uint)(end-ret)){
		return 0;
	}

	start=ret+size;
	return ret;
}

uint mpool_getfree(){
	return (uint)(end-start);
}
