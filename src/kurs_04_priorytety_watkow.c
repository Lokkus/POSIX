/*
 * kurs_03_priorytety_watkow.c
 *
 *  Created on: 11 lut 2017
 *      Author: lokkus
 */

#include "common.h"
static const int N = 4;

static void* watek(void* _arg){
    Arg* arg = (Arg*)_arg;
    arg->licznik = 0;
    while(!arg->przerwij){
        arg->licznik +=1;
        usleep(10);
    }

    return NULL;
}

int main_priorytety(int argc, char* argv[]){
    pthread_t id[N];
    pthread_attr_t attr;
    Arg arg[N];
    int pmin, pmax;
    int i, sched_policy;
    struct sched_param param;

    sched_policy = SCHED_OTHER;

    if(argc > 1){
        switch(atoi(argv[1])){

        case 0:
            sched_policy = SCHED_OTHER;
            break;

        case 1:
            sched_policy = SCHED_RR;
            break;

        case 2:
            sched_policy = SCHED_FIFO;
            break;

        default:
            break;
        }
    }
    else{
        puts("program [0|1|2]");
        return EXIT_FAILURE;
    }

    pmin = sched_get_priority_min(sched_policy);
    pmax = sched_get_priority_max(sched_policy);

    switch(sched_policy){

    case SCHED_OTHER:
        printf("SCHED_OTHER w zakresie %d ... %d\n", pmin, pmax);
        break;

    case SCHED_RR:
        printf("SCHED_RR: priorytety w zakresie %d ... %d\n", pmin, pmax);
        break;

    case SCHED_FIFO:
        printf("SCHED_FIFO: priorytety w zakresie %d ... %d\n", pmin, pmax);
        break;
    }

    errno = pthread_attr_init(&attr);
    test_errno("pthread_attr_init");

    /* parametry szeregowania odczytywane z atrybutow */
    errno = pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
    test_errno("pthread_attr_setinheritsched");


    /* wybor podanego algorytmu szeregowania */
    errno = pthread_attr_setschedpolicy(&attr, sched_policy);
    test_errno("pthread_attr_setschedpolicy");


    /* utworzenie kilku watkow z roznymi priorytetami */
    for(i = 0; i<N; i++){
        /* kolejne watki maja coraz wyzsze priorytety */
        param.__sched_priority = pmin + (pmax - pmin) * i / (float)(N-1);
        arg[i].przerwij = 0;
        arg[i].licznik = 0;
        arg[i].priorytet = param.__sched_priority;

        /* ustawienie priorytetu */
        errno = pthread_attr_setschedparam(&attr, &param);
        test_errno("pthread_attr_setschedparam");

        /* uruchomienie watku */
        errno = pthread_create(&id[i], &attr, watek, &arg[i]);
        test_errno("pthread_create");

        printf("Uwtorzono watek #%d o priorytecie  %d\n", i, arg[i].priorytet);
    }

    errno = pthread_attr_destroy(&attr);
    test_errno("pthread_attr_destroy");

    /* oczekiwanie */
    sleep(2);

    /* ustawienie flagi zakończenia pracy, ktora testuja funkcje watkow oraz odczyt ich biezacych licznikow */

    for(i = 0; i<N; i++){
        arg[i].przerwij = 1;
        printf("watek %d (priorytet %3d): licznik = %d\n", i, arg[i].priorytet, arg[i].licznik);
    }

    /* oczekiwanie na ich zakonczenie */
    for(i = 0; i<N; i++){
        errno = pthread_join(id[i], NULL);
        test_errno("pthread_join");
    }
    return EXIT_SUCCESS;

}
