#include "device.h"

#define MB_GET_FIRMWARE			0x00001
#define MB_GET_BOARD_MODEL		0x10001
#define MB_GET_BOARD_REVISION	0x10002
#define MB_GET_BOARD_MAC_ADDR	0x10003
#define MB_GET_BOARD_SERIAL		0x10004
#define MB_GET_ARM_MEMORY 		0x10005
#define MB_GET_VC_MEMORY		0x10006
#define MB_GET_TIMING			0x20002
#define MB_GET_POWER_STATE		0x20001
#define MB_SET_POWER_STATE		0x28001
#define MB_GET_CLOCK_STATE		0x30001
#define MB_SET_CLOCK_STATE		0x38001
#define MB_GET_CLOCK_RATE		0x30002
#define MB_SET_CLOCK_RATE		0x38002
#define MB_GET_MAX_CLOCK_RATE	0x30004
#define MB_GET_MIN_CLOCK_RATE	0x30007
#define MB_GET_TURBO			0x30009
#define MB_SET_TURBO			0x38009
#define MB_GET_VOLTAGE			0x30003
#define MB_SET_VOLTAGE			0x38003
#define MB_GET_MAX_VOLTAGE		0x30005
#define MB_GET_MIN_VOLTAGE		0x30008
#define MB_GET_TEMP				0x30006
#define MB_GET_MAX_TEMP			0x3000A


#define MBOX_REQUEST		0
#define MBOX_TAG_LAST		0


extern volatile unsigned int mbox[36];


int mbox_get_firmware(uint *ret){
	mbox[0]=8*4;
	mbox[1]=MBOX_REQUEST;

	mbox[2] = MB_GET_FIRMWARE;	//get serial number command
	mbox[3] = 8;			//buffer size
	mbox[4] = 0;
	mbox[5] = 0;			//clear output buffer
	mbox[6] = 0;

	mbox[7] = MBOX_TAG_LAST;

	if(mbox_call(MBOX_CH_ARM_VC)){
		ret[0]=mbox[5];
		return 1;
	}else{
		return 0;
	}
}

int mbox_get_board_model(uint *ret){
	mbox[0]=8*4;
	mbox[1]=MBOX_REQUEST;

	mbox[2] = MB_GET_BOARD_MODEL;
	mbox[3] = 8;
	mbox[4] = 0;
	mbox[5] = 0;
	mbox[6] = 0;

	mbox[7] = MBOX_TAG_LAST;

	if(mbox_call(MBOX_CH_ARM_VC)){
		ret[0]=mbox[5];
		return 1;
	}else{
		return 0;
	}
}

int mbox_get_board_revision(uint *ret){
	mbox[0]=8*4;
	mbox[1]=MBOX_REQUEST;

	mbox[2] = MB_GET_BOARD_REVISION;
	mbox[3] = 8;
	mbox[4] = 0;
	mbox[5] = 0;
	mbox[6] = 0;

	mbox[7] = MBOX_TAG_LAST;

	if(mbox_call(MBOX_CH_ARM_VC)){
		ret[0]=mbox[5];
		return 1;
	}else{
		return 0;
	}
}

int mbox_get_mac_address(uint *ret){
	mbox[0]=8*4;
	mbox[1]=MBOX_REQUEST;

	mbox[2] = MB_GET_BOARD_MAC_ADDR;
	mbox[3] = 8;
	mbox[4] = 0;
	mbox[5] = 0;
	mbox[6] = 0;

	mbox[7] = MBOX_TAG_LAST;

	if(mbox_call(MBOX_CH_ARM_VC)){
		ret[0]=mbox[5];
		ret[1]=mbox[6];
		return 2;
	}else{
		return 0;
	}
}

int mbox_get_serial(uint *ret){
	mbox[0] = 8*4;
	mbox[1] = MBOX_REQUEST;

	mbox[2] = MB_GET_BOARD_SERIAL;
	mbox[3] = 8;
	mbox[4] = 8;
	mbox[5] = 0;
	mbox[6] = 0;

	mbox[7] = MBOX_TAG_LAST;

	if(mbox_call(MBOX_CH_ARM_VC)){
		ret[0]=mbox[5];
		ret[1]=mbox[6];
		return 2;
	}else{
		return 0;
	}
}

int mbox_get_arm_memory(uint *ret){
	mbox[0]=8*4;
	mbox[1]=MBOX_REQUEST;

	mbox[2] = MB_GET_ARM_MEMORY;
	mbox[3] = 8;
	mbox[4] = 0;
	mbox[5] = 0;
	mbox[6] = 0;

	mbox[7] = MBOX_TAG_LAST;

	if(mbox_call(MBOX_CH_ARM_VC)){
		ret[0]=mbox[5]; //start addr
		ret[1]=mbox[6]; //capacity
		return 2;
	}else{
		return 0;
	}
}

int mbox_get_vc_memory(uint *ret){
	mbox[0]=8*4;
	mbox[1]=MBOX_REQUEST;

	mbox[2] = MB_GET_VC_MEMORY;
	mbox[3] = 8;
	mbox[4] = 0;
	mbox[5] = 0;
	mbox[6] = 0;

	mbox[7] = MBOX_TAG_LAST;

	if(mbox_call(MBOX_CH_ARM_VC)){
		ret[0]=mbox[5]; //start addr
		ret[1]=mbox[6]; //capacity
		return 2;
	}else{
		return 0;
	}
}

int mbox_get_clock_rate(uint *ret, uint clk_id){ // MHz
	mbox[0]=8*4;
	mbox[1]=MBOX_REQUEST;

	mbox[2] = MB_GET_CLOCK_RATE;
	mbox[3] = 8;
	mbox[4] = 0;
	mbox[5] = clk_id;
	mbox[6] = 0;

	mbox[7] = MBOX_TAG_LAST;

	if(mbox_call(MBOX_CH_ARM_VC)){
		ret[0]=mbox[6]/1000000;
		return 1;
	}else{
		return 0;
	}
}

int mbox_get_temp(uint *ret){ // C
	mbox[0]=8*4;
	mbox[1]=MBOX_REQUEST;

	mbox[2] = MB_GET_TEMP;
	mbox[3] = 8;
	mbox[4] = 0;
	mbox[5] = 1;
	mbox[6] = 0;

	mbox[7] = MBOX_TAG_LAST;

	if(mbox_call(MBOX_CH_ARM_VC)){
		ret[0]=mbox[6]/1000;
		return 1;
	}else{
		return 0;
	}
}

int mbox_get_max_temp(uint *ret){ //C
	mbox[0]=8*4;
	mbox[1]=MBOX_REQUEST;

	mbox[2] = MB_GET_MAX_TEMP;
	mbox[3] = 8;
	mbox[4] = 0;
	mbox[5] = 1;
	mbox[6] = 0;

	mbox[7] = MBOX_TAG_LAST;

	if(mbox_call(MBOX_CH_ARM_VC)){
		ret[0]=mbox[6]/1000;
		return 1;
	}else{
		return 0;
	}
}

int mbox_get_max_clock_rate(uint *ret, uint clk_id){ // MHz
	mbox[0]=8*4;
	mbox[1]=MBOX_REQUEST;

	mbox[2] = MB_GET_MAX_CLOCK_RATE;
	mbox[3] = 8;
	mbox[4] = 0;
	mbox[5] = clk_id;
	mbox[6] = 0;

	mbox[7] = MBOX_TAG_LAST;

	if(mbox_call(MBOX_CH_ARM_VC)){
		ret[0]=mbox[6]/1000000;
		return 1;
	}else{
		return 0;
	}
}

int mbox_get_min_clock_rate(uint *ret, uint clk_id){ //MHz
	mbox[0]=8*4;
	mbox[1]=MBOX_REQUEST;

	mbox[2] = MB_GET_MIN_CLOCK_RATE;
	mbox[3] = 8;
	mbox[4] = 0;
	mbox[5] = clk_id;
	mbox[6] = 0;

	mbox[7] = MBOX_TAG_LAST;

	if(mbox_call(MBOX_CH_ARM_VC)){
		ret[0]=mbox[6]/1000000;
		return 1;
	}else{
		return 0;
	}
}

int mbox_get_voltage(uint *ret, uint v_id){ // mV
	mbox[0]=8*4;
	mbox[1]=MBOX_REQUEST;

	mbox[2] = MB_GET_VOLTAGE;
	mbox[3] = 8;
	mbox[4] = 0;
	mbox[5] = v_id;
	mbox[6] = 0;

	mbox[7] = MBOX_TAG_LAST;

	if(mbox_call(MBOX_CH_ARM_VC)){
		ret[0]=mbox[6]/1000;
		return 1;
	}else{
		return 0;
	}
}

int mbox_get_min_voltage(uint *ret, uint v_id){ //mV
	mbox[0]=8*4;
	mbox[1]=MBOX_REQUEST;

	mbox[2] = MB_GET_MIN_VOLTAGE;
	mbox[3] = 8;
	mbox[4] = 0;
	mbox[5] = v_id;
	mbox[6] = 0;

	mbox[7] = MBOX_TAG_LAST;

	if(mbox_call(MBOX_CH_ARM_VC)){
		ret[0]=mbox[6]/1000;
		return 1;
	}else{
		return 0;
	}


}

int mbox_get_max_voltage(uint *ret, uint v_id){ //mV
	mbox[0]=8*4;
	mbox[1]=MBOX_REQUEST;

	mbox[2] = MB_GET_MAX_VOLTAGE;
	mbox[3] = 8;
	mbox[4] = 0;
	mbox[5] = v_id;
	mbox[6] = 0;

	mbox[7] = MBOX_TAG_LAST;

	if(mbox_call(MBOX_CH_ARM_VC)){
		ret[0]=mbox[6]/1000;
		return 1;
	}else{
		return 0;
	}
}

int mbox_set_clock_rate(uint *ret, uint clk_id, uint val){ //MHz
	mbox[0]=9*4;
	mbox[1]=MBOX_REQUEST;

	mbox[2] = MB_SET_CLOCK_RATE;
	mbox[3] = 12;
	mbox[4] = 0;
	mbox[5] = clk_id;
	mbox[6] = val*1000000;
	mbox[7] = 1;

	mbox[8] = MBOX_TAG_LAST;

	if(mbox_call(MBOX_CH_ARM_VC)){
		ret[0]=mbox[6];
		return 1;
	}else{
		return 0;
	}
}

int mbox_set_voltage(uint *ret, uint v_id, uint val){ // mV
	mbox[0]=9*4;
	mbox[1]=MBOX_REQUEST;

	mbox[2] = MB_SET_VOLTAGE;
	mbox[3] = 8;
	mbox[4] = 0;
	mbox[5] = v_id;
	mbox[6] = val*1000;
	mbox[7] = 0;

	mbox[8] = MBOX_TAG_LAST;

	if(mbox_call(MBOX_CH_ARM_VC)){
		ret[0]=mbox[6];
		return 1;
	}else{
		return 0;
	}
}


int mbox_framebuffer_init(uint *buff, uint w, uint h, uint p){
	mbox[0] = 35*4;
	mbox[1] = MBOX_REQUEST;

	mbox[2] = 0x48003;	//set phy wh
	mbox[3] = 8;
	mbox[4] = 8;
	mbox[5] = w;		//FrameBufferInfo.width
	mbox[6] = h;		//FrameBufferInfo.height

	mbox[7] = 0x48004;	//set virt wh
	mbox[8] = 8;
	mbox[9] = 8;
	mbox[10] = w;		//FrameBufferInfo.virtual_width
	mbox[11] = h;		//FrameBufferInfo.virtual_height

	mbox[12] = 0x48009;	//set virt offset
	mbox[13] = 8;
	mbox[14] = 8;
	mbox[15] = 0;		//FrameBufferInfo.x_offset
	mbox[16] = 0;		//FrameBufferInfo.y.offset

	mbox[17] = 0x48005;	//set depth
	mbox[18] = 4;
	mbox[19] = 4;
	mbox[20] = p;		//FrameBufferInfo.depth

	mbox[21] = 0x48006;	//set pixel order
	mbox[22] = 4;
	mbox[23] = 4;
	mbox[24] = 1;		//RGB, not BGR preferably

	mbox[25] = 0x40001;	//get framebuffer, gets alignment on request
	mbox[26] = 8;
	mbox[27] = 8;
	mbox[28] = 4096;	//FrameBufferInfo.pointer
	mbox[29] = 0;		//FrameBufferInfo.size

	mbox[30] = 0x40008;	//get pitch
	mbox[31] = 4;
	mbox[32] = 4;
	mbox[33] = 0;		//FrameBufferInfo.pitch

	mbox[34] = MBOX_TAG_LAST;

	if(mbox_call(MBOX_CH_ARM_VC) && mbox[28]){
		mbox[28]&=0x3FFFFFFF;
		buff[0]=mbox[5];	//width
		buff[1]=mbox[6];	//height
		buff[2]=mbox[33];	//pitch
		buff[3]=(uint)mbox[28];	//buffer
		return 4;
	}else{
		return 0;
	}
}

