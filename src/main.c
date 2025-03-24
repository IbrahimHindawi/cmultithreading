#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

static void *proc(void *arg) {
    char *input = (char *)arg;
    int a = 0;
    int const repeats = 10;
    while (a < repeats) {
        printf("input was '%s' at instance[%d]\n", input, a);
        sleep(1);
        if (a == repeats) {
            // kill thread
            printf("killing thread\n");
            pthread_exit(0);
        }
        a += 1;
    }
    // thread return == kill thread
    return NULL;
}

int main(int argc, char *argv[]) {
    printf("threading...\n");
    pthread_t pthread1;
    static char *thread_input1 = "I am thread no.1";
    int rc = pthread_create(&pthread1, NULL, proc, (void *)thread_input1);
    if (rc != 0) {
        printf("Error Occured: %d", rc);
        exit(0);
    }
    printf("main() join\n");
    pthread_join(pthread1, NULL);
    // pause();
    // pthread_exit(0);
    return 0;
}
