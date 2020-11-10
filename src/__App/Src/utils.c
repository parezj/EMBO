/*
 * CTU/UniLabTool project
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "utils.h"

void busy_wait(int us)
{
    for (int i = 0; i < 2000000; ++i)
        asm("nop");
}

void itoa_fast(char* s, int num, int radix)
{
    char sign = 0;
    char temp[17];  //an int can only be 16 bits long
                    //at radix 2 (binary) the string
                    //is at most 16 + 1 null long.
    int temp_loc = 0;
    int digit;
    int str_loc = 0;

    //save sign for radix 10 conversion
    if (radix == 10 && num < 0) {
        sign = 1;
        num = -num;
    }

    //construct a backward string of the number.
    do {
        digit = (unsigned int)num % radix;
        if (digit < 10)
            temp[temp_loc++] = digit + '0';
        else
            temp[temp_loc++] = digit - 10 + 'A';
        num = (((unsigned int)num) / radix);
    } while ((unsigned int)num > 0);

    //now add the sign for radix 10
    if (radix == 10 && sign) {
        temp[temp_loc] = '-';
    } else {
        temp_loc--;
    }


    //now reverse the string.
    while ( temp_loc >=0 ) {// while there are still chars
        s[str_loc++] = temp[temp_loc--];
    }
    s[str_loc] = 0; // add null termination.
}

void sprint_fast(char* s, const char* format, float fVal, int prec)
{
    char result[100] = { '\0' };
    char result_rev[100] = { '\0' };
    int dVal, dec, i, j, k;

    if (prec <= 0)
    {
        sprintf(result, "%d", (int)fVal);
        sprintf(s, format, result);
        return;
    }

    fVal += 0.5 * pow(0.1, prec);
    k = pow(10, prec);

    dVal = fVal;
    dec = ((int)(fVal * k)) % k;

    for (i = 0; i < prec; i++)
    {
        result[i] = (dec % 10) + '0';
        dec /= 10;
    }

    result[i] = '.';
    i++;

    if (dVal > 0)
    {
        while (dVal > 0)
        {
            result[i] = (dVal % 10) + '0';
            dVal /= 10;
            i++;
        }
        i--;
    }
    else
        result[i] = '0';

    for (j = 0; i >= 0; i--, j++)
        result_rev[j] = result[i];

    sprintf(s, format, result_rev);
}
