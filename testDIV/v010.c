#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define POP_SIZE 200
#define MUTATE_PROB 100
#define GENERATION_MAX 10
#define Region 10
#define Year 5

int (*connect)[20];
int numTown[Region];

typedef struct {
    int* population;
    int seatsRegion[Region];
    int sumPopulation[Region];
    double  idealFitness[Region];
}townData;

typedef struct {
	int* chrom;
    int* area;
	double fitness;
}individual;

townData data[Year];
individual pop[POP_SIZE];
individual pop_next[POP_SIZE];

int load_connect(char file_name[260]);
int load_population(char file_name[260]);

int main(){
    load_connect("connect_id.txt");
    return 0;
}

int load_connect(char file_name[260]){
    char townIDstr[20];
    int  townIDint;

    int townCount = 0;
    int connectTownCount = 0;

    FILE *fp_connect;
    fp_connect = fopen(file_name, "r");

    if( fp_connect == NULL ) {
        perror("ERRO\n");
        return 1;
    }
    while( ( fgets( townIDstr, 20, fp_connect ) ) != NULL ){
        townIDint = atoi(townIDstr);
        //printf("%d\n",townIDint);
        if(townIDint!=9999){
            (*(connect + townCount))[connectTownCount] = townIDint;
            printf("%d\n",(*(connect + townCount))[connectTownCount]);
            connectTownCount++;
        }else{
            if (townIDint==9999){
                break;
            }
        }
    }
    fclose(fp_connect);
}