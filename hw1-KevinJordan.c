/*
Welcome to HW-1 for CSCI 330 Fall 2021
Program calculates interest paid on a loan
By Kevin Jordan - kevin.jordan@und.edu
*/

#include <stdlib.h>
#include <stdio.h>

int main(void) {
    int n=1; //num of months initialize
    float r, B, P, I, iTotal; //initialize vars
    iTotal = 0; //set default vals
    r = 0.22;
    B = 5000.0;

    printf("Weclome to the interest calculator\n");
    printf("\n");
    printf("Enter monthly payment amount($): "); //user prompt
    scanf("%f", &P); //user input
    printf("\n");
    printf("Interest rate: %.2f%\n", r*100); //print vals used in calc
    printf("Initial balance: $%.2f\n", B);
    printf("Monthly payment amount: $%.2f\n", P);
    printf("\n");
    printf("Month    Interest    Balance\n"); //set up table headers
    I = (r/12)*B; //calc I[o]
    iTotal += I; //update total interest
    printf("%-8d $%-10.2f $%-8.2f\n", n, I, B); //print first row
    while (B > 0) { //while there is still balance to pay
        B = B-P+I; //update balance
        if (B < 0) break; //if negative break as no need to calc I/iTotal
        I = (r/12)*B; //calc I[n]
        iTotal += I; //update total interest
        n++; //increment month counter
        printf("%-8d $%-10.2f $%-8.2f\n", n, I, B); //print all other rows
    }
    printf("\n");
    printf("Total interest paid: $%.2f\n", iTotal); //print total interest
    printf("\n");

return 0;
}
