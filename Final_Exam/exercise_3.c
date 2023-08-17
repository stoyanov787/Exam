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
#define ROW_LEN 4
#define FILE_LEN 20

int M;
char file_name[FILE_LEN];
pthread_mutex_t mutex;

void* find_average(void *arg){
    int *numbers = (int*)arg;
    int sum = 0;
    for(int i = 0; i < M; i++){
        sum += numbers[i];
    }

    double average = sum / (double)M;

    pthread_mutex_lock(&mutex);
    
    FILE* file = fopen(file_name, "a");

    fprintf(file, "%.3lf\n", average);

    fclose(file);
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

int main(void){
    unsigned int N;
    scanf("%d", &N);
    scanf("%d", &M);

    char row[ROW_LEN];
    unsigned int line_number;
    int numbers[N][M];

    for(int i = 0; i < N; i++){
        scanf("%s", row);
        scanf("%d", &line_number);
        for(int j = 0; j < M; j++){
            scanf("%d", &numbers[i][j]);
        }
    }
    scanf("%s", file_name);

    FILE* check_file_exist = fopen(file_name, "r");
    if(check_file_exist == NULL){
        perror("File does not exist error");
        exit(EXIT_FAILURE);
    }
    fclose(check_file_exist);  

    pthread_t t[N];
    pthread_mutex_init(&mutex, NULL);

    for(int i = 0; i < N; i++){
        if(pthread_create(&t[i], NULL, find_average, numbers[i]) != 0){
            perror("Creation error");
            exit(EXIT_FAILURE);
        }
    }

    for(int i = 0; i < N; i++){
        if(pthread_join(t[i], NULL) != 0){
            perror("Joining error");
            exit(EXIT_FAILURE);
        }
    }

    pthread_mutex_destroy(&mutex);

    return 0;
}
