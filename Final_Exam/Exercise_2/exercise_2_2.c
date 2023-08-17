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


int main(int argc, char* argv[]){
    if(argc < 2){
        perror("Invalid input");
        exit(EXIT_FAILURE);
    }

    int files_count = argc - 1;
    int pipes_count;
    if(files_count == 1){
        pipes_count = 1;
    }else{
        pipes_count = files_count + 1;
    }
    int fd[pipes_count][2];
    int pids[files_count];

    for(int i = 0; i < pipes_count; i++){
        pipe(fd[i]);
    }

    for(int i = 0; i < files_count; i++){
        pid_t cur_pid = fork();
        if(cur_pid < 0){
            perror("Fork error");
            exit(EXIT_FAILURE);
        }else if(cur_pid == 0){
            for(int j = 0; j < pipes_count; j++){
                close(fd[j][0]); // Close reading
                // Close writing
                if(i != j){
                    close(fd[j][1]);
                }
            }
            int fd_file = open(argv[i + 1], O_RDONLY);
            off_t len = lseek(fd_file, 0, SEEK_END);
            lseek(fd_file, 0, SEEK_SET);
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
            if(write(fd[i][1], &sum, sizeof(sum)) == -1){
                perror("Error writing");
                exit(EXIT_FAILURE);
            }
            close(fd[i][1]);

            printf("%s - %ld\n", argv[i + 1], sum);

            exit(EXIT_SUCCESS);
        }else{
            pids[i] = cur_pid;
        }
    }

    for(int i = 0; i < files_count; i++){
        int status;
        waitpid(pids[i], &status, 0);
        if(!WIFEXITED(status)){
            perror("Invalid status");
            exit(EXIT_FAILURE);
        }
    }

    for(int i = 0; i < files_count; i++){
        close(fd[i][1]);
    }

    uint64_t overall_sum = 0;
    uint64_t sum;
    for(int i = 0; i < files_count; i++){
        sum = 0;
        if(read(fd[i][0], &sum, sizeof(sum)) == -1){
                perror("Error writing");
                exit(EXIT_FAILURE);
        }
        overall_sum += sum;
    }

    for(int i = 0; i < files_count; i++){
        close(fd[i][0]);
    }

    printf("Overall sum is %ld\n", overall_sum);

    return 0;
}
