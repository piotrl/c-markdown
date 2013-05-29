#ifndef STACK
#define STACK

void push(char c); // add char c instead of first '\0' and add '\0' to next
void pop();     // overwrite last element by '\0'

char top();     // return char || -1
char empty();   // return: true / false
int size();     // return int > 0

#endif