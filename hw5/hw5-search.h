/*
Welcome to HW-5 for CSCI 330 Fall 2021
SEARCH header part of hw4's program functions.
By Kevin Jordan - kevin.jordan@und.edu ID 1301006
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef _theStruct
#define _theStruct

struct _data {
    char *name;
    long number;
};

#endif

void SEARCH(struct _data *BlackBox, char *name, int size);
