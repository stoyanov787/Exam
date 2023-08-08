#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void hex_dump(char* filename){
    FILE* file = fopen(filename, "r");
    if(file == NULL){
        perror("Unable to open file");
        exit(-1);
    }

    int symbol;
    while((symbol = fgetc(file)) != EOF){
        printf("%x ", symbol);
    }
    printf("\n");

    fclose(file);
}

void print_bits(uint8_t symbol){
    int byte_size = 8;
    for(int i = (sizeof(symbol) * byte_size) - 1; i >= 0; i--){
        printf("%d", !!(symbol & (1U << i)));
    }
}

void binary_dump(char* filename){
    FILE* file = fopen(filename, "r");
    if(file == NULL){
        perror("Unable to open file");
        exit(-1);
    }

    int symbol;
    while((symbol = fgetc(file)) != EOF){
        print_bits((uint8_t)symbol);
        printf(" ");
    }
    printf("\n");

    fclose(file);
}

int main(int argc, char** argv){
    if(argc != 3){
        perror("Not enough arguments");
        exit(-1);
    }

    if(!strcmp(argv[2], "-H")){
        hex_dump(argv[1]);
    }else if(!strcmp(argv[2], "-B")){
        binary_dump(argv[1]);
    }else{
        perror("Invalid mode");
        exit(-1);
    }

    return 0;
}