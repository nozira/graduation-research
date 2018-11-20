#include "define.h"

int read_population(char file_name[260],int year){
    char ch;
    FILE *fp;
    fp = fopen(file_name, "r");

    //erro
    if( fp == NULL ) {
        perror("ERRO\n");
        return 1;
    }

    //read-pop[]
    char str[20];
    int countNumTown = 0;
    sum_Population[year] = 0;

    while( ( fgets(str,20,fp) ) != NULL ) {
        population[year][countNumTown] = population[year][countNumTown] + atoi(str);
        sum_Population[year] = sum_Population[year] + atoi(str);
        countNumTown = countNumTown + 1;
    }
    fclose(fp);
}