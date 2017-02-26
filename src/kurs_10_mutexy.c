/*
 * kurs_10_mutexy.c
 *
 *  Created on: 22 lut 2017
 *      Author: lokkus
 */


#include "common.h"

static const int N = 10;    /* liczba watkow */
static const int K = 100;   /* liczba iteracji */

pthread_mutex_t blokada;
#define BLOKADA

int licznik = 0;    /* zmienna ktora powinna byc chroniona blokada */

void* watek(void* numer){
    int i;
    for(i = 0; i<K; i++){
#ifdef BLOKADA
        errno = pthread_mutex_lock(&blokada);
        test_errno("pthread_mutex_lock");
#endif
        licznik = licznik+1;
        ms_sleep(1);
#ifdef BLOKADA
        errno = pthread_mutex_unlock(&blokada);
        test_errno("pthread_mutex_unlock");
#endif
    }

    return NULL;
}

void main_mutexy(){
    pthread_t id[N];
    int i;

    printf("licznik =%d\n", licznik);

    errno = pthread_mutex_init(&blokada, NULL);
    test_errno("pthread_mutex_init");

    for(i = 0; i<N; i++){
        errno = pthread_create(&id[i], NULL, watek, (void*)i);
        test_errno("pthread_create");
    }

    /* oczekiwanie na jego zakonczenie */
    for(i = 0; i<N; i++){
        errno = pthread_join(id[i], NULL);
        test_errno("pthread_join");
    }

    printf("licznik = %d, spodziewana wartosc = %d %s\n", licznik, N*K, (licznik != N*K ? "Blad": ""));

}
