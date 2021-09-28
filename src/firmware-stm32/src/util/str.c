/*
 * Name: str.c
 * Author: Martin Stankus
 *
 */

#include "str.h"

int strcmp(const char *src1, const char *src2)
{
	int ind = 0;

	while (src1[ind] == src2[ind]) {
		if (!src1[ind]) {
			return 0;
		}
		ind++;
	}

	if (src1[ind] < src2[ind]) {
		ind = -ind;
		ind--;
	} else {
		ind++;
	}

	return ind;
}

unsigned int strcpy(char *dest, const char *src)
{
	unsigned int ind = 0u;

	while (src[ind]) {
		dest[ind] = src[ind];
		ind++;
	}

	dest[ind] = 0;

	return ind;
}

unsigned int strcat(char *dest, const char *src)
{
	unsigned int dest_len;

	dest_len = strlen(dest);

	return dest_len + strcpy(&dest[dest_len], src);
}

unsigned int strlen(const char *src)
{
	unsigned int ind = 0u;

	while (src[ind]) {
		ind++;
	}

	return ind;
}
