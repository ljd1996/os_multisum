#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

static int N = 0;
static long M = 0;
static long sum = 0;
static long count = 0;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

const static char *fileInput = "input.txt";
const static char *fileOutput = "output.txt";

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

void setOutput() {
    FILE *pFile = fopen(fileOutput, "w");
    if (pFile == NULL) {
        perror("Error opening file");
    } else {
        fprintf(pFile,"%ld", sum);
        fclose(pFile);
    }
}

void threadSum() {
    while (count <= M) {
        pthread_mutex_lock(&mutex);
        if (count <= M) {
            sum += count++;
        }
        pthread_mutex_unlock(&mutex);
    }
}

int main(int argc, char const *argv[]) {
    getInput();

    printf("N = %d\n", N);
    printf("M = %ld\n", M);

    if (N < 1 || N >= 100) {
        printf("N is behind 1 and 100.\n");
        return -1;
    }

    if (M < 0 || M >= 4294967296) {
        printf("M is behind 0 and 4294967296.\n");
        return -1;
    }

    struct timeval start;
    struct timeval end;
    gettimeofday(&start, NULL);

    int ret;
    pthread_t thread[N];
    for (int i = 0; i < N; i++) {
        ret = pthread_create(&thread[i], NULL, (void *)threadSum, NULL);

        if(ret != 0) {
            printf("create pthread-%d error!\n", i);
            return -1;
        }
    }

    for (int i = 0; i < N; i++) {
        pthread_join(thread[i], NULL);
    }
    
    printf("the final result = %ld\n", sum);

    gettimeofday(&end, NULL);
    printf("the tatol time = %ld us\n", 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec);

    setOutput();

    return 0;
}
