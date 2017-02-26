/*
 * kurs_13_blokady_zapis_odczyt.c
 *
 *  Created on: 26 lut 2017
 *      Author: lokkus
 */

#include "common.h"

static pthread_rwlock_t blokada;
int wartosc;    /* obiekt chroniony blokada */
static const int N = 5;
static const int K = 2;

/* watek zmienia wartosc */

static void* pisarz(void* numer){
    while(1){
        printf(" pisarz #%d czeka na dostep\n", (int)numer);
        errno = pthread_rwlock_wrlock(&blokada);
        test_errno("pthread_ rwlock_wrlock");
        printf(" pisarz #%d ustawia nowa wartosc\n", (int)numer);
        ms_sleep(113);

        printf(" pisarz #%d zwalnia blokade\n", (int)numer);
        errno = pthread_rwlock_unlock(&blokada);
        test_errno("pthread_rwlock_unlock");

        ms_sleep(317);
    }

    return NULL;
}

/* watek tylko odczytuje wartosc */
static void* czytelnik(void* numer){
    int errno;
    while(1){
        printf("  czytelnik #%d czeka na dostep\n", (int)numer);
        errno = pthread_rwlock_rdlock(&blokada);
        test_errno("pthread_rwlock_rdlock");
        printf("  czytelnik #%d odczytuje wartosc\n");

        ms_sleep(13);

        printf("  czytelnik #%d zwalnia blokade\n", (int)numer);
        errno = pthread_rwlock_unlock(&blokada);
        test_errno("pthread_rwlock_unlock");

        ms_sleep(13);
    }
    return NULL;
}

void main_blokady_zapis_odczyt(){
    pthread_t id;
    int i;

    pthread_rwlock_init(&blokada, NULL);

    /* utworzenie K watkow piszacych */
    for(i = 0; i<K; i++){
        errno = pthread_create(&id, NULL, czytelnik, (void*)i);
        test_errno("pthread_create");
    }

    /* utworzenie N watkow czytajacych */
    for(i = 0; i<N; i++){
        errno = pthread_create(&id, NULL, pisarz, (void*)i);
    }

    /* kilka sekund na prace watkow i koniec */
    ms_sleep(1500);
}

