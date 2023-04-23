/*
Welcome to HW-5 for CSCI 330 Fall 2021
LOAD function part of hw4's program functions.
By Kevin Jordan - kevin.jordan@und.edu ID 1301006
*/

#include "./hw5-load.h"

struct _data *LOAD(FILE *stream, int size) {
    rewind(stream);
    int i;
    size_t len = 0;
    char *line, *token1, *token2;
    struct _data *BlackBox;
    BlackBox = (struct _data*)calloc(size, sizeof(struct _data));
    if (BlackBox == NULL) exit(1);
    for (i=0; i<size; i++) {
        line = NULL;
        getline(&line, &len, stream);
        token1 = strtok(line, " ");
        token2 = strtok(NULL, "\n");
        BlackBox[i].name = (char*)calloc(strlen(token1)+1, sizeof(char));
        if (BlackBox[i].name == NULL) exit(1);
        strcpy(BlackBox[i].name, token1);
        BlackBox[i].number = atol(token2);
        free(line);
    }
    return BlackBox;
}
