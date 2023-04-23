/*
Welcome to the Final for CSCI 330 Fall 2021.
Program uses a linked list to create, populate,
and traverse a graph. Then a greedy walk
algorithm is executed traversing the graph in random
order until "home" node is reached.
By Kevin Jordan - kevin.jordan@und.edu ID 1301006
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct graphNode {
    char name[100]; //Establishment name
    int arcCnt; //Number of outgoing arc from this node
    int weights[10]; //Weights of each outgoing arc from this node
    struct graphNode *arcs[10];
};

struct listNode {
    char name[100]; //Establishment name
    struct listNode *next;
    struct graphNode *graph; //Pointer into graph
};

typedef struct graphNode GRAPH; //for easy typing

typedef struct listNode LIST; //for easy typing

LIST *BUILD_NODES(LIST *head, char estab[]) {
    int i;
    LIST *newListNode, *current;
    newListNode = (LIST*)malloc(sizeof(LIST)); //allocate memory for list node
    if (newListNode == NULL) exit(1);
    GRAPH *newGraphNode;
    newGraphNode = (GRAPH*)malloc(sizeof(GRAPH)); //allocate memory for graph node
    if (newGraphNode == NULL) exit(1);
    strcpy(newListNode->name, estab); //copy name into list node
    strcpy(newGraphNode->name, estab); //and graph node
    newListNode->graph = newGraphNode; //reference pointer into graph from list
    newGraphNode->arcCnt = 0; //initialize graph node to 0 out arcs
    for (i=0; i<10; i++) {
        newGraphNode->weights[i] = 0;
        newGraphNode->arcs[i] = NULL;
    }
    current = head;
    if (head == NULL) { //special case of linked list being empty
        newListNode->next = NULL;
        head = newListNode;
    }
    else { //if list already has nodes
        while (current->next != NULL) { //go to end of list
            current = current->next;
        }
    newListNode->next = current->next; //add the new list node
    current->next = newListNode;
    }
    return head;
}

void POPULATE_GRAPH(LIST *head, char arcStart[], char arcEnd[], int weight) {
    int i = 0;
    LIST *current; //trackers for both origin and destination nodes
    GRAPH *Start, *Stop;
    current = head;
    while (strncmp(current->name, arcStart, strlen(current->name)-1) != 0) { //find arc origin node
        current = current->next;
    }
    Start = current->graph; //set it
    current = head;
    while (strncmp(current->name, arcEnd, strlen(current->name)-1) != 0) { //find arc destination node
        current = current->next;
    }
    Stop = current->graph; //set it
    while (Start->arcs[i] != NULL) { //find first spot in array with no existing arcs
        i++;
    }
    Start->arcs[i] = Stop; //add arc to the origin graph node
    Start->weights[i] = weight; //add its associated cost at same array index
    Start->arcCnt++; //incement number of outgoing arc counter
}

void GREEDY_WALK(LIST *head, char startKey[]) {
    //srand(2021); // (FROM HW10)seed random # generator for consistent results
    int minVal = 1000;
    int cost = 0;
    int i = 0;
    int j, index;
    LIST *currentList;
    GRAPH *currentGraph;
    currentList = head;
    while (strcmp(currentList->name, startKey) != 0) { //find starting node
        currentList = currentList->next;
    }
    currentGraph = currentList->graph; //switch to graph nodes for random walk
    printf("******************************************\n");
    printf("Starting Graph Node: %s\n", currentGraph->name); //start
    for (i=0; i<10000; i++) {
        //printf("%s\n", currentGraph->name);  // ***Uncomment to see graph node path taken***
        if (currentGraph->arcCnt == 0) {
            printf("Dead end found at %s!\n", currentGraph->name);
            break;
        }
        for (j=0; j<currentGraph->arcCnt; j++) {
            if (currentGraph->weights[j] < minVal) {
                minVal = currentGraph->weights[j];
                index = j;
            }
        }
        minVal = 1000;
        if (currentGraph->arcs[index] != NULL) {
            cost += currentGraph->weights[index];
            currentGraph = currentGraph->arcs[index];
        }
        /*(FROM HW10)******************************************
        index = (random() % currentGraph->arcCnt); //generate random arc index
        if (currentGraph->arcs[index] != NULL) {
            cost += currentGraph->weights[index]; //tally cost for each jump
            currentGraph = currentGraph->arcs[index]; //jump to next graph node specified by index of possible out arcs
        }
        ******************************************************/
        if (strncmp(currentGraph->name, "Home", 4) == 0) {
            printf("Ending Graph Node: %s\n", currentGraph->name); //end
            printf("Total Trip Cost: $%d\n", cost); //total trip cost
            printf("******************************************\n");
            break;
        }
        if (i == 9999) {
            printf("Error: We got caught in a loop, and couldn't find the way home!\n");
        }
    }
}

LIST *FREE(LIST *head) {
    LIST *current, *tracker;
    current = head;
    while (current != NULL) { //for each node
        free(current->graph); //free the graph node
        current->graph = NULL;
        tracker = current->next;
        free(current); //free reference linked list node
        current = NULL;
        current = tracker;
    }
    return head;
}

/*Useful for showing graph nodes and arcs [not used]*/
void DISPLAY(LIST *head) {
    int i = 0;
    LIST *current;
    current = head; //start at beginning of linked list
    while (current != NULL) { //while not at end
        printf("Graph Start Node: %s\n", current->graph->name); //node where arcs start
        while (current->graph->arcs[i] != NULL) { //print outgoing arcs
            printf("Arc end: %s\n", current->graph->arcs[i]->name);
            i++;
        }
        printf("\n");
        i = 0;
        current = current->next; //next list node
    }
}

int main(void) {
    int weight, i;
    size_t len = 0;
    char *stop; //end of datafile section value creation for strncmp
    stop = (char*)calloc(5, sizeof(char));
    stop = "STOP"; //end of datafile section value
    char *line, *estab, *arcStart, *arcEnd, *startKey;
    LIST *head;
    head = NULL;
    FILE *stream;
    stream = fopen("./hw10.data", "r"); //open datafile
    while (1) { //for first section of datafile containing node names
        line = NULL;
        getline(&line, &len, stream);
        estab = strtok(line, "\n"); //get the node name
        if (strncmp(estab, stop, 4) == 0) { //if end of section val found
            free(line); //free and end here
            line = NULL;
            break;
        } //otherwise
        head = BUILD_NODES(head, estab); //add both the list and graph nodes
        free(line);
        line = NULL;
    }
    while (1) { //for second section of datafile containing arc info
        line = NULL;
        getline(&line, &len, stream);
        arcStart = strtok(line, " ");
        if (strncmp(arcStart, stop, 4) == 0) { //if end of section val found
            free(line); //free and end here
            line = NULL;
            break;
        } //otherwise
        arcEnd = strtok(NULL, " ");
        weight = atoi(strtok(NULL, "\n"));
        POPULATE_GRAPH(head, arcStart, arcEnd, weight); //add arc to the graph
        free(line);
        line = NULL;
    }
    //DISPLAY(head);    // ***Uncomment to display graph map***
    getline(&line, &len, stream); //get the starting node for random walk
    startKey = strtok(line, "\n");
    GREEDY_WALK(head, startKey); //do the drunkards walk home
    head = FREE(head); //free all allocated memory for nodes
    fclose(stream);
    return 0;
}

