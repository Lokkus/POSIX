/*
 * kurs_07_przerywanie_watkow.c
 *
 *  Created on: 12 lut 2017
 *      Author: lokkus
 */

#include "common.h"

static void zakonczenie(void* numer){
    printf("funkcja finalizujaca dla watku #%d\n", (int)numer);
}

static void* watek1(void* numer){
    int i, n;

    pthread_cleanup_push(zakonczenie, numer);

    /* ustawia mozliwosc przerwania i zwraca poprzednia watrosc
     * PTHREAD_CANCEL_ENABLE - przerwanie mozliwe
     * PTHREAD_CANCEL_DISABLE - przerwanie niemozliwe
     * */
    errno = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    test_errno("pthread_setcancelstate");

    /* ustawia sposob przerwania i zwraca poprzednia wartosc
     * PTHREAD_CANCEL_ASYNCHRONOUS - przerwanie asynchroniczne
     * PTHREAD_CANCEL_DEFFERED - przerwanie odpoznione
     * */
    errno = pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    test_errno("pthread_setcanceltype");

    printf("\turuchomiono watek #%d (przerwanie asynchroniczne) \n", (int)numer);
    while(1){
        n = 1000000;
        for(i=0; i<n; i++);
    }
    pthread_cleanup_pop(1);
    return NULL;
}

static void* watek2(void* numer){
    int i, n;
    pthread_cleanup_push(zakonczenie, numer);

    errno = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    test_errno("pthread_setcancelstate");

    errno = pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
    test_errno("pthread_setcanceltype");

    printf("\turuchomiono watek #%d (przerwanie opoznione) \n", (int)numer);
    while(1){
        /* punkt przerwania */
        pthread_testcancel();
        n=1000000;
        for(i = 0; i<n; i++);
    }
    pthread_cleanup_pop(1);
    return NULL;
}

static void* watek3(void* numer){
    int n = (void*)numer;
    pthread_cleanup_push(zakonczenie, numer);
    errno = pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
    test_errno("pthread_setcancelstate");

    printf("\turuchomiono watek #%d (przez 2 sekundy nie mozna przerwac)\n", (int)n);
    sleep(2);

    printf("\twatek #%d mozna juz przerwac\n", (int)numer);
    errno = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    test_errno("pthread_setcancelstate");
    pause();

    pthread_cleanup_pop(1);
    return NULL;
}

static void przerwanie(pthread_t id, const char* napis){
    printf("%s: wysylanie sygnalu przerwania do watku\n", napis);

    /* przerwanie wskazanego watku */
    errno = pthread_cancel(id);
    test_errno("pthread_cancel");

    printf("%s: wyslano, oczekiwanie na zakonczenie\n", napis);
    errno = pthread_join(id, NULL);
    test_errno("pthread_join");

    printf("%s: watek zakonczony\n", napis);
}

int main_przerywanie(int argc, char* argv[]){
    pthread_t id[3];

    /* utworzenie watkow */
    errno = pthread_create(&id[0], NULL, watek1, (void*)0);
    test_errno("pthread_create(1)");

    errno = pthread_create(&id[1], NULL, watek2, (void*)1);
    test_errno("pthread_create(2)");

    errno = pthread_create(&id[2], NULL, watek3, (void*)2);
    test_errno("pthread_create(3)");

    /*przerywanie kolejnych watkow */
    przerwanie(id[0], "#0");
    przerwanie(id[1], "#1");
    przerwanie(id[2], "#2");

}
