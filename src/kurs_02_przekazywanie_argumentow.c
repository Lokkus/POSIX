/*
 * kurs_02_przekazywanie_argumentow.c
 *
 *  Created on: 10 lut 2017
 *      Author: lokkus
 */


#include "common.h"

static void* watek1(void* arg){
    Wizytowka *w = (Wizytowka*)arg;
    printf("Wizytowka w watku1\nImie: %s\nNazwisko: %s\nWiek: %d\n", w->imie, w->nazwisko, w->wiek);
    return NULL;
}

static void* watek2(void* liczba){
    char *napis;
    int i;
    napis = malloc((int)liczba+1);
    if(napis){
        for(i = 0; i<(int)liczba; i++){
            napis[i] = 'z';
        }
        napis[(int)liczba] = 0;
    }
    return napis;
}
static Wizytowka utworz_wizytowke(char* imie, char* nazwisko, int wiek){
    Wizytowka w;
    w.imie = malloc(strlen(imie)*sizeof(char));
    strcpy(w.imie, imie);
    w.nazwisko = malloc(strlen(nazwisko)*sizeof(char));
    strcpy(w.nazwisko, nazwisko);
    w.wiek = wiek;

    return w;
}
static void kasuj_wizytowke(Wizytowka* wiz){
    free(wiz->imie);
    free(wiz->nazwisko);
}
void main_przekazywanie_argumentow(int argc, char* argv[]){
    pthread_t w1, w2;

    Wizytowka wiz;
    char* wynik;
    wiz = utworz_wizytowke("Marcin", "Kubicz", 34);

    errno = pthread_create(&w1, NULL, watek1, &wiz);
    test_errno("pthread_ create w1");

    errno = pthread_create(&w2, NULL, watek2, (void*)11);
    test_errno("pthread_create w2");

    /* oczekiwanie na zakonczenie watkow */

    errno = pthread_join(w1, NULL);
    test_errno("pthread_join w1");

    errno = pthread_join(w2,(void**)&wynik);
    test_errno("pthread_join w1");

    if(wynik){
        printf("Watek zwrocil wynik %s", wynik);
    }
    else{
        puts("Watek 2 nic nie zwrocil\n");
    }

    kasuj_wizytowke(&wiz);
    free(wynik);


}
