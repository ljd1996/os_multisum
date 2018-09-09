#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

static int N = 0;
static long M = 0;
static long sum = 0;
static long count = 0;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


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
    sscanf(argv[1], "%d", &N);
    sscanf(argv[2], "%ld", &M);

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

    gettimeofday(&end, NULL);
    printf("%ld", 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec);

    return 0;
}
