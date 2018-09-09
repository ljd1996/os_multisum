#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <semaphore.h>

#define PERM S_IRUSR|S_IWUSR

static int N = 0;
static long M = 0;

typedef struct {
    long sum;
    long count;
    sem_t S;
} Process;

int main(int argc, char const *argv[]) {

    sscanf(argv[1], "%d", &N);
    sscanf(argv[2], "%ld", &M);

    struct timeval start;
    struct timeval end;
    gettimeofday(&start, NULL);

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

        gettimeofday(&end, NULL);
        printf("%ld", 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec);
    }

    return 0;
}
