#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/wait.h>

uint64_t overall_sum = 0;
pthread_mutex_t mutex;

void* find_sum(void* arg){
    int fd_file = open((char*)arg, O_RDONLY);
    off_t len = lseek(fd_file, 0, SEEK_END);
    lseek(fd_file, 0, SEEK_SET);
    // use malloc to prevent overflow
    uint64_t arr[len / sizeof(uint64_t)];
    if(read(fd_file, arr, len) != sizeof(arr)){
        perror("Writing error");
        exit(EXIT_FAILURE);
    }
    close(fd_file);

    uint64_t sum = 0;
    for(int i = 0; i < len / sizeof(uint64_t); i++){
        uint64_t num = arr[i];
        while(num > 0){
            sum += (num % 10);
            num /= 10;
        }
    }

    pthread_mutex_lock(&mutex);
    overall_sum += sum;
    pthread_mutex_unlock(&mutex);
    printf("%s - %ld\n", (char*)arg, sum);
    pthread_exit(NULL);
}

int main(int argc, char* argv[]){
    if(argc < 2){
        perror("Invalid input");
        exit(EXIT_FAILURE);
    }

    int files_count = argc - 1;
    pthread_t t[files_count];
    pthread_mutex_init(&mutex, NULL);

    for(int i = 0; i < files_count; i++){
        if(pthread_create(&t[i], NULL, find_sum, argv[i + 1]) != 0){
            perror("Creation error");
            exit(EXIT_FAILURE);
        }
    }

    for(int i = 0; i < files_count; i++){
        if(pthread_join(t[i], NULL) != 0){
            perror("Joining error");
            exit(EXIT_FAILURE);
        }
    }
    pthread_mutex_destroy(&mutex);

    printf("Overall sum is %ld\n", overall_sum);

    return 0;
}
