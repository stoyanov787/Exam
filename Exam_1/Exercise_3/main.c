#include <stdio.h>
#include "functions.h"

int main(void){
    unsigned int n;
    scanf("%u", &n);
    int arr[n];
    for(int i = 0; i < n; i++){
        scanf("%d", &arr[i]);
    }

    int dest[100];
    int new_n;

    subseq(arr, n, dest, &new_n);

    for(int i = 0; i < new_n; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}