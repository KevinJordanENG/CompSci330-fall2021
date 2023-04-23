/*
Welcome to HW-8 for CSCI 330 Fall 2021
main header part for hw8's libraries
By Kevin Jordan - kevin.jordan@und.edu ID 1301006
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "./hw5-scan.h"
#include "./hw5-load.h"
#include "./hw5-search.h"
#include "./hw5-free.h"

#ifndef _theStruct
#define _theStruct

struct _data {
    char *name;
    long number;
};

#endif

int main(int argv, char **argc);
