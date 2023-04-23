/*
Welcome to the Midterm for CSCI 330 Fall 2021
Program modifies HW4 to include last name as
command line arg. Also displays name when found.
By Kevin Jordan - kevin.jordan@und.edu ID 1301006
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct _data {
    char *firstname;
    char *lastname;
    long rnumber;
};

int SCAN(FILE *(*stream)) {
    int size = 0, strLength;
    size_t len = 0;
    char *line;
    *stream = fopen("./midterm.data", "r");
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
    char *line, *first, *last, *number;
    struct _data *BlackBox;
    BlackBox = (struct _data*)calloc(size, sizeof(struct _data));
    if (BlackBox == NULL) exit(1);
    for (i=0; i<size; i++) {
        line = NULL;
        getline(&line, &len, stream);
        first = strtok(line, " ");
        last = strtok(NULL, " ");
        number = strtok(NULL, "\n");
        BlackBox[i].firstname = (char*)calloc(strlen(first)+1, sizeof(char));
        if (BlackBox[i].firstname == NULL) exit(1);
        BlackBox[i].lastname = (char*)calloc(strlen(last)+1, sizeof(char));
        if (BlackBox[i].lastname == NULL) exit(1);
        strcpy(BlackBox[i].firstname, first);
        strcpy(BlackBox[i].lastname, last);
        BlackBox[i].rnumber = atol(number);
        free(line);
    }
    return BlackBox;
}


void SEARCH(struct _data *BlackBox, char *first, char *last, int size) {
    int i;
    int flag = 0;
    for (i=0; i<size; i++) {
        if ((strcmp(first, BlackBox[i].firstname) == 0) && (strcmp(last, BlackBox[i].lastname) == 0)) {
            flag = 1;
            printf("*******************************************\n");
            printf("[%s %s] was found at the %d entry\n", BlackBox[i].firstname, BlackBox[i].lastname, i);
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
        free(BlackBox[i].firstname);
        BlackBox[i].firstname = NULL;
        free(BlackBox[i].lastname);
        BlackBox[i].lastname = NULL;
    }
    free(BlackBox);
    BlackBox = NULL;
}

int main(int argv, char **argc) {
    if (argv <= 2) {
        printf("*******************************************\n");
        printf("* You must include a name to search for.  *\n");
        printf("*******************************************\n");
    }
    else if (argv == 3) {
        int size, i;
        struct _data *BlackBox;
        FILE *stream;
        stream = (FILE*)malloc(sizeof(FILE));
        if (stream == NULL) exit(1);
        size = SCAN(&stream);
        BlackBox = LOAD(stream, size);
        SEARCH(BlackBox, argc[1], argc[2], size);
        FREE(BlackBox, size);
        fclose(stream);
        stream = NULL;
    }
    else if (argv > 3) {
        printf("*******************************************\n");
        printf("* Too many names entered, two at a time!  *\n");
        printf("*******************************************\n");
    }
    return 0;
}
