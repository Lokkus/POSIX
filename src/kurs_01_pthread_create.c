/*
 * kurs_01_pthread_create.c
 *
 *  Created on: 10 lut 2017
 *      Author: lokkus
 */


#include "common.h"


static void* watek (void* _arg){
    puts("Witaj w roznoleglym swiecie");
    return NULL;
}

void main_pthread_create(int argc, char* argv[]){
    pthread_t id, id2;
    int i;
    pthread_t iden1, iden2;

    errno = pthread_create(&id, NULL, watek, NULL);
    test_errno("pthread_create");
    iden1 = pthread_self();

    errno = pthread_create(&id2, NULL, watek, NULL);
    test_errno("pthread_create");
    iden2 = pthread_self();

    if(pthread_equal(iden1, iden2)){
        printf("Watki 1 i 2 maja rowne ID\n");
    }
    else{
        printf("Watki maja rozne ID\n");
    }

    errno = pthread_join(id, NULL);
    test_errno("pthread_join");

    errno = pthread_join(id2, NULL);
    test_errno("pthread_join");


}
