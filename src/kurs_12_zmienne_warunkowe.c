/*
 * kurs_12_zmienne_warunkowe.c
 *
 *  Created on: 26 lut 2017
 *      Author: lokkus
 */


#include "common.h"

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
static const int N = 5;

char warunek = 0;

static void* watek(void* numer){
    printf("\t uruchomiono watek numer: %d\n",(int)numer);
    while(1){
        pthread_mutex_lock(&mutex);
        do{
            if(warunek){
                break;
            }
            else{
                printf("\twatek #%d oczekuje na sygnal ...\n", (int)numer);
                pthread_cond_wait(&cond, &mutex);
                printf("\twatek #%d otrzymal sygnal!\n", (int)numer);
            }

        }while(1);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void main_zmienne(){
    pthread_t id[N];
    int i;

    puts("Poczatek programu");

    for(i = 0; i<N; i++){
        errno =pthread_create(&id[i], NULL, watek, (void*)(i+1));
        test_errno("pthread_create");
    }

    /* wysylanie sygnalow */
    sleep(1);
    puts("pthread_cond_signal - sygnalizacja");
    pthread_cond_signal(&cond);

    sleep(1);

    puts("pthread_cond_broadcast - rozgloszenie");
    pthread_cond_broadcast(&cond);

    sleep(10);

    /* konczymy procesy bez ogladania sie na watki */
    puts("Koniec programu");


}

