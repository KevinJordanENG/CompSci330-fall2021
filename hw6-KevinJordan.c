/*
Welcome to HW-6 for CSCI 330 Fall 2021.
Program creates a pointer-based linked list,
reads in specified file as command line arg,
uses an insertion sort for 'add' flagged names,
and deletes if name is 'delete' flagged. Displays
final list on completion, and frees dynamically
allocated memory.
By Kevin Jordan - kevin.jordan@und.edu ID 1301006
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct node {//struct needed for each node
    char *name;
    struct node *next;
};

typedef struct node LINK;//for easy typing

int LIST_SEARCH(char name[], LINK *head) {
    int flag = 0;
    LINK *current;
    current = head;//start at head
    while (current != NULL) {//while not at end
        if (strcmp(current->name, name) == 0) {//change flag if found
            flag = 1;
        }
        current = current->next;
    }
    return flag;
}

LINK *LIST_INSERT(char name[], LINK *head) {
    LINK *newNode, *current;
    newNode = (LINK*)malloc(sizeof(LINK));//alocate memory for node
    newNode->name = (char*)calloc(strlen(name)+1, sizeof(char));//alloc mem for name
    strcpy(newNode->name, name);//copy str into node
    current = head;
    if (head == NULL) {//if no list yet create head node
        newNode->next = NULL;
        head = newNode;
    }
    else if (strcmp(current->name, newNode->name) > 0) {//if repalcing first item
        newNode->next = head;
        head = newNode;
    }
    else {//if inserting into middle
        while (current->next != NULL) {
            if (strcmp(current->name, newNode->name) < 0) {
                if (strcmp(current->next->name, newNode->name) > 0) {
                    break;
                }
                current = current->next;
            }
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    return head;
}

void LIST_DELETE(char name[], LINK *(*head)) {
    LINK *current, *obsoleteNode;
    current = (*head);
    if (strcmp((*head)->name, name) == 0) {//if removing first item
        obsoleteNode = (*head);
        (*head) = (*head)->next;
        free(obsoleteNode->name);//free and
        obsoleteNode->name = NULL;//set dangling pointers to NULL
        free(obsoleteNode);
        obsoleteNode = NULL;
    }
    else {//if removing from middle or end
        while (current->next != NULL) {
            if (strcmp(current->next->name, name) == 0) {
                obsoleteNode = current->next;
                current->next = current->next->next;
                free(obsoleteNode->name);
                obsoleteNode->name = NULL;
                free(obsoleteNode);
                obsoleteNode = NULL;
            }
            else {
                current = current->next;
            }
        }
    }
}

void LIST_DISPLAY(LINK *head) {
    LINK *current;
    current = head;
    while (current != NULL) {//while not at end
        printf("%s\n", current->name);//print each item
        current = current->next;
    }
}

LINK *LIST_FREE(LINK *head) {
    LINK *current, *tracker;
    current = head;//start at head
    while (current != NULL) {
        free(current->name);//free internal name item
        current->name = NULL;
        tracker = current->next;//set tracker to next
        free(current);//free current node
        current = NULL;
        current = tracker;//set current to tracker
    }
    return head;
}

int main(int argv, char **argc) {
    if (argv == 1) {
        printf("*******************************************\n");
        printf("* You must include a filename to load.    *\n");
        printf("*******************************************\n");
    }
    else if (argv == 2) {
        int i, flag, size = 0;
        size_t len = 0;
        char *line, *name, *op_code;//initialize buffers
        LINK *head;
        head = NULL;
        FILE *stream;
        stream = (FILE*)malloc(sizeof(FILE));//alloc mem for file size
        if (stream == NULL) exit(1);
        stream = fopen(argc[1], "r");//open file
        while (1) {//see how many lines in file
            line = NULL;
            getline(&line, &len, stream);
            free(line);
            line = NULL;
            if (feof(stream)) break;
            size++;
        }
        rewind(stream);//reset to beginning
        for (i=0; i<size; i++) {//for each line item
            line = NULL;
            getline(&line, &len, stream);//get it into its own buffer
            name = strtok(line, " ");//get name
            op_code = strtok(NULL, "\n");//get op code
            flag = LIST_SEARCH(name, head);//search existing list for name
            if (flag == 0) {//if it wasnt found
                if (op_code[0] == 'a') {//and its supposed to be added
                    head = LIST_INSERT(name, head);//add it
                }
            }
            else if (flag != 0) {//if its already in the list
                if (op_code[0] == 'd') {//and its supposed to be removed
                    LIST_DELETE(name, &head);//remove it
                }
            }
            free(line);//free line buffer
            line = NULL;
        }
        LIST_DISPLAY(head);//display final list
        head = LIST_FREE(head);//free list - POOF! GONE!
    }
    else if (argv > 2) {
        printf("*******************************************\n");
        printf("* Too many filenames entered, 1 at a time!*\n");
        printf("*******************************************\n");
    }
    return 0;
}

