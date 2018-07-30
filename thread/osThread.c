#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

static int N = 0;
static long M = 0;
static long sum = 0;
static long count = 0;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


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

void setOutput() {
    FILE *pFile = fopen("output.txt", "w");
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
        sum += count;
        count++;
        pthread_mutex_unlock(&mutex);
        printf("the thread result = %ld\n", sum);
    }
}

int main(int argc, char const *argv[]) {
    clock_t start = clock();
    
    getInput();

    printf("N = %d\n", N);
    printf("M = %ld\n", M);

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
    
    setOutput();

    printf("the final result = %ld\n", sum);
    printf("the tatol time = %ld\n", clock()-start);

    return 0;
}
