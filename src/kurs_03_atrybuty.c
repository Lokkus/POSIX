/*
 * kurs_03_atrybuty.c
 *
 *  Created on: 11 lut 2017
 *      Author: lokkus
 */

#include "common.h"

/* wszystkie atrybuty watku opisuje typ pthread_attr_t
 *
 */

static void wyswietl_atrybuty(const pthread_attr_t * attr){
    int x;
    size_t rozmiar;
    void* addr;
    struct sched_param param;

    puts("atrybuty watku");

    /* rodzaj watku */
    printf("Rodzaj: ");

    /* odczytuje rodzaj watku jaki ma zostac ustalony podczas jego tworzenia
     * rodzaj jest identyfikowany jedna z wartosci:
     * PTHREAD_CREATE_JOINABLE
     * PTHREAD_CREATE_DETACHED
     */
    errno = pthread_attr_getdetachstate(&attr, &x);
    test_errno("pthread_attr_getdetachstate");

    switch(x){

    case PTHREAD_CREATE_JOINABLE:
        puts("joinable");
        break;

    case PTHREAD_CREATE_DETACHED:
        puts("detached");
        break;

    default:
        break;
    }

    /* adres i rozmiar stosu */
    errno = pthread_attr_getstackaddr(attr, (void**)&addr);
    test_errno("pthread_attr_getstackaddr");

    printf("Adres stosu: %p\n", addr);

    errno = pthread_attr_getstacksize(attr, &rozmiar);
    test_errno("pthread_attr_getstacksize");

    printf("Rozmiar stosu: %lu (minimalny %lu)\n", rozmiar, PTHREAD_STACK_MIN);

    /* rozmiar obszaru zabezpieczajacego stos */
    errno = pthread_attr_getguardsize(attr, &rozmiar);
    test_errno("pthread_attr_getguardsize");
    printf("Rozmiar obszaru zabezpieczajacego stos: %lu\n", rozmiar);

    /* szeregowanie */
    errno = pthread_attr_getinheritsched(attr, &x);
    test_errno("pthread_attr_getinheritsched");
    switch(x){

    case PTHREAD_INHERIT_SCHED:
        puts("Parametry szeregowania dziedziczone");
        break;

    case PTHREAD_EXPLICIT_SCHED:
        puts("Parametry podawane bezposrednio");
        break;

        printf("algorytm szeregowania ");
        errno = pthread_attr_getschedpolicy(attr, &x);
        test_errno("pthread_attr_getschedpolicy");
        switch(x){

        case SCHED_OTHER:
            puts("SHED_OTHER");
            break;

        case SCHED_RR:
            puts("SCHED_RR");
            break;

        case SCHED_FIFO:
            puts("SCHED_FIFO");
            break;

        default:
            break;
        }

        errno = pthread_attr_getschedparam(attr, &param);
        test_errno("pthread_attr_getschedparam");
        printf("Priorytet: %d\n", param.__sched_priority);
        break;

        default:
            break;

    }

    /* zakres szeregowania */
    errno = pthread_attr_getscope(attr, &x);
    test_errno("pthread_attr_getscope");
    printf(" *zakres szeregowania* ");

    switch(x){
    case PTHREAD_SCOPE_PROCESS:
        puts("proces");
        break;

    case PTHREAD_SCOPE_SYSTEM:
        puts("system");
        break;

    default:
        break;
    }
}

void main_atrybuty(int argc, char* argv[]){
    pthread_attr_t attr;
    errno = pthread_attr_init(&attr);
    test_errno("pthread_attr_init");

    wyswietl_atrybuty(&attr);
}
