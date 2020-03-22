#include "device.h"

static uint width;
static uint height;
static uint pdepth;
static uint *fb;


int graphic_init(uint w, uint h, uint p){
	uint retval;
	uint buff[4]={0};

	retval=mbox_framebuffer_init(buff, w, h, p);

	width=buff[0];
	height=buff[1];
	pdepth=buff[2];
	fb=(uint*)buff[3];

	if(retval==4)
		return 0;
	else
		return -1;
}

void graphic_clear(uint c){
	uint i;
	for(i=0;i<width*height;++i){
		fb[i]=c;
	}
}

void graphic_draw_pixel(uint x, uint y, uint c){
	fb[x+y*width]=c;
}


void graphic_draw_rect(uint x, uint y, uint w, uint h, uint c){
	uint i;
	uint x2=x+w;
	uint y2=y+h;

	for(i=x;i<x2;++i){
		fb[i+y*width]=c;
		fb[i+(y+h)*width]=c;
	}
	for(i=y;i<y2;++i){
		fb[x+i*width]=c;
		fb[x+w+i*width]=c;
	}
}

void graphic_fill_rect(uint x, uint y, uint w, uint h, uint c){
	uint xi, x2=x+w;
	uint yi, y2=y+h;

	for(yi=y;yi<y2;++yi){
		for(xi=x;xi<x2;++xi){
			fb[xi+yi*width]=c;
		}
	}
}
