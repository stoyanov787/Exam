#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to encode odd numbers
char odd_encoding(char number){
    switch(number){
        case '0': return '!';
        case '1': return '#';
        case '2': return '/';
        case '3': return '~';
        case '4': return '=';
        case '5': return '\'';
        case '6': return '\\';
        case '7': return '>';
        case '8': return '.';
        case '9': return ',';
    }
}

// Function to encode string
char* encode(char* str){
    size_t len = strlen(str);
    char* result = malloc(sizeof(char) * (len + 1)); // length of str and '\0'

    for(int i = 0; i < len; i++){
        // Check if index(i) is even or odd
        if(i % 2 == 0){
            result[i] = str[i] + ('A' - '0');
        }else{
            result[i] = odd_encoding(str[i]);
        }
    }
    result[len] = '\0';

    return result;
}

int main(void){
    char *str = malloc(sizeof(char) * 501); // 500 digits and '\0'
    printf("Enter number: ");
    scanf("%s", str);

    char *result = encode(str);
    printf("%s\n", result);
    
    free(str);
    free(result);

    return 0;
}