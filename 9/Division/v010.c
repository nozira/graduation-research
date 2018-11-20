#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "./header/define.h"
#include "./header/MT.h"

int connect[numTown][20];
int seatsRegion;

regionData  data[Year];
individual pop[POP_SIZE];
individual pop_next[POP_SIZE];

void initial();
void fitness();
void bubsort();
int numArea();
void expressionArea();
int rank_choise();
void crossover();

int load_connect(char file_name[260]);
int load_population(char file_name[260],int year);

int main(int argc, char *argv[]){

    seatsRegion = atoi(argv[1]);

    printf("%10d\n",seatsRegion);

    load_connect(argv[2]);
    for(int y =0; y < Year;y++){
        load_population(argv[y+3],y);
    }
    initial();
    for(int g = 0; g < GENERATION_MAX; g++){
        //printf("%f\n",pop[0].fitness);
        fitness();
        bubsort();
        crossover();
    }

    FILE *outputfile;         // 出力ストリーム
    outputfile = fopen(argv[8], "w");  // ファイルを書き込み用にオープン(開く)
    if (outputfile == NULL) {          // オープンに失敗した場合
        printf("cannot open\n");         // エラーメッセージを出して
        exit(1);                         // 異常終了
    }
    for(int k= 0; k < numTown; k++){
        fprintf(outputfile,"%d,%d\n",k,pop[0].area[k]); // ファイルに書く
    }
    fclose(outputfile);
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
            //printf("%4d",connect[townCount][connectTownCount]);
            connectTownCount++;
        }else{
            if (townIDint==9999){
                connect[townCount][connectTownCount] = -1;
                connect[townCount][19] = connectTownCount;//最後の要素に隣接する自治体数を格納
                //printf("%4d\n",connect[townCount][19]);
                connectTownCount = 0;
                townCount++;
            }
        }
    }
    fclose(fp_connect);
}
int load_population(char file_name[260],int year){

    char townPOPstr[20];
    int  townPOPint;

    int townCount = 0;

    FILE *fp_population;
    fp_population = fopen(file_name, "r");

    if( fp_population == NULL ) {
        perror("ERRO\n");
        return 1;
    }
    while( ( fgets( townPOPstr, 20, fp_population ) ) != NULL ){
        townPOPint = atoi(townPOPstr);
        data[year].population[townCount] = townPOPint;
        // printf("%10d\n",data[year].population[townCount]);
        data[year].sumPopulation = data[year].sumPopulation + townPOPint;
        townCount++;
    }
    fclose(fp_population);
}
void initial(){
    int choice;

    for(int i= 0; i < POP_SIZE; i++){
        for(int j= 0; j < numTown; j++){
            choice = genrand_int32() % (connect[j][19]+1);//NUM
            pop[i].chrom[j] = connect[j][choice];
            pop[i].area[j] = -1;
        }
    }
    expressionArea();
}
void fitness(){
    for(int i = 0; i <POP_SIZE;i++){
        double FITNESS = 0;
        int temp;
        int NUM_AREA;
        NUM_AREA = numArea(i);
        int sumArea[NUM_AREA];
        for(int yearCount = 0; yearCount < 5 ;yearCount++ ){
            data[yearCount].idealFitness = data[yearCount].sumPopulation / seatsRegion;
            if(seatsRegion == NUM_AREA){
                for(int areaCount = 0; areaCount < NUM_AREA;areaCount++){
                    sumArea[areaCount] = 0;
                    for(int j = 0; j < numTown; j++){
                        if(areaCount == pop[i].area[j]){
                            sumArea[areaCount] = sumArea[areaCount] + data[yearCount].population[j];
                        }
                    }
                    FITNESS = FITNESS + ((data[yearCount].idealFitness - sumArea[areaCount])*(data[yearCount].idealFitness - sumArea[areaCount]));
                }
            }else{
                if(seatsRegion < NUM_AREA){
                    for(int areaCount = 0; areaCount < NUM_AREA;areaCount++){
                        sumArea[areaCount] = 0;
                        for(int j = 0; j < numTown; j++){
                            if(areaCount == pop[i].area[j]){
                                sumArea[areaCount] = sumArea[areaCount] + data[yearCount].population[j];
                            }
                        }
                    }
                    for (int n = 0; n < NUM_AREA; n++) {
                        for (int m = (NUM_AREA - 1); m > n; m--) {
                            if (sumArea[m - 1] > sumArea[m]) {
                                temp = sumArea[m - 1];
                                sumArea[m - 1] = sumArea[m];
                                sumArea[m] = temp;
                            }
                        }
                    }
                    for(int areaCount = 0; areaCount < NUM_AREA;areaCount++){
                        if(areaCount < seatsRegion){
                            FITNESS = FITNESS + ((data[yearCount].idealFitness - sumArea[areaCount])*(data[yearCount].idealFitness - sumArea[areaCount]));
                        }else{
                            FITNESS = FITNESS + (sumArea[areaCount]*sumArea[areaCount]);
                        }
                    }
                }else{
                    for(int areaCount = 0; areaCount < NUM_AREA;areaCount++){
                        sumArea[areaCount] = 0;
                        for(int j = 0; j < numTown; j++){
                            if(areaCount == pop[i].area[j]){
                                sumArea[areaCount] = sumArea[areaCount] + data[yearCount].population[j];
                            }
                        }
                    }
                    for (int n = 0; n < NUM_AREA; n++) {
                        for (int m = (NUM_AREA - 1); m > n; m--) {
                            if (sumArea[m - 1] > sumArea[m]) {
                                temp = sumArea[m - 1];
                                sumArea[m - 1] = sumArea[m];
                                sumArea[m] = temp;
                            }
                        }
                    }
                    for(int areaCount = 0; areaCount < seatsRegion;areaCount++){
                        if(areaCount < NUM_AREA){
                            FITNESS = FITNESS + ((data[yearCount].idealFitness - sumArea[areaCount])*(data[yearCount].idealFitness - sumArea[areaCount]));
                        }else{
                            FITNESS = FITNESS + (data[yearCount].idealFitness*data[yearCount].idealFitness);
                        }
                    }
                }
            }
        }
        pop[i].fitness = FITNESS;
    }
}
void crossover() {

    int parent_one;
    int parent_two;


    if(genrand_int32() % MUTATE_PROB==0){
        parent_two = genrand_int32() % (POP_SIZE-1);
    }

	for (int i = 0; i < POP_SIZE; i++) {
        parent_one = rank_choise();
        parent_two = rank_choise();
        if(genrand_int32() % MUTATE_PROB ==0){
            parent_one = genrand_int32() % (POP_SIZE-1);
            parent_two = genrand_int32() % (POP_SIZE-1);
        }
        for(int j =0; j < numTown; j++){
            int _0_or_1;
            _0_or_1 = genrand_int32() % 2;
            switch(_0_or_1){
                case 0:
                    pop_next[i].chrom[j] = pop[parent_one].chrom[j];
                    break;
                case 1:
                    pop_next[i].chrom[j] = pop[parent_two].chrom[j];
                    break;
            }
        }
	}
    for(int i = 1; i < POP_SIZE; i++){
        for(int j =0; j < numTown; j++){
            pop[i] = pop_next[i];
        }
    }
    expressionArea();
}
int rank_choise(){

    int rank[POP_SIZE];
    int probability = POP_SIZE;
    int range_probability = 0;
    int pop_choise;
    int search;

    for(int i = 0; i < POP_SIZE;i++){
        range_probability = range_probability + i;
        rank[i] = probability;
        probability = probability - 1;
    }
    search = rank[0];

    pop_choise = genrand_int32() % range_probability;
    for(int i = 1; i < POP_SIZE;i++){
        if (search > pop_choise){
            return i ;
            break;
        }
        else{
            search = search + rank[i];
        }
    }
}
void bubsort() {
    individual temp;

    for (int i = 0; i < (POP_SIZE - 1); i++) {
        for (int j = (POP_SIZE - 1); j > i; j--) {
            if (pop[j - 1].fitness > pop[j].fitness) {
                temp = pop[j - 1];
                pop[j - 1] = pop[j];
                pop[j] = temp;
            }
        }
    }
}
int numArea(int iNumber){
    int numArea=0;
    for(int j = 0; j < numTown; j++ ){
        for(int k = 0; k < numTown; k++ ){
            if(j==pop[iNumber].area[k]){
                numArea++;
                break;
            }else{
                if(j==numTown-1){
                    return numArea;
                }
            }
        }
    }
}
void expressionArea(){
    int area;
    int tmp[numTown];

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
                        for(int k=0;k<numTown;k++){
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
}