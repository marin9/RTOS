#include "device.h"

#define FLASH_CAPACITY	(128*1024)
#define FLASH_PAGE_LEN	256
#define FLASH_ADDR_LEN	24

#define CMD_READ	0x03
#define CMD_WRITE	0x02
#define CMD_WREN	0x06
#define CMD_WRDI	0x04
#define CMD_RDSR	0x05
#define CMD_WRSR	0x01


static char flash_readSR(){
	char sr;
	spi_begin();
	spi_sendByte(CMD_RDSR);
	sr=spi_readByte();
	spi_end();
	return sr;
}

/*  Unused
static void flash_writeSR(char byte){
	while(flash_readSR()&1);
	spi_begin();
	spi_sendByte(CMD_WREN);
	spi_end();
	
	spi_begin();
	spi_sendByte(CMD_WRSR);
	spi_sendByte(byte);
	spi_end();
}
*/

static char flash_readByte(int addr){
	char addr2=(char)((addr&0xff0000)>>16);
	char addr1=(char)((addr&0xff00)>>8);
	char addr0=(char)(addr&0x00ff);
	char byte;

	while(flash_readSR()&1);

	spi_begin();
	spi_sendByte(CMD_READ);
	if(FLASH_ADDR_LEN==24){
		spi_sendByte(addr2);
	}
	spi_sendByte(addr1);
	spi_sendByte(addr0);
	byte=spi_readByte();
	spi_end();
	return byte;
}

static void flash_writeByte(int addr, char data){
	char addr2=(char)((addr&0xff0000)>>16);
	char addr1=(char)((addr&0xff00)>>8);
	char addr0=(char)(addr&0x00ff);

	while(flash_readSR()&1);

	spi_begin();
	spi_sendByte(CMD_WREN);
	spi_end();

	spi_begin();
	spi_sendByte(CMD_WRITE);
	if(FLASH_ADDR_LEN==24){
		spi_sendByte(addr2);
	}
	spi_sendByte(addr1);
	spi_sendByte(addr0);
	spi_sendByte(data);
	spi_end();
}

static int flash_readPage(int addr, char *data){
	int i;
	char addr2=(char)((addr&0xff0000)>>16);
	char addr1=(char)((addr&0xff00)>>8);
	char addr0=(char)(addr&0x00ff);

	while(flash_readSR()&1);
	
	spi_begin();
	spi_sendByte(CMD_READ);
	if(FLASH_ADDR_LEN==24){
		spi_sendByte(addr2);
	}
	spi_sendByte(addr1);
	spi_sendByte(addr0);
	for(i=0;i<FLASH_PAGE_LEN;++i){
		data[i]=spi_readByte();
	}
	spi_end();
	return FLASH_PAGE_LEN;
}

static int flash_writePage(int addr, char *data){
	int i;
	char addr2=(char)((addr&0xff0000)>>16);
	char addr1=(char)((addr&0xff00)>>8);
	char addr0=(char)(addr&0x00ff);

	while(flash_readSR()&1);

	spi_begin();
	spi_sendByte(CMD_WREN);
	spi_end();

	spi_begin();
	spi_sendByte(CMD_WRITE);
	if(FLASH_ADDR_LEN==24){
		spi_sendByte(addr2);
	}
	spi_sendByte(addr1);
	spi_sendByte(addr0);
	for(i=0;i<FLASH_PAGE_LEN;++i){
		spi_sendByte(data[i]);
	}
	spi_end();

	return FLASH_PAGE_LEN;
}



void flash_init(){
	spi_init();
}

int flash_read(int unit, void* buffer, int nblocks, int offset){
	if(unit!=0)
		return -1;

	int i=0;
	char *buf=(char*)buffer;

	while(i<nblocks){
		if(nblocks-i>=FLASH_PAGE_LEN){
			i += flash_readPage(i+offset, buf+i);
		}else{
			buf[i]=flash_readByte(i+offset);
			++i;
		}
	}
	return i;
}

int flash_write(int unit, void* buffer, int nblocks, int offset){
	if(unit!=0)
		return -1;

	int i=0;
	char *buf=(char*)buffer;

	while(i<nblocks){
		if(nblocks-i>=FLASH_PAGE_LEN){
			i += flash_writePage(i+offset, buf+i);
		}else{
			flash_writeByte(i+offset, buf[i]);
			++i;
		}
	}
	return i;
}
