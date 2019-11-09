#pragma once
#include "types.h"

int mux_init(uint id);
int mux_lock(uint id);
int mux_unlock(uint id);
int mux_trylock(uint id);
