#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <semaphore.h>

#define PERM S_IRUSR|S_IWUSR

static int N = 0;
static long M = 0;

const static char *fileInput = "input.txt";
const static char *fileOutput = "output.txt";

typedef struct {
    long sum;
    long count;
    sem_t S;
} Process;

void getInput() {
    FILE *pFile = fopen(fileInput, "r");
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

void setOutput(long result) {
    FILE *pFile = fopen(fileOutput, "w");
    if (pFile == NULL) {
        perror("Error opening file");
    } else {
        fprintf(pFile,"%ld", result);
        fclose(pFile);
    }
}

int main(int argc, char const *argv[]) {
    clock_t start = clock();
    
    getInput();

    printf("N = %d\n", N);
    printf("M = %ld\n", M);

    int shm_id;
    Process *pProcess;

    if((shm_id = shmget(IPC_PRIVATE, sizeof(Process), PERM)) == -1){  
        printf("Create Share Memory Error.\n");
        return -1;
    }

    pProcess = (Process *)shmat(shm_id, NULL, 0);
    pProcess->sum = 0;
    pProcess->count = 0;

    sem_init(&pProcess->S, 0, 1);

    pid_t pid;
    int status;

    for (int i = 0; i < N; i++) {
        pid =fork();
        if (pid == 0 || pid == -1) {
            break;
        }
    }

    if(pid==-1) {
        printf("fail to fork!\n");
        return -1;
    } else if(pid == 0) {
        while (pProcess->count <= M) {
            sem_wait(&pProcess->S);
            if (pProcess->count <= M) {
                pProcess->sum += pProcess->count++;
            }
            sem_post(&pProcess->S);
        }
    } else {
        wait(&status);

        sem_destroy(&pProcess->S);
        setOutput(pProcess->sum);

        printf("the final result = %ld\n", pProcess->sum);
        printf("the tatol time = %ld\n", clock()-start);
    }

    return 0;
}
