#include <stdio.h>
#include "functions.h"

int main(){
    double r, h, V, S;

    while(1){
        scanf("%lf", &r);
        scanf("%lf", &h);
        if(r == 0 && h == 0) break;

        if(cylinder(r, h, &V, &S) == -1){
            printf("Invalid data\n");
        }else{
            printf("V = %.2lf, S = %.2lf\n", V, S);
        }
    }

    return 0;
}