/*
 * kurs_11_mutexy_rozne_zachowania.c
 *
 *  Created on: 22 lut 2017
 *      Author: lokkus
 */


#include "common.h"

static pthread_t id;
static pthread_mutex_t mutex;
static pthread_mutexattr_t mutexattr;

static void* watek(void* _args){
    int errno;

    //1
    puts("przed wykonaniem pthread_mutex_lock(1)");
    errno = pthread_mutex_lock(&mutex);
    test_errno("pthread_mutex_lock(1)");
    puts("...wykonano pthread_mutex_lock (1)");

    //2
    puts("przed wykonaniem pthread_mutex_lock(2)");
    errno = pthread_mutex_lock(&mutex);
    test_errno("pthread_mutex_lock(2)");
    puts("...wykonano pthread_mutex_lock (2)");

    //3
    puts("przed wykonaniem pthread_mutex_unlock(2)");
    errno = pthread_mutex_unlock(&mutex);
    test_errno("pthread_mutex_unlock(2)");
    puts("...wykonano pthread_mutex_unlock(2)");

    //4
    puts("przed wykonaniem pthread_mutex_unlock(1)");
    errno = pthread_mutex_unlock(&mutex);
    test_errno("pthread_mutex_unlock(1)");
    puts("...wykonano pthread_mutex_unlock(1)");

    return NULL;
}

int mutexy_rozne(int argc, char* argv[]){
    int errno;

    pthread_mutexattr_init(&mutexattr);

    if(argc > 1){
        switch(atoi(argv[1])){
        case 1:
            puts("mutex typu PTHREAD_MUTEX_ERRORCHECK");
            pthread_mutexattr_settype(&mutexattr, PTHREAD_MUTEX_ERRORCHECK);
            break;

        case 2:
            puts("mutex typu PTHREAD_MUTEX_RECURSIVE");
            pthread_mutexattr_settype(&mutexattr, PTHREAD_MUTEX_RECURSIVE);
            break;

        default:
            puts("mutex typu PTHREAD_MUTEX_NORMAL");
            pthread_mutexattr_settype(&mutexattr, PTHREAD_MUTEX_NORMAL);
            break;

        }
    }
    else{
        puts("uzycie programu [0|1|2]");
        return EXIT_FAILURE;
    }

    /*inicjalizacja mutexu */
    errno = pthread_mutex_init(&mutex, &mutexattr);
    test_errno("pthread_mutex_init");

    /* utworzenie watku */
    errno = pthread_create(&id, NULL, watek, NULL);
    test_errno("pthread_create");

    /* oczekiwanie na jego zakonczenie */
    pthread_join(id, NULL);
    test_errno("pthread_join");

    return EXIT_SUCCESS;

}
