/*
 * Author: Daniel Cabral Silveira
 *
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef struct _data {
    int time;
    void *args;
    void (*callback)(void *);
} Data;

void *func(void *args) {
    Data *data = (Data *)args;
    void  (*callback)(void *);
    int time = data->time;
    printf("Dentro da thread.\n");;
    sleep(time);
    callback = data->callback;
    callback(data->args);
    free(data);
    data=NULL;
    return NULL;
}

void timer(void (*callback)(void *), void *args, int time) {
    pthread_t thread_id;
    int thread;

    Data *data = malloc(sizeof(Data));
    data->time = time;
    data->callback = callback;
    data->args = args;

    thread = pthread_create(&thread_id, NULL, func, (void *) data);
    if(thread != 0) {
        printf("Erro ao chamar thread.\n");
    }
    pthread_detach(pthread_self());
}
