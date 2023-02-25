/*
This is the code file for the integer associated red-black tree module
By Jack Perry
*/


#include <stdio.h>
#include "integer.h"

int int_cmp(const void *v1, const void *v2) {
    int p1 = *(int *)v1;
    int p2 = *(int *)v2;
    
    if (p1 < p2) {
        return -1;
    } else if (p1 > p2) {
        return 1;
    }
    return 0;
}


void int_print(const void *v) {
    int p = *(int *)v;
    printf("%d ", p);
}