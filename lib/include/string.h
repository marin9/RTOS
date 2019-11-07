#pragma once
#include "types.h"

void *memset(void *s, int c, uint n);
void *memcpy(void *dest, void *src, uint n);
uint strlen(char *s);
int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, int n);
char *strcpy(char *dest, const char *src);
char *strncpy(char *dest, const char *src, int n);
char *strcat(char *dest, const char *src);
int atoi(char *str);
int sprintf(char *buff, char *format, ...);
int vssprintf(char *str, char **arg);
