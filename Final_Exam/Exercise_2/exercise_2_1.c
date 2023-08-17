#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/types.h>
#include <fcntl.h>
/*
#include <string.h>

#include <pthread.h>
#include <semaphore.h>

#include <sys/wait.h>
*/

int main(int argc, char* argv[]){
    if(argc != 3){
        perror("Invalid input");
        exit(EXIT_FAILURE);
    }
    /*
    Програмата записва N на брой цели неотрицателни 64 битови числа в бинарен файл с името filename. 
Ако файл с такова име не съществува - той се създава. 
Ако съществува - предишното му съдържание се трие. 
Вие имате избор какви числа да запишете във файла.

    */

    size_t N;
    sscanf(argv[1], "%ld", &N);
    uint64_t arr[N];

    for(int i = 0; i < N; i++){
        arr[i] = rand() % 101;
    }
    for(int i = 0; i < N; i++){
        printf("%ld\n", arr[i]);
    }

    // cHECK TRUNCT
    int fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0777);

    if(write(fd, arr, sizeof(arr)) == -1){
        perror("Writing error");
        exit(EXIT_FAILURE);
    }
    close(fd);


    return 0;
}
