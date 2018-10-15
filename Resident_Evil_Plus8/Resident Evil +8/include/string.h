#ifndef _STRING_H_
#define _STRING_H_

#include "types.h"


void StringCat(char *str1, char *str2);
void StringLower(char *str);
void StringUpper(char *str);
u32 StringCopy(char *dst, char *src);
u32 StringLength(char *string);
u32 StringEqual(char *s0,char *s1);


#endif //_STRING_H_
