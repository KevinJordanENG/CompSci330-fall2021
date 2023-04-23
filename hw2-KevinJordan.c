/*
Welcome to HW-2 for CSCI 330 Fall 2021
Program displays menu of sorting options.
Each option reads file, sorts data, prints
the sorted list.
By Kevin Jordan - kevin.jordan@und.edu ID 1301006
*/

#include <stdlib.h>
#include <stdio.h>

struct carData {
    char model[15];
    float engineLiter;
    int price;
    char color[15];
} temp;

int sizeOfFile(void){
    int size = 0;
    FILE *data;
    data = fopen("./hw2.data", "r");
    while (1){
        fscanf(data, "%s %f %d %s", temp.model, &temp.engineLiter, &temp.price, temp.color);
        if (feof(data)) break;
        size++;
    }
    return (size+1);
}

void fill(int size, struct carData cars[]){
    int i;
    FILE *data;
    data = fopen("./hw2.data", "r");
    for (i=0; i<(size+1); i++){
        fscanf(data, "%s %f %d %s", cars[i].model, &cars[i].engineLiter, &cars[i].price, cars[i].color);
    }
}

void bubbleSortF(int size, struct carData cars[]){
    int i, swapped;
    do {
        swapped = 0;
        for (i=0; i<(size-1); i++){
            if (cars[i].engineLiter > cars[i+1].engineLiter){  
                temp = cars[i];
                cars[i] = cars[i+1];
                cars[i+1] = temp;
                swapped = 1;
            }
        }
    } while (swapped);
}

void bubbleSortI(int size, struct carData cars[]){
    int i, swapped;
    do {
        swapped = 0;
        for (i=0; i<(size-1); i++){
            if (cars[i].price > cars[i+1].price){
                temp = cars[i];
                cars[i] = cars[i+1];
                cars[i+1] = temp;
                swapped = 1;
            }
        }
    } while (swapped);
}

void printHigh(int size, struct carData cars[]){
    int i;
    for (i=(size-1); i>=0; i--){
        printf("%s %f %d %s\n", cars[i].model, cars[i].engineLiter, cars[i].price, cars[i].color);
    }
}

void printLow(int size, struct carData cars[]){
    int i;
    for (i=0; i<size; i++){
        printf("%s %f %d %s\n", cars[i].model, cars[i].engineLiter, cars[i].price, cars[i].color);
    }
}

void printMenu(void){
    printf("\n");
    printf("1. Sort data by the float value & print high to low\n");
    printf("2. Sort data by the float value & print low to high\n");
    printf("3. Sort data by the int value & print high to low\n");
    printf("4. Sort data by the int value & print low to high\n");
    printf("5. Exit\n");
    printf("\n");
}

void menuChoice(void){
    char choice;
    int size;
    struct carData cars[100];
    while (1){
        printMenu();
        scanf("%c", &choice);
        switch (choice){
            case '1':
                size = sizeOfFile();
                fill(size, cars);
                bubbleSortF(size, cars);
                printHigh(size, cars);
                break;
            case '2':
                size = sizeOfFile();
                fill(size, cars);
                bubbleSortF(size, cars);
                printLow(size, cars);
                break;
            case '3':
                size = sizeOfFile();
                fill(size, cars);
                bubbleSortI(size, cars);
                printHigh(size, cars);
                break;
            case '4':
                size = sizeOfFile();
                fill(size, cars);
                bubbleSortI(size, cars);
                printLow(size, cars);
                break;
            case '5':
                exit(1);
        }
    }
}

int main(void){
    menuChoice();
    return 0;
}
