/*
 * CTU/UniLabTool project
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef UTILS_H
#define UTILS_H

void busy_wait(int us);
void itoa_fast(char* s, int num, int radix);
void sprint_fast(char* s, const char* format, float fVal, int prec);

#endif /* UTILS_H */
