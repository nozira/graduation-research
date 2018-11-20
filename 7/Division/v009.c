#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "./header/MT.h"
#include "./header/define.h"
#include "./header/read-conect.h"
#include "./header/read_population.h"

int num[numTown];
int conect[numTown][20];
int population[5][numTown];
int sum_Population[5];
double  IDEAL_value;

typedef struct {
	int chrom[numTown];
    int area[numTown];
	double fitness;
}indivisual;

indivisual pop[POP_SIZE];

void initial();
void fitness();
void crossover();
void bubsort();
int numArea(int indviNnmber);

int main(int argc, char *argv[]){

    init_genrand((unsigned)time(NULL));
    read_conect(argv[1]);
    read_population(argv[2],0);////////////////////
    read_population(argv[3],1);
    read_population(argv[4],2);
    read_population(argv[5],3);
    read_population(argv[6],4);

    initial();

    for(int y=0;y<GENERATION_MAX;y++){
        fitness();
        bubsort();
        crossover();
    }
    FILE *outputfile;         // 出力ストリーム
    outputfile = fopen(argv[7], "w");  // ファイルを書き込み用にオープン(開く)
    if (outputfile == NULL) {          // オープンに失敗した場合
        printf("cannot open\n");         // エラーメッセージを出して
        exit(1);                         // 異常終了
    }
    for(int k= 1; k < numTown; k++){
        fprintf(outputfile,"%4d:%4d\n",k,pop[0].area[k]); // ファイルに書く
    }
    fclose(outputfile);
}
void initial(){
    int choise;
    int area=0;
    int tmp[numTown];
    for(int i= 0; i < POP_SIZE; i++){
        for(int j= 0; j < numTown; j++){
            choise = genrand_int32() % (num[j]+1);
            if(choise==1){
                choise=0;
            }
            if(j==0){
                pop[i].chrom[j]=999999;
                pop[i].area[j] =999999;
            }
            else{
                pop[i].chrom[j] = conect[j][choise];
                pop[i].area[j] = -1;
            }
        }
    }

    for(int i = 0; i <POP_SIZE;i++){
        area=0;
        for(int j = 1; j < numTown; j++ ){
            pop[i].area[j]=-1;
        }
        for(int j = 1; j < numTown;j++){
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
    }
    for(int i = 1;i<numTown;i++){
        tmp[i]=0;
    }
    for(int i = 1;i<numTown;i++){
        tmp[pop[i].area[i]]++;
    }
    for(int i = 1;i<numTown;i++){
        if(tmp[i]==0){
            area--;
            for(int j =1;j<numTown;j++){
                if(pop[i].area[j]==area){
                    pop[i].area[j]=i;
                }
            }
        }
    }
}
void fitness(){
    for(int i = 0; i <POP_SIZE;i++){
        pop[i].fitness = 0;
    }
    for(int yearCount = 0; yearCount < 5 ;yearCount++ ){
        IDEAL_value = sum_Population[yearCount] /289;
        for(int i = 0; i <POP_SIZE;i++){
            double SSR = 0;
            int sumArea[numArea(i)];
            for(int areaCount = 0; areaCount < numArea(i);areaCount++){
                sumArea[areaCount] = 0;
                for(int j = 1; j < numTown; j++){
                    if(areaCount == pop[i].area[j]){
                        sumArea[areaCount] = sumArea[areaCount] + population[yearCount][j];
                    }
                    else{
                    }
                }
                SSR = SSR + ((IDEAL_value - sumArea[areaCount])*(IDEAL_value - sumArea[areaCount]));
            }
            pop[i].fitness = pop[i].fitness + (SSR*(numArea(i)*numArea(i)));
        }
    }

}
void crossover() {

    int chromChild[numTown];
    int areaChild[numTown];

    chromChild[0]=99999;
    areaChild[0]=99999;


    for(int j =0; j < numTown; j++){
        int _0_or_1;
        _0_or_1 = genrand_int32() % 2;
        chromChild[j] = pop[_0_or_1].chrom[j];
        areaChild[j] = pop[_0_or_1].area[j];
    }


	for (int i = 1; i < POP_SIZE; i++) {
        for(int j =0; j < numTown; j++){
            pop[i].chrom[j] = chromChild[j];
            pop[i].area[j] = areaChild[j];
        }
	}
}
void bubsort() {
    indivisual temp;

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