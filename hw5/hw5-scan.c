/*
Welcome to HW-5 for CSCI 330 Fall 2021
SCAN function part of hw4's program functions.
By Kevin Jordan - kevin.jordan@und.edu ID 1301006
*/

#include "./hw5-scan.h"

int SCAN(FILE *(*stream)) {
    int size = 0, strLength;
    size_t len = 0;
    char *line;
    *stream = fopen("./hw4.data", "r");
    while (1) {
        line = NULL;
        strLength = getline(&line, &len, *stream);
        free(line);
        if (feof(*stream)) break;
        size++;
    }
    return size;
}
