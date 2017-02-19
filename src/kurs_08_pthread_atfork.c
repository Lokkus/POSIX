/*
 * kurs_08_pthread_atfork.c
 *
 *  Created on: 12 lut 2017
 *      Author: lokkus
 */

#include "common.h"

static const int N = 3;

pthread_t id[3];

static void* watek(void* numer){
    printf("\turuchomiono watek #%d\n", (int)numer);

    while(1){
        printf("\t\twatek #%d w procesie #%d\n", (int)numer, getpid());
        usleep(700*1000);
    }
    return NULL;
}

static void inicjalizacja_watkow(){
    int i;
    printf("tworzenie %d watkow w procesie %d\n", N, getpid());

    /* utworzenie watkow */
    for(i = 0; i<N; i++){
        errno = pthread_create(&id[i], NULL, watek, (void*)i+1);
        test_errno("pthread_create");
    }
}

int main_pthread_atfork(int argc, char* argv[]){
    pid_t pid;
    puts("Poczatek programu");
    inicjalizacja_watkow();

    /* rejestrowanie funkcji wykonywanej w procesie potomnym */
    errno = pthread_atfork(NULL, NULL, inicjalizacja_watkow);
    test_errno("pthread_atfork");

    sleep(1);

    pid = fork();
    printf("fork => %d\n", pid);

    switch(pid){

    case -1:
        test_errno("fork");
        break;

    /* proces potomny */
    case 0:
        sleep(2);
        break;

    /* proces nadrzedny */
    default:
        waitpid(pid, NULL, 0);
        test_errno("waitpid");
        break;
    }
    /* konczymy proces bez ogladania sie na watki */


}
