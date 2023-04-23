/*
Welcome to HW-3 for CSCI 330 Fall 2021
Program displays menu of sorting options.
Each option reads file, sorts data, prints
the sorted list. Updated HW-2, using dynamically
allocated array.
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

void menuAndFile(void){
    int i, size;
    char choice;
    struct carData *cars;
    FILE *data;
    data = fopen("./hw3.data", "r");
    if (data == NULL){
        printf("ERROR - file could not be opened");
    }
    size = 1;
    while (1){
        fscanf(data, "%s %f %d %s", temp.model, &temp.engineLiter, &temp.price, temp.color);
        if (feof(data)) break;
        size++;
    }
    rewind(data);
    cars = calloc(size, sizeof(temp));
    if (cars == NULL){
        printf("ERROR - could not allocate memory");
    }
    for (i=0; i<size; i++){
        fscanf(data, "%s %f %d %s", cars[i].model, &cars[i].engineLiter, &cars[i].price, cars[i].color);
    }

    while (1){
        printMenu();
        scanf("%c", &choice);
        switch (choice){
            case '1':
                bubbleSortF(size, cars);
                printHigh(size, cars);
                break;
            case '2':
                bubbleSortF(size, cars);
                printLow(size, cars);
                break;
            case '3':
                bubbleSortI(size, cars);
                printHigh(size, cars);
                break;
            case '4':
                bubbleSortI(size, cars);
                printLow(size, cars);
                break;
            case '5':
                exit(1);
        }
    }
    free(cars);
    cars = NULL;
    fclose(data);
}

int main(void){
    menuAndFile();
    return 0;
}
