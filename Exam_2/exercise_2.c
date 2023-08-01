#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#define CARS_COUNT 10

typedef struct Car{
    char model[20];
    uint8_t maxspeed;
    double price;
}Car;

// Function to compare two cars based on their model names in increasing order
int cmp_model_min_to_max(const void* a, const void* b){
    return strcmp(((Car*)a)->model, ((Car*)b)->model);
}

// Function to compare two cars based on their model names in decreasing order
int cmp_model_max_to_min(const void* a, const void* b){
    return strcmp(((Car*)b)->model, ((Car*)a)->model);
}

// Function to compare two cars based on their maxspeeds in increasing order
int cmp_maxspeed_min_to_max(const void* a, const void* b){
    return ((Car*)a)->maxspeed - ((Car*)b)->maxspeed;
}

// Function to compare two cars based on their maxspeeds in decreasing order
int cmp_maxspeed_max_to_min(const void* a, const void* b){
    return ((Car*)b)->maxspeed - ((Car*)a)->maxspeed;
}

// Function to compare two cars based on their prices in increasing order
int cmp_price_min_to_max(const void* a, const void* b){
    return ((Car*)a)->price - ((Car*)b)->price;
}

// Function to compare two cars based on their prices in decreasing order
int cmp_price_max_to_min(const void* a, const void* b){
    return ((Car*)b)->price - ((Car*)a)->price;
}

// Function to get appropriate function based on choice(n)
int (*getComparator(int n))(const void*, const void*){
    switch(n){
        case 1: return cmp_model_min_to_max;
        case 2: return cmp_model_max_to_min;
        case 3: return cmp_maxspeed_min_to_max;
        case 4: return cmp_maxspeed_max_to_min;
        case 5: return cmp_price_min_to_max;
        case 6: return cmp_price_max_to_min;
    }
}

// Function to print cars 
void print_cars(Car* cars){
    for(int i = 0; i < CARS_COUNT; i++){
        printf("%s - ", cars[i].model);
        printf("%u - ", cars[i].maxspeed);
        printf("%.2lf\n", cars[i].price);
    }
}

int main(void){
    srand(time(NULL));

    // Create array of 10 cars
    Car* cars = malloc(sizeof(Car) * CARS_COUNT);
    for(int i = 0; i < CARS_COUNT; i++){
        // Model - [A-Z][a-z] {4,10}
        int len = (rand() % 7) + 4;
        for(int index = 0; index < len; index++){
            // If random number is even use uppercase letters otherwise lowercase letters
            if(rand() % 2 == 0) cars[i].model[index] = (rand() % ('Z' - 'A' + 1)) + 'A';
            else cars[i].model[index] = (rand() % ('z' - 'a' + 1)) + 'a';
        }
        cars[i].model[len] = '\0';
        
        cars[i].maxspeed = (rand() % 201) + 100; // Maxspeed - 100 - 300
        cars[i].price = (rand() % 9900001)/100.0 + 1000.00; // Price - 1000.00 - 100000.00

    }
    print_cars(cars);
    printf("\n");

    // Get users chooice for function
    int choice;
    do{
        printf("Choice: ");
        scanf("%d", &choice);
    }while(choice <= 0 || choice > 6);

    // Sort the cars using quick sort(qsort)
    printf("\n");
    qsort(cars, CARS_COUNT, sizeof(Car), getComparator(choice));
    print_cars(cars);

    free(cars);

    return 0;
}