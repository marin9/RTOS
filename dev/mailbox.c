#include "rpi.h"
#include "device.h"

#define MBOX_READ		((volatile uint*)(MBOX_BASE+0x80))
#define MBOX_POLL		((volatile uint*)(MBOX_BASE+0x90))
#define MBOX_SENDER		((volatile uint*)(MBOX_BASE+0x94))
#define MBOX_STATUS		((volatile uint*)(MBOX_BASE+0x98))
#define MBOX_CONFIG		((volatile uint*)(MBOX_BASE+0x9C))
#define MBOX_WRITE		((volatile uint*)(MBOX_BASE+0xA0))

#define MBOX_RESPONSE   0x80000000

#define MBOX_FULL       0x80000000
#define MBOX_EMPTY      0x40000000


volatile uint  __attribute__((aligned(16))) mbox[36];



int mbox_call(int ch){
	uint d=(((uint)mbox) & 0xfffffff0)+(ch & 0xf);

	while((*MBOX_STATUS) & MBOX_FULL);
	*MBOX_WRITE=d;

	while(1){
		while((*MBOX_STATUS) & MBOX_EMPTY);

		if(*MBOX_READ==d){
			return mbox[1]==MBOX_RESPONSE;
		}
	}
	return 0;
}
