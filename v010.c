#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "./header/define.h"
#include "./header/MT.h"

int connect[numTown][20];
int population[Year][numTown];
int seatsRegion;
int sumPopulation;
double idealFitness;

individual pop[POP_SIZE];
individual pop_next[POP_SIZE];

void initial(int region);

int load_connect(char file_name[260]);
int load_population(char file_name[260],int year);

int main(int argc, char *argv[]){

    seatsRegion = (int)argv[1];
    sumPopulation = (int)argv[2];
    idealFitness = (int)argv[3];

    load_connect(argv[4]);
    for(int y =0; y < Year;y++){
        load_population(argv[y+5],y);
    }


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
        if(townIDint!=9999){
            connect[townCount][connectTownCount]= townIDint-1;
            printf("%4d",connect[townCount][connectTownCount]);
            connectTownCount++;
        }else{
            if (townIDint==9999){
                connect[townCount][connectTownCount] = -1;
                connect[townCount][19] = connectTownCount;//最後の要素に隣接する自治体数を格納
                printf("%4d\n",connect[townCount][19]);
                connectTownCount = 0;
                townCount++;
            }
        }
    }
    fclose(fp_connect);
}
int load_population(char file_name[260]){

    char townPOPstr[20];
    int  townPOPint;

    int townCount = 0;

    FILE *fp_population;
    fp_population = fopen(file_name, "r");

    if( fp_population == NULL ) {
        perror("ERRO\n");
        return 1;
    }
    data[region][year].sumPopulation = 0;
    while( ( fgets( townPOPstr, 20, fp_population ) ) != NULL ){
        townPOPint = atoi(townPOPstr);
        population[year][townCount] = townPOPint;
        printf("%7d\n",population[year][townCount]);
        townCount++;
    }
    fclose(fp_population);
}/*
void initial(int region){
    int choice;
    int area;
    int tmp[numTown];

    for(int i= 0; i < POP_SIZE; i++){
        for(int j= 0; j < numTown; j++){
            choice = genrand_int32() % (connect[region][j][19]+1);//NUM
            pop[i].chrom[j] = connect[region][j][choice];
            pop[i].area[j] = -1;
        }
    }
    for(int i = 0; i <POP_SIZE;i++){
        area=0;
        for(int j = 0; j < numTown;j++){
            if(pop[i].area[j]=-1){
                if(pop[i].chrom[j]==0){
                    pop[i].area[j]=area;
                    area++;
                }else{
                    if(pop[i].area[pop[i].chrom[j]]==-1){
                        pop[i].area[j] = area;
                        pop[i].area[pop[i].chrom[j]] = area;
                        area++;
                    }else{
                        pop[i].area[j]=pop[i].area[pop[i].chrom[j]];
                    }
                }
            }else{
                if(pop[i].chrom[j]!=0){
                    if(pop[i].area[pop[i].chrom[j]]==-1){
                        pop[i].area[pop[i].chrom[j]]=pop[i].area[j];
                    }else{
                        for(int k=1;k<numTown;k++){
                            if(pop[i].area[k]==pop[i].area[pop[i].chrom[j]]){
                                pop[i].area[k]= pop[i].area[pop[i].chrom[j]];
                            }else{
                                if(pop[i].area[pop[i].chrom[j]]==0){
                                    pop[i].area[j]=pop[i].area[pop[i].chrom[j]];
                                }
                            }
                        }
                    }
                }
            }
        }
        for(int k = 0; k < area; k++){
            tmp[k] = 0;
        }
        for(int k = 0; k < numTown; k++){
            tmp[pop[i].area[k]]++;
        }
        for(int k = 0; k < area; k++){
            if(tmp[k] == 0){
                area--;
                for(int j = 0; j < numTown; j++){
                    if(pop[i].area[j] > k){
                        pop[i].area[j]--;
                    }
                }
                for(int m = k+1; m < area; m++){
                    tmp[m-1] = tmp[m];
                }
            }
        }
    }
}*/