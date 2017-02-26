/*
 * common.c
 *
 *  Created on: 26 lut 2017
 *      Author: lokkus
 */


#include "common.h"

void ms_sleep(const unsigned int ms){
    struct timespec time;
    time.tv_sec = (ms/1000);
    time.tv_nsec = (ms %1000)*1000000;
    nanosleep(&time, NULL);
}
