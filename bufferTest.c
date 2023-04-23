#include <stdio.h>
#include <stdlib.h>

/*
Test cases
12345 & abcde
1234567890123456789012345678901234567890 & abcde
12345 & abcdefghijklmnopqrst
*/

void function(void) {
    char string1[5], string2[15];
    printf("Enter text for string 1: ");
    scanf("%s", string1);
    printf("Enter text for string 2: ");
    scanf("%s", string2);
    printf("%s\n", string1);
    printf("%s\n", string2);
}

int main(void) {
    function();
    return 0;
}
