/*
Welcome to HW-10 for CSCI 330 Fall 2021.
Program uses a linked list to create, populate,
and traverse a graph. Then a drunkard's walk
algorithm is executed traversing the graph in random
order until "home" node is reached. To ensure stable
results, random is seeded with 2021.
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
    LIST *currentFrom, *currentTo; //trackers for both origin and destination nodes
    currentFrom = head;
    while (strcmp(currentFrom->name, arcStart) != 0) { //find arc origin node
        currentFrom = currentFrom->next;
    }
    currentTo = head;
    while (strcmp(currentTo->name, arcEnd) != 0) { //find arc destination node
        currentTo = currentTo->next;
    }
    while (currentFrom->graph->arcs[i] != NULL) { //find first spot in array with no existing arcs
        i++;
    }
    currentFrom->graph->arcs[i] = currentTo->graph; //add arc to the origin graph node
    currentFrom->graph->weights[i] = weight; //add its associated cost at same array index
    currentFrom->graph->arcCnt++; //incement number of outgoing arc counter
}

void DRUNKARDS_WALK(LIST *head, char startKey[]) {
    srand(2021); //seed random # generator for consistent results
    int index, cost = 0;
    LIST *currentList;
    GRAPH *currentGraph;
    currentList = head;
    while (strcmp(currentList->name, startKey) != 0) { //find starting node
        currentList = currentList->next;
    }
    currentGraph = currentList->graph; //switch to graph nodes for random walk
    printf("******************************************\n");
    printf("Starting Graph Node: %s\n", currentGraph->name); //start
    while (currentGraph->arcCnt != 0) { //Home is only node without outgoing arcs, so this is how we know we are home
        index = (random() % currentGraph->arcCnt); //generate random arc index
        cost += currentGraph->weights[index]; //tally cost for each jump
        currentGraph = currentGraph->arcs[index]; //jump to next graph node specified by index of possible out arcs
    }
    printf("Ending Graph Node: %s\n", currentGraph->name); //end
    printf("Total Trip Cost: $%d\n", cost); //total trip cost
    printf("******************************************\n");
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
        while (current->graph->arcs[i] != NULL) { //for each outgoing arc
            printf("Arc end: %s %d\n", current->graph->arcs[i]->name,current->graph->weights[i]); //out arc destination and cost
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
    getline(&line, &len, stream); //get the starting node for random walk
    startKey = strtok(line, "\n");
    DRUNKARDS_WALK(head, startKey); //do the drunkards walk home
    head = FREE(head); //free all allocated memory for nodes
    fclose(stream);
    return 0;
}

