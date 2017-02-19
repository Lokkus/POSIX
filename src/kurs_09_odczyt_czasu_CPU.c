/*
 * kurs_09_odczyt_czasu_CPU.c
 *
 *  Created on: 12 lut 2017
 *      Author: lokkus
 */

#include "common.h"

static const int N = 10; /*liczba watkow */
static long clock_ms(const clockid_t id_zegara);

/* funkcja zwraca czas CPU dla watku (w milisekundach) */
static long get_thread_time(pthread_t id){
    clockid_t id_zegara;
    errno = pthread_getcpuclockid(id, &id_zegara);
    test_errno("pthread_getcpuclockid");

    return clock_ms(id_zegara);
}

/* funkcja zwraca czas w milisekundach dla wskazanego zegara */
static long clock_ms(const clockid_t id_zegara){
    struct timespec czas;

    if(clock_gettime(id_zegara, &czas)){
        perror("clock_gettime");
        exit(EXIT_FAILURE);
    }
    else{
        return (czas.tv_sec * 1000) + (czas.tv_nsec/1000000);
    }
}

static void* watek(void* _arg){
    Parametry* arg = (Parametry*)_arg;
    int i;
    printf("Watek #%d uruchomiony, dwa razy wykona %d pustych petli\n", (int)arg->id, (int)arg->n);

    for(i = 0; i<arg->n; i++);
    /* zuzycie czasu procesora */
    sleep(2);

    for(i = 0; i<arg->n; i++);
    /* zuzycie czasu procesora */

    /* podsumowanie pracy */
    printf("Watek #%d zakonczony, zuzyl %ldms czasu procesora\n", (int)arg->id, clock_ms(CLOCK_THREAD_CPUTIME_ID));
    return NULL;
}

int main_odczyt_czasu_CPU(int argc, char* argv[]){
    pthread_t id[N];
    Parametry param[N];
    int i;

    srand(time(NULL));

    printf("poczatek programu, uruchomione zostanie %d watkow\n", N);
    test_errno("pthread_create");

    /* utworzenie watku */
    for(i = 0; i<N; i++){
        param[i].id = i;
        param[i].n = rand() % 10000000 + 1;

        errno = pthread_create(&id[i], NULL, watek, &param[i]);
        test_errno("pthread_create");
    }

    /* stan na polmetu */

    sleep(1);
    puts("po okolo sekundzie watki zuzyly:");
    for(i=0; i<N; i++){
        printf("* #%d: %ldms\n", i, get_thread_time(id[i]));
    }

    /* oczekiwanie na zakonczenie watkow */
    for(i = 0; i<N; i++){
        errno = pthread_join(id[i], NULL);

        test_errno("pthread_join");
    }

    /* jeszcze podsumowanie */
    puts("");
    printf("glowny watek zluzyl %ldms czasu procesora\n", clock_ms(CLOCK_THREAD_CPUTIME_ID));
    printf("proces zuzyl %ldms czasu procesora\n", clock_ms(CLOCK_PROCESS_CPUTIME_ID));

    return EXIT_SUCCESS;

}
