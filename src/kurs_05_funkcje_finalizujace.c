/*
 * kurs_05_funkcje_finalizyjace.c
 *
 *  Created on: 11 lut 2017
 *      Author: lokkus
 */


#include "common.h"

static void zwolnij_pamiec(void* adres){
    printf("Zwalnianie pamieci spod adresu %p\n", adres);
    free(adres);
}

static void* watek(void* id){
    char* tablica1 = malloc(100);
    char* tablica2 = NULL;

    printf("watek #%d zaalokowal 100 bajtow pod adresem %p\n", (int)id, tablica1);

    pthread_cleanup_push(zwolnij_pamiec, tablica1);
    if(tablica1){
        tablica2 = malloc(200);
        printf("watek #%d zaalokowal 200 bajtow pod adresem %p\n", (int)id, tablica2);

        pthread_cleanup_push(zwolnij_pamiec, tablica2);
        if((int)id > 0){
            /* watek konczy sie w tym punkcie, funkcje finalizujace zostana uruchomione */
            pthread_exit(NULL);
        }
        pthread_cleanup_pop(1);
    }
    pthread_cleanup_pop(1);

    printf("watek #%d zakonczyl sie\n", (int)id);
    return NULL;
}

int main_f_finalizujace(int argc, char* argv[]){
    pthread_t id1, id2;

    /* utworzenie 2 watkow */
    errno = pthread_create(&id1, NULL, watek, (void*)(int)0);
    test_errno("pthread_create");
    sleep(2);

    errno = pthread_create(&id2, NULL, watek, (void*)(int)1);
    test_errno("pthread_create");

    /* oczekiwanie na ich zakonczenie */
    pthread_join(id1, NULL);
    pthread_join(id2, NULL);
    return EXIT_SUCCESS;

}
