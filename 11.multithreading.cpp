#include <stdio.h>
#include <pthread.h>
void *printNumbers(void *threadId) {
    int id = *((int *)threadId);
    int i;
    for ( i = 1; i <= 5; i++) {
        printf("Thread %d: %d\n", id, i);
    }
    pthread_exit(NULL);
}
int main() {
    pthread_t thread1, thread2;
    int id1 = 1;
    int id2 = 2;
    pthread_create(&thread1, NULL, printNumbers, (void *)&id1);
    pthread_create(&thread2, NULL, printNumbers, (void *)&id2);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    printf("Main thread exiting.\n");
return 0;
}