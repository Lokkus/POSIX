/*
 * kurs_06_prywatne_dane.c
 *
 *  Created on: 12 lut 2017
 *      Author: lokkus
 */


#include "common.h"
static const int N = 3;

/* funkcja wypisuje wiersz, poprzedzajac go prefixem przypisanym do watku */
static void wyswietl(const char* napis){
    char* prefix = (char*)pthread_getspecific(klucz);
    if(prefix == NULL){
        /* nalezy zabezpiecznyc sie przed sytuacja, gdy dany watek nie przygotowal nic do klucza */
        puts(napis);
    }
    else{
        printf("%s:, %s\n", prefix, napis);
    }
}

/* destruktor klucza */
static void destruktor (void* napis){
    printf("wywolano destruktor, adres pamieci do zwolnienia: %p ('%s')\n", napis, (char*)napis);
    free(napis);
}

static void* watek(void* napis){
    /* ustawienie prefiksu w lokalnych danych watku */
    int status = pthread_setspecific(klucz, napis);

    if(status){
        fprintf(stderr, "pthread_setspecific: %s\n", strerror(status));
    }
    else{
        printf("Adres napisu: %p ('%s')\n", napis, (char*)napis);
    }
    wyswietl("Witaj w rownoleglym swiecie!");
    sleep(1);
    wyswietl("Watek wykonuje prace");
    sleep(1);
    wyswietl("watek zakonczony");
    return NULL;
}

int main_prywatne(int argc, char* argv[]){
    pthread_t id[N];
    int i;
    /* prefixy dla komunikatow z watkow */
    char* prefix[3] = {"***", "!!!", "###"};

    /* utworzenie klucza */
    errno = pthread_key_create(&klucz, destruktor);
    test_errno("pthread_key_create");

    /* utworzenie watkow */
    for(i = 0; i<N; i++){
        errno = pthread_create(&id[i], NULL, watek, (void*)strdup(prefix[i%3]));
        test_errno("pthread_create");
    }

    /* oczekiwanie na ich zakonczenie */

    for(i = 0; i<N; i++){
        pthread_join(id[i], NULL);
    }
    /*usuniecie klucza */
    errno = pthread_key_delete(klucz);
    test_errno("pthread_key_delete");
    return EXIT_SUCCESS;
}

