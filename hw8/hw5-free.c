/*
Welcome to HW-5 for CSCI 330 Fall 2021
FREE function part of hw4's program functions.
By Kevin Jordan - kevin.jordan@und.edu ID 1301006
*/

#include "./hw5-free.h"

void FREE(struct _data *BlackBox, int size){
    int i;
    for (i=0; i<size; i++) {
        free(BlackBox[i].name);
        BlackBox[i].name == NULL;
    }
    free(BlackBox);
    BlackBox == NULL;
}
