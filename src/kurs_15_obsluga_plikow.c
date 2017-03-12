/*
 * kurs_15_obsluga_plikow.c
 *
 *  Created on: 9 mar 2017
 *      Author: lokkus
 */

#include <fcntl.h>
#include <stdio.h>
#include "common.h"
//#include <sys/stat.h>

#define MAX 100

int main_pliki(int argc, char* argv[]){
    char buf[MAX];
    int desc_zrodlo, desc_cel;
    int lbajt;

    if(argc < 3){
        fprintf(stderr, "Za malo argumentow. Uzyj:\n");
        fprintf(stderr, "%s <plik zrodlowy> < plik docelowy>\n");
        exit(1);
    }

    desc_zrodlo = open(argv[1], O_RDONLY);
    if(desc_zrodlo == -1){
        perror("Blad otwarcia pliku");
        exit(1);
    }

    desc_cel = creat(argv[2], 0640);
    if(desc_cel == -1){
        perror("Blad utworzenia pliku docelowego");
        exit(1);
    }

    while((lbajt = read(desc_zrodlo, buf, MAX)) > 0){
        static i = 0;
        printf("Ala ma kota = %d\n", i++);
        if(write(desc_cel, buf, lbajt) == -1){
            perror("Blad zapisu pliku docelowego");
            exit(1);
        }
    }


    if(lbajt == -1){
        perror("Blad odczytu pliku zrodlowego");
        exit(1);
    }

    if(close(desc_zrodlo) == -1 || close(desc_cel) == -1){
        perror("Blad zamkniecia plikow");
        exit(1);
    }

    exit(0);
}

