#pragma once


#define BIT_VAL(n) 			(1<<n)
#define BIT_GET(x, n) 		((x>>n)&1)
#define BIT_SET(x, n)		(x|(1<<n))
#define BIT_CLR(x, n)		(x&(~(1<<n)))
#define BIT_INV(x, n)		(x^(1<<n))
#define BIT_WR(x, n, v)		((x&(~(1<<n)))|((v&1)<<n))
