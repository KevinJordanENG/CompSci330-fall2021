/*
Welcome to HW-9 for CSCI 330 Fall 2021
Program provides similar functionality to HW-4
but instead of using pointers for the name, there
is a fixed array. Implemented with stack overflow
protection, for secure coding demonstration.
By Kevin Jordan - kevin.jordan@und.edu ID 1301006
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct _data {
    char name[5];
    long number;
};

int SCAN(FILE *(*stream)) {
    int size = 0;
    size_t len = 0;
    char *line;
    *stream = fopen("./hw4.data", "r");
    while (1) {
        line = NULL;
        getline(&line, &len, *stream);
        free(line);
        if (feof(*stream)) break;
        size++;
    }
    return size;
}

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
        strncpy(BlackBox[i].name, token1, 5);
        BlackBox[i].number = atol(token2);
        free(line);
    }
    return BlackBox;
}

void SEARCH(struct _data *BlackBox, char *name, int size) {
    int i;
    int flag = 0;
    for (i=0; i<size; i++) {
        if (strncmp(name, BlackBox[i].name, 5) == 0) {
            flag = 1;
            printf("*******************************************\n");
            printf("* The name was found at list entry: %d\n", i);
            printf("*******************************************\n");
            break;
        }
    }
    if (flag == 0) {
        printf("*******************************************\n");
        printf("* The name was NOT found in the list      *\n");
        printf("*******************************************\n");
    }
}

void FREE(struct _data *BlackBox){
    int i;
    free(BlackBox);
    BlackBox == NULL;
}

int main(int argv, char **argc) {
    if (argv == 1) {
        printf("*******************************************\n");
        printf("* You must include a name to search for.  *\n");
        printf("*******************************************\n");
    }
    else if (argv == 2) {
        int size;
        struct _data *BlackBox;
        FILE *stream;
        stream = (FILE*)malloc(sizeof(FILE));
        if (stream == NULL) exit(1);
        size = SCAN(&stream);
        BlackBox = LOAD(stream, size);
        SEARCH(BlackBox, argc[1], size);
        FREE(BlackBox);
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
