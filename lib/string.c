#include "string.h"


void *memset(void *s, int c, uint n){
	uint p;
	char *m=(char*)s;
	for(p=0;p<n;p++,m++){
		*m=(char)c;
	}
	return s;
}

void *memcpy(void *dest, void *src, uint n){
	uint p=0;
	char *d=(char*)dest;
	char *s=(char*)src;

	while(p<n){
		*d++=*s++;
		++p;
	}
	return dest;
}

uint strlen(char *s){
	uint i;
	for(i=0;s[i];i++);
	return i;
}

int strcmp(const char *s1, const char *s2){
	int i;
	for(i=0;s1[i] || s2[i];i++){
		if(s1[i]<s2[i]) return -1;
		else if(s1[i]>s2[i]) return 1;
	}
	return 0;
}

/*! Returns -1 if s1 < s2, 0 if s1 == s2 or 1 if s1 > s2 */
int strncmp(const char *s1, const char *s2, int n){
	int i;
	for(i=0; i<n &&(s1[i] || s2[i]);i++){
		if(s1[i]<s2[i]) return -1;
		else if(s1[i]>s2[i]) return 1;
	}
	return 0;
}

char *strcpy(char *dest, const char *src){
	int i;
	for(i=0;src[i];i++){
		dest[i]=src[i];
	}
	dest[i]=0;
	return dest;
}

char *strncpy(char *dest, const char *src, int n){
    int i;
    for(i=0;src[i] && i<n;i++){
        dest[i]=src[i];
    }
    dest[i]=0;
    return dest;
}

char *strcat(char *dest, const char *src){
	int i;
	for(i=0;dest[i];i++);
	strcpy(&dest[i], src);
	return dest;
}

int atoi(char *str){
	int i, res=0; // Initialize result 
   
    // Iterate through all characters of input string and 
    // update result 
    for(i=0;str[i]!='\0';++i){
        res=res*10+str[i]-'0'; 
    }
    // return result. 
    return res; 
}

void hex2str(char *str, int n){
	int i, hb;
	str[0]='0';
	str[1]='x';

	for(i=0;i<8;++i){
		hb=n>>(7-i)*4;
		hb &= 0xf;

		if(hb>9){
			str[i+2]=(char)(hb+'A'-10);
		}else{
			str[i+2]=(char)(hb+'0');
		}
	}
	str[10]=0;
}

void bin2str(char *str, int n, int b){
	int i;
	str[0]='0';
	str[1]='b';

	for(i=0;i<b;++i){
		if((n>>(b-1-i))&1){
			str[2+i]='1';
		}else{
			str[2+i]='0';
		}
	}
	str[2+b]=0;
}

void dec2str(char *str, int n){
	int i=0;
	int w=0;
	int d=1000000000;

	if(n<0){
		n=-n;
		str[i]='-';
		++i;
	}

	while(d){
		str[i]=n/d+'0';
		if(str[i]!='0'){
			w=1;
		}
		if(w){
			++i;
		}
		n=n%d;
		d/=10;
	}
	if(i==0){
		str[0]='0';
		str[1]=0;
	}else{
		str[i]=0;
	}
}


int vssprintf(char *str, char **arg){
	char *format, *p;
	char buffer[20];
	int v, t, i=0;

	if(*arg){
		format=*arg++;
	}else{
		return 0;
	}

	while(*format){
		v=*((int*)arg);
		if(*format=='%'){
			++format;
			switch(*format){
			case 'd':
				dec2str(buffer, v);
				t=strlen(buffer);
				memcpy(str+i, buffer, t);
				i+=t;
				break;
			case 'u':
				if(v<0) v=-v;
				dec2str(buffer, v);
				t=strlen(buffer);
				memcpy(str+i, buffer, t);
				i+=t;
				break;
			case 'x':
				hex2str(buffer, v);
				t=strlen(buffer);
				memcpy(str+i, buffer, t);
				i+=t;
				break;
			case 'c':
				str[i++]=v;
				break;
			case 's':
				p=*arg;
				if(!p){
					str[i]=0;
					strcat(str, "null");
					i+=strlen("null");
				}else{
					t=strlen(p);
					memcpy(str+i, p, t);
					i+=t;
				}
			default:
				break;
			}
			(int*)arg++;
		}else{
			if(*format=='\n'){
				str[i++]='\r';
			}
			str[i++]=*format;
		}
		++format;
	}

	str[i++]=0;
	return i;
}

int sprintf(char *buff, char *format, ...){
	return vssprintf(buff, &format);
}
