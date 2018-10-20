#include "define.h"

int read_population(char file_name[260]){
    int city02 = 0;//count of cityID 
    char ch03;
    FILE *fp03;
    fp03 = fopen(file_name, "r");
    //erro////////////////////////
    if( fp03 == NULL ) {
        perror("ERRO\n");
        return 1;
    }
    //read-pop[]///////////////////
    int temp;
    char str[20];
    SUM_population = 0;
    while( ( fgets(str,20,fp03) ) != NULL ) {
        population[city02] = atoi(str);
        city02 = city02 + 1;
        SUM_population = SUM_population + atoi(str);
    }
    fclose(fp03);
}