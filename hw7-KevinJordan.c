/*
Welcome to HW-7 for CSCI 330 Fall 2021.
Program creates 2 pointer-based linked lists,
one of a poem badly spelled, the other with a
codex for fixing spelling errors. The program
compares the nodes (words) in the first linked list
with those in the codex, replacing as needed for
correct word. Displays corrected poem at end.
By Kevin Jordan - kevin.jordan@und.edu ID 1301006
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct node {
    char *word;
    struct node *next;
};

struct codex {
    char *word1;
    char *word2;
    struct codex *next;
};

typedef struct node WORD;

typedef struct codex CODEX;

WORD *WORD_BUILD(WORD *head, char word[]) { // funct just to add node
    WORD *newNode, *current; // allocate memory for node
    newNode = (WORD*)malloc(sizeof(WORD));
    if (newNode == NULL) exit(1); // allocate memory for word in node
    newNode->word = (char*)calloc(strlen(word)+1, sizeof(char));
    if (newNode->word == NULL) exit(1);
    strcpy(newNode->word, word);
    current = head; // start at beginning
    if (head == NULL) { // special case of no list yet
        newNode->next = NULL; // start list if not started yet
        head = newNode;
    }
    else { // if list is already started
        while (current->next != NULL) { // while not at end
            current = current->next; // go to end
        }
    newNode->next = current->next; // add new node
    current->next = newNode;
    }
    return head; // return head of poem list
}

WORD *WORD_GET(FILE *stream, WORD *head, int size) {
    int i, j, endLine = 0;
    size_t len = 0;
    char *line, *punct, *w1, *w2, *w3, *w4, *w5, *w6, *w7, *w8; // need enough pointers for all words/punct in line
    for (i=0; i<size; i++) { // for each line in file
        line = NULL; // set buffer to NULL
        getline(&line, &len, stream); // get the line
        punct = (char*)calloc(2, sizeof(char)); // allocate for line's punct mark and null terminator "\0"
        w1 = strtok(line, " "); // all lines of poem have at least 4 words,
        head = WORD_BUILD(head, w1); // before last word in line (special case).
        w2 = strtok(NULL, " "); // so add these nodes directly,
        head = WORD_BUILD(head, w2); // using add node function.
        w3 = strtok(NULL, " "); // EX: this gets 3rd word in line
        head = WORD_BUILD(head, w3); // EX: this function adds it to the end of list
        w4 = strtok(NULL, " ");
        head = WORD_BUILD(head, w4);
        w5 = strtok(NULL, " "); // 5th word in line starts need for end-of-line special case handling
        if (w5 != NULL) { // if theres a 5th word in the line
            for (j=0; j<strlen(w5); j++) { // for each char in word, loop looking for punctuation mark
                if (ispunct(w5[j]) != 0) { // if there is a punctuation mark
                    endLine = 1; // this is last word in the line
                    sprintf(punct, "%c%c", (char)w5[j], '\0'); // strip the punct and concatenate with "\0" to form punct str
                    w5[j] = '\0'; // replace where the punct was with null terminator effectively chopping off the punct and "\n"
                }
            }
            head = WORD_BUILD(head, w5); // if no punct add to list as is. if not add word without either ".\n" or ",\n"
        }
        if (endLine == 1) head = WORD_BUILD(head, punct); // if there was punct mark, add it as its own node/word
        endLine = 0; // reset punctuation / end-of-line flag
        w6 = strtok(NULL, " ");
        if (w6 != NULL) { // if theres a 6th word in the line
            for (j=0; j<strlen(w6); j++) { // repeat end-of-line handling procedure detailed in w5 comments
                if (ispunct(w6[j]) != 0) { // if punct found
                    endLine = 1; // set flag
                    sprintf(punct, "%c%c", (char)w6[j], '\0'); // concatenate into its own string
                    w6[j] = '\0'; // chop ".\n" or ",\n" off word
                }
            }
            head = WORD_BUILD(head, w6); // add word to list without punct
        }
        if (endLine == 1) head = WORD_BUILD(head, punct); // if punct found add it as its own node
        endLine = 0; // reset flag
        w7 = strtok(NULL, " "); // see comments for w5 / w6 for functioning / logic
        if (w7 != NULL) {
            for (j=0; j<strlen(w7); j++) {
                if (ispunct(w7[j]) != 0) {
                    endLine = 1;
                    sprintf(punct, "%c%c", (char)w7[j], '\0');
                    w7[j] = '\0';
                }
            }
            head = WORD_BUILD(head, w7);
        }
        if (endLine == 1) head = WORD_BUILD(head, punct);
        endLine = 0;
        w8 = strtok(NULL, " "); // see comments for w5 / w6 for functioning / logic
        if (w8 != NULL) {
            for (j=0; j<strlen(w8); j++) {
                if (ispunct(w8[j]) != 0) {
                    endLine = 1;
                    sprintf(punct, "%c%c", (char)w8[j], '\0');
                    w8[j] = '\0';
                }
            }
            head = WORD_BUILD(head, w8);
        }
        if (endLine == 1) head = WORD_BUILD(head, punct);
        free(punct); // 8 words max per line, so free punct for next line
        endLine = 0; // reset flag
        free(line); // free buffer for next line
        line = NULL; // no dangling!
    }
    return head; // return head of poem list
}

CODEX *CODEX_BUILD(FILE *stream, CODEX *head, int size) {
    int i;
    size_t len = 0;
    char *line, *word1, *word2;
    for (i=0; i<size; i++) { // for each line in file
        line = NULL; // set buffer to null
        getline(&line, &len, stream); // get the line string
        word1 = strtok(line, " "); // split off first word
        word2 = strtok(NULL, "\n"); // split off second word
        CODEX *newNode, *current; // allocate memory for node
        newNode = (CODEX*)malloc(sizeof(CODEX));
        if (newNode == NULL) exit(1); // allocate memory for both words
        newNode->word1 = (char*)calloc(strlen(word1)+1, sizeof(char));
        if (newNode->word1 == NULL) exit(1);
        strcpy(newNode->word1, word1);
        newNode->word2 = (char*)calloc(strlen(word2)+1, sizeof(char));
        if (newNode->word2 == NULL) exit(1);
        strcpy(newNode->word2, word2);
        current = head; // start at head
        if (head == NULL) { // special case of no head yet
            newNode->next = NULL; // add head node if this case
            head = newNode;
        }
        else { // if list already started
            while (current->next != NULL) { // while not at end
                current = current->next; // go to end
            }
            newNode->next = current->next; // add the new node
            current->next = newNode;
        }
        free(line); // free buffer
        line = NULL;
    }
    return head; // return list head
}

void WORD_DISPLAY(WORD *head) { // poem display with formatting
    WORD *current;
    current = head;
    while (current != NULL) { // for each node
        if ((current->word[0] == ',') || (current->word[0] == '.')) { // if "word" of node is punct
            printf("%s\n", current->word); // print the nodes "word" and a carriage return "\n"
        }
        else { // if not a punctuation node
            printf("%s", current->word); // print just the word
            if (!((current->next->word[0] == ',') || (current->next->word[0] == '.'))) { // if next node is not punct
                printf(" "); // print a space as well
            }
        }
        current = current->next; // do for each node
    }
}

int LIST_LENGTH(WORD *head) { // funct to find length of poem linked list
    int size = 0;
    WORD *current;
    current = head;
    while (current != NULL) { // while not at end
        size++; // increment counter
        current = current->next; // cycle to next node
    }
    return size; // return number of nodes
}

void CHECKER(WORD *(*whead), CODEX *chead, int size) { // needs both lists heads passed in
    int i;
    WORD *wcurrent, *newNode, *obsoleteNode; // need both new or obsolete node options
    CODEX *ccurrent;
    wcurrent = *whead; // start at beginning of poem linked list
    for (i=0; i<size; i++) { // for number of nodes in the poem linked list
        ccurrent = chead; // start at the beginning of codex linked list
        if (wcurrent == *whead) { // special case of replacing head
            while (ccurrent != NULL) { // check each codex entry
                if (strcmp(wcurrent->word, ccurrent->word1) == 0) { // if head matches a codex entry
                    obsoleteNode = (*whead); // remove node from front (head)
                    (*whead) = (*whead)->next;
                    free(obsoleteNode->word); // free word
                    free(obsoleteNode); // free obsolete node
                    obsoleteNode->word = NULL; // no dangling!
                    obsoleteNode = NULL;
                    newNode = (WORD*)malloc(sizeof(WORD)); // allocate memory for replacement node
                    newNode->word = (char*)calloc(strlen(ccurrent->word2)+1, sizeof(char));
                    strcpy(newNode->word, ccurrent->word2);
                    newNode->next = (*whead); // replace head with new node
                    (*whead) = newNode;
                }
                ccurrent = ccurrent->next; // no codex match yet, check next one
            }
        }
        else if (i == (size-1)) { // special case of end of list (tail)
            continue; //last node will be punctuation so no need to evaluate
        }
        else { // is not either head or tail node
            while (ccurrent != NULL) { // check all entries in codex list
                if (strcmp(wcurrent->next->word, ccurrent->word1) == 0) { // if the next node is the one to replace
                    obsoleteNode = wcurrent->next; // remove it
                    wcurrent->next = wcurrent->next->next;
                    free(obsoleteNode->word); // and free it
                    obsoleteNode->word = NULL; // no dangling pointers!
                    free(obsoleteNode);
                    obsoleteNode = NULL;
                    newNode = (WORD*)malloc(sizeof(WORD)); // allocate memory for replacement node
                    newNode->word = (char*)calloc(strlen(ccurrent->word2)+1, sizeof(char));
                    strcpy(newNode->word, ccurrent->word2);
                    newNode->next = wcurrent->next; // and add replacement node/word
                    wcurrent->next = newNode;
                }
                ccurrent = ccurrent->next; // no codex match yet, check next one
            }
        }
        wcurrent = wcurrent->next; // cycle to next poem node to check
    } // after first loop thru, maybe "skip"s added
    wcurrent = *whead; // reset to head for "skip" checking
    while (wcurrent->next != NULL) { // check each poem node
        if (strcmp(wcurrent->next->word, "skip") == 0) { // for any added "skip"s
            obsoleteNode = wcurrent->next; // remove skip node if found
            wcurrent->next = wcurrent->next->next;
            free(obsoleteNode->word); // free it
            obsoleteNode->word = NULL; // no dangling pointers!
            free(obsoleteNode);
            obsoleteNode = NULL;
        }
        wcurrent = wcurrent->next; // cycle to next poem node to check
    }
}

void CODEX_DISPLAY(CODEX *head) { // only used to verify codex list was properly freed
    CODEX *current;
    current = head;
    while (current != NULL) { // while not at end
        printf("%s ", current->word1); // print node contents
        printf("%s\n", current->word2);
        current = current->next; // cycle to next node
    }
}

WORD *WORD_FREE(WORD *head) {
    WORD *current, *tracker;
    current = head; // start at beginning
    while (current != NULL) { // while not at end
        free(current->word);  // free word
        current->word = NULL;
        tracker = current->next; //set tracker to next
        free(current); // so current can be freed
        current = NULL; // no dangling!
        current = tracker; // update current to tracker
    }
    return head;
}

CODEX *CODEX_FREE(CODEX *head) {
    CODEX *current, *tracker;
    current = head; // start at beginning
    while (current != NULL) { // while not at end
        free(current->word1); // free both words
        current->word1 = NULL; // no dangling pointers!
        free(current->word2);
        current->word2 = NULL;
        tracker = current->next; // set tracker to next
        free(current); // so current can be freed
        current = NULL;
        current = tracker; // update current to tracker
    }
    return head;
}

int SCAN(FILE *(*stream), char *filepath) {//funct to find number of lines in file
    int size = 0;
    size_t len = 0;
    char *line;
    *stream = fopen(filepath, "r"); //open file
    while (1) {
        line = NULL; //set buffer to null
        getline(&line, &len, *stream); //fill line buffer
        free(line); //free buffer
        line = NULL; //reset to NULL
        if (feof(*stream)) break;
        size++; //tracker for number of lines
    }
    rewind(*stream); //rewind for use in other functs
    return size;
}

int main(void) {
    int wsize, csize, numNodes;
    char *wfile = "./hw7data.txt", *cfile = "./hw7codex.txt"; //filepaths to load
    WORD *whead; //create head nodes for both lists
    whead = NULL;
    CODEX *chead;
    chead = NULL;
    FILE *stream1; //allocate memory for files
    stream1 = (FILE*)malloc(sizeof(FILE));
    if (stream1 == NULL) exit(1);
    FILE *stream2;
    stream2 = (FILE*)malloc(sizeof(FILE));
    if (stream2 == NULL) exit(1);
    wsize = SCAN(&stream1, wfile); // get number of lines in poem file
    csize = SCAN(&stream2, cfile); // get number of lines in codex file
    whead = WORD_GET(stream1, whead, wsize); //builds lined list for poem data
    chead = CODEX_BUILD(stream2, chead, csize); //builds linked list for codex
    numNodes = LIST_LENGTH(whead); // checks how many nodes (words) in poem linked list
    CHECKER(&whead, chead, numNodes); // finds and replaces incorrect words
    WORD_DISPLAY(whead); // displays proper corrected poem in correct format
    whead = WORD_FREE(whead); // frees all words and nodes in poem linked list
    whead = NULL;
    WORD_DISPLAY(whead); //if properly freed, should not print anything as empty list
    chead = CODEX_FREE(chead); // frees all words and nodes in codex linked list
    chead = NULL;
    CODEX_DISPLAY(chead); //if properly freed, should not print anything as empty list
    free(stream1); //free memory for files
    stream1 = NULL; // no dangling!
    free(stream2);
    stream2 = NULL;
    return 0;
}
