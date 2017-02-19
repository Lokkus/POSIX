/*
 * common.h
 *
 *  Created on: 10 lut 2017
 *      Author: lokkus
 */

#ifndef COMMON_H_
#define COMMON_H_

#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>
#include <pthread.h>
#include <sched.h>
#include <unistd.h>
#include <time.h>
#include "na_brudno.h"
#include "kurs_01_pthread_create.h"
#include "kurs_02_przekazywanie_argumentow.h"
#include "kurs_03_atrybuty.h"
#include "kurs_04_priorytety_watkow.h"
#include "kurs_05_funkcje_finalizyjace.h"
#include "kurs_06_prywatne_dane.h"
#include "kurs_07_przerywanie_watkow.h"
#include "kurs_08_pthread_atfork.h"
#include "kurs_09_odczyt_czasu_CPU.h"

#define test_errno(msg) \
    do{ \
        if(errno){ \
            perror(msg); \
            exit(EXIT_FAILURE); \
        } \
    }while(0)



#endif /* COMMON_H_ */
