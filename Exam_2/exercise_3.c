#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to check if number is double (if the number contains decimal point)
int is_double(char* number){
    int len = strlen(number);
    for(int i = 0; i < len; i++) if(number[i] == '.') return 1;
    return 0;
}

// Function to check if number is hexadecimal (if the number begins with '0x' or '0X')
int is_hex(char* number){
    int len = strlen(number);
    if(len > 2){
        if(number[0] == '0'){
            return number[1] == 'x' || number[1] == 'X';
        }
    }
    return 0;
}

// Function to sum given values
double sum_values(int count, char** values){
    double sum = 0.00;
    for(int i = 0; i < count; i++){
        // Check what is the type of the number(double, hexadecimal or integer)
        if(is_double(values[i])){
            double number_double;
            sscanf(values[i], "%lf", &number_double);
            sum += number_double;
        }else if(is_hex(values[i])){
            int number_hex;
            sscanf(values[i], "%x", &number_hex);
            sum += number_hex;
        }else{
            int number_int;
            sscanf(values[i], "%d", &number_int);
            sum += number_int;
        }
    }
    return sum;
}

int main(int argc, char** argv){
    printf("Sum is: %.2lf\n", sum_values(argc, argv));

    return 0;
}