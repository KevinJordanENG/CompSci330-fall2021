/*
Welcome to HW-5 for CSCI 330 Fall 2021
SEARCH function part of hw4's program functions.
By Kevin Jordan - kevin.jordan@und.edu ID 1301006
*/

#include "./hw5-search.h"

void SEARCH(struct _data *BlackBox, char *name, int size) {
    int i;
    int flag = 0;
    for (i=0; i<size; i++) {
        if (strcmp(name, BlackBox[i].name) == 0) {
            flag = 1;
            printf("*******************************************\n");
            printf("* The name was found at list entry: %d\n", i);
            printf("*******************************************\n");
        }
    }
    if (flag == 0) {
        printf("*******************************************\n");
        printf("* The name was NOT found in the list      *\n");
        printf("*******************************************\n");
    }
}
