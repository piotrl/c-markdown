#ifndef CONFIG
#define CONFIG

// compile:
//

#define DEBUG(var, type) \
  printf("\n %i: " #var " == " #type " \n", __LINE__, var)

#include <stdio.h>

FILE* input;
FILE * output;

static char singletons[] = { '*', '_', '`' };
static char* conv[] = { "strong", "em", "code" };

#endif