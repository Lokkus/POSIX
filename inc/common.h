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
#include "kurs_02_przekazywanie_argumentow.h"
#include "kurs_04_priorytety_watkow.h"
#include "kurs_06_prywatne_dane.h"
#include "kurs_09_odczyt_czasu_CPU.h"

#define test_errno(msg) \
    do{ \
        if(errno){ \
            perror(msg); \
            exit(EXIT_FAILURE); \
        } \
    }while(0)


void ms_sleep(const unsigned int ms);
void main_pthread_create(int argc, char* argv[]);
void main_atrybuty(int argc, char* argv[]);
int main_f_finalizujace(int argc, char* argv[]);
int main_przerywanie(int argc, char* argv[]);
int main_pthread_atfork(int argc, char* argv[]);
void main_mutexy();
int mutexy_rozne(int argc, char* argv[]);
void main_zmienne();
void main_blokady_zapis_odczyt();
void main_bariery();
int main_pliki(int argc, char* argv[]);



int main_wazniak_watki(int argc, char* argv[]);


#endif /* COMMON_H_ */
