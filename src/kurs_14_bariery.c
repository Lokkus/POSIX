/*
 * kurs_14_bariery.c
 *
 *  Created on: 26 lut 2017
 *      Author: lokkus
 */

#include "common.h"

static pthread_barrier_t bariera;
static const int N = 10;

/* w tym programie bariera sluzy do wstrzymania programu do czasu az wszystkie
 * watki skoncza dzialanie
 */

static void* watek(void* numer){
    int s, status;

    s = rand()%4 + 1;
    printf("\twatek #%d rozpoczety, zostanie wstrzymany na %d sekund\n", (int)numer, s);

    sleep(s);

    printf("\twatek osiagnal bariere\n", (int)numer);
    status = pthread_barrier_wait(&bariera);

    switch(status){
    case 0: /* ok */
        break;
    case PTHREAD_BARRIER_SERIAL_THREAD:
        printf("\twszystkie watki osiagnely bariere PTHREAD_BARRIER_SERIAL_THREAD w watku #%d\n", (int)numer);
        break;

    default:
        fprintf(stderr, "pthread_barrier_wait: %s\n", strerror(status));
        break;
    }
    return NULL;
}

void main_bariery(){
    int i;
    pthread_t id[N];

    srand(time(NULL));

    printf("zostanie uruchomionych %d watkow\n", N);

    errno = pthread_barrier_init(&bariera, NULL, N);
    test_errno("pthread_barrier_init");

    for(i = 0; i<N; i++){
        errno = pthread_create(&id[i], NULL, watek, (void*)i);
        test_errno("pthread_create");
    }

    /* oczekiwanie na dojscie do bariery wszystkich watkow */
    for(i = 0; i<N; i++){
        errno = pthread_join(id, NULL);
        test_errno("pthread_join");
    }

    /* zwolnienie bariery */
    errno = pthread_barrier_destroy(&bariera);
    test_errno("pthread_barrier_destroy");
}
