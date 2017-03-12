/*
 * kurs_16_wazniak_watki.c
 *
 *  Created on: 11 mar 2017
 *      Author: lokkus
 */
#include "common.h"


static void* watek(void* arg){
    printf("Jestem w watku numer %d\n", (int)arg);
    return NULL;
}

int main_wazniak_watki(int argc, char* argv[]){
    pthread_t id[5];
    int i;

    for(i = 0; i<5; i++){
        pthread_create(&id[i], NULL, watek, (int)i);
        test_errno("Pthread_create");
    }

    for(i = 0; i<5; i++){
        pthread_join(id[i], NULL);
    }

    return EXIT_SUCCESS;
}
