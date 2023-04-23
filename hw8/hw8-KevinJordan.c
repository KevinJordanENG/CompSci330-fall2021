/*
Welcome to HW-8 for CSCI 330 Fall 2021
main program part of hw4's program functions.
Uses static/shared libraries to compile into executable
By Kevin Jordan - kevin.jordan@und.edu ID 1301006
*/

#include "./hw8-lib-KevinJordan.h"

int main(int argv, char **argc) {
    if (argv == 1) {
        printf("*******************************************\n");
        printf("* You must include a name to search for.  *\n");
        printf("*******************************************\n");
    }
    else if (argv == 2) {
        int size, i;
        struct _data *BlackBox;
        FILE *stream;
        stream = (FILE*)malloc(sizeof(FILE));
        if (stream == NULL) exit(1);
        size = SCAN(&stream);
        BlackBox = LOAD(stream, size);
        SEARCH(BlackBox, argc[1], size);
        FREE(BlackBox, size);
        fclose(stream);
        stream = NULL;
    }
    else if (argv > 2) {
        printf("*******************************************\n");
        printf("* Too many names entered, one at a time!  *\n");
        printf("*******************************************\n");
    }
    return 0;
}


