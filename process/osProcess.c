#include <stdio.h>
#include <stdlib.h>
// #include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/shm.h>

static int N = 0;
static long M = 0;
// static long sum = 0;
static long count = 0;
// static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


void getInput() {
    FILE *pFile = fopen("input.txt", "r");
    char line[20];
    if (pFile == NULL) {
        perror("Error opening file");
    } else {
        fseek(pFile, 2, SEEK_SET);
        if (fgets(line, 20, pFile) != NULL) {
            N = atoi(line);
        }
        
        fseek(pFile, ftell(pFile)+2, SEEK_SET);
        if (fgets(line, 20, pFile) != NULL) {
            M = atol(line);
        }
        fclose(pFile);
    }
}

// void setOutput() {
//     FILE *pFile = fopen("output.txt", "w");
//     if (pFile == NULL) {
//         perror("Error opening file");
//     } else {
//         fprintf(pFile,"%ld", sum);
//         fclose(pFile);
//     }
// }

int main(int argc, char const *argv[]) {
    clock_t start = clock();
    
    getInput();

    printf("N = %d\n", N);
    printf("M = %ld\n", M);

    pid_t pid;
    int status = 0;

    // shmget(0, sizeof(long), IPC_PRIVATE);
    long *sum = (long *)shmat(shmget(IPC_PRIVATE, sizeof(long), IPC_CREAT), NULL, 0);

    pid =fork();

    if(pid < 0) {
        perror("fork fail");
        return -1;
    }

    if(pid > 0) {
        wait(&status);
        // setOutput();

        // printf("the final result = %ld\n", *sum);
        // printf("the tatol time = %ld\n", clock()-start);
    } else {
        // while (count <= M) {
            // pthread_mutex_lock(&mutex);
            // sum += count;
            // count++;
            // pthread_mutex_unlock(&mutex);
            printf("the threa\n");
            *sum = 10;
            printf("the thread result = %ld\n", *sum);
        // }
    }

    return 0;
}
