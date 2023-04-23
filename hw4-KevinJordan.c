/*
Welcome to HW-4 for CSCI 330 Fall 2021
Program takes command line arg of a name
and returns if it is in data file hw4.data.
Makes use of various methods of passing 
pointers and values by reference or value
as well as dynamic memory allocation.
By Kevin Jordan - kevin.jordan@und.edu ID 1301006
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct _data {
    char *name;
    long number;
};

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

void FREE(struct _data *BlackBox, int size){
    int i;
    for (i=0; i<size; i++) {
        free(BlackBox[i].name);
        BlackBox[i].name == NULL;
    }
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
