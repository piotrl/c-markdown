#include "stack.h"

char stack[1000] = {'\0'};

int size()
{
    int i = 0;
    while(stack[i] != '\0')
    {
        i++;
    }
    return i;
}

char empty()
{
    return (stack[0] == '\0');
}

char top()
{
    int i = size();

    if(empty()) return -1;
    else return stack[i-1];
}

void push(char c)
{
    int i = size(); // i = pierwszy element, ktory nie jest w tablicy

    stack[i] = c;
    stack[i+1] = '\0';
}

void pop()
{
    int i = size();

    stack[i-1] = '\0';
}