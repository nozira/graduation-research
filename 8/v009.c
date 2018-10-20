#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "./MT.h"
#include "./define.h"
#include "./read-conect.h"
#include "./read_population.h"

int num[numTown];
int conect[numTown][20];
int population[numTown];
int SUM_population;
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
void swap(int *a, int *b);
void swap_indivi(indivisual *a, indivisual *b);
void bubsort();
void elite_save();
int numArea(int indviNnmber);

int main(){

    int output[numTown][20];
    int out[numTown];

    init_genrand((unsigned)time(NULL));
    read_conect("conect_id.txt");
    read_population("0.txt");
    initial();
    for(int y=0;y<GENERATION_MAX;y++){
        fitness();
        bubsort();
        crossover();
        printf("#%3d\n",y);
        printf("%20.8f\n",pop[0].fitness);
    }
    int zen=0;
    int r=0;
    for(int x=0;x<numTown;x++){
        for(int j= 1; j < numTown; j++){
            if(x==pop[0].area[j]){
                out[x]=out[x] + population[j];
            }
        }
        if(out[x]!=0){
            printf("%10d::%3d\n",out[x],r);
            r++;
            zen=zen+out[x];
        }

    }
printf("%10d##\n",zen);
    /*
    for(int k= 0; k < numTown; k++){
        for(int j= 0; j < 20; j++){
            output[k][j]=0;
        }
    }
    int No=0;
    int ID=0;
    for(int k= 0; k < numTown; k++){
        printf("%d############\n",k);
        int YorN=0;
        for(int j= 1; j < numTown; j++){
            if(k==pop[0].area[j]){
                printf("%4d::",j);
                output[No][ID]=j;
                ID++;
                YorN=1;
            }
        }
        if(YorN==1){
            No++;
        }
        printf("\n");
    }
    for(int k= 0; k < numTown; k++){
        printf("##%3d##\n",k);
        int YorN=0;
        for(int j= 0; j < 20; j++){
            if(output[k][j]!=0){
                printf("%d:",output[k][j]);
                YorN=1;
            }
        }
        if(YorN==0){
            break;
        }
        printf("\n\n\n");
    }*/
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

    IDEAL_value = SUM_population / (JP / 289) ;

    int K;

    for(int i = 0; i <POP_SIZE;i++){
        int sumArea[numArea(i)];
        for(int A=0;A<numArea(i);A++){
            sumArea[A]=0;
            for(int j=1;j<numTown;j++){
                if(A==pop[i].area[j]){
                    sumArea[A] = sumArea[A] + population[j];
                }
            }
        }
        pop[i].fitness = 0;
        for(int A=0;A<numArea(i);A++){
            K = (numArea(i)-((SUM_population / JP)*289))*(numArea(i)-((SUM_population / JP)*289));
            pop[i].fitness = pop[i].fitness + (((IDEAL_value - sumArea[A])*(IDEAL_value - sumArea[A]))*K);
        }
    }

}
void crossover() {
	int cross_point;
    int erro_point;
    int choise_E;

    cross_point = genrand_int32() % numTown;
	for (int i = 0; i < POP_SIZE; i++) {
		for (int j = 1; j < numTown; j++) {
            if(j % 2 ==0){
                choise_E=genrand_int32()%(POP_SIZE/2);
                swap(&pop[0].chrom[j], &pop[choise_E].chrom[j]);
                swap(&pop[0].area[j], &pop[choise_E].area[j]);
            }   
		}
        for (int j = 1; j < numTown; j++) {
            pop[i].chrom[j]=pop[0].chrom[j];
            pop[i].area[j] = pop[0].area[j];

            if ((genrand_int32() % 10) == 0) {
                erro_point = genrand_int32() % (num[j]+1);
                while(erro_point==1){
                    erro_point = genrand_int32() % (num[j]+1);
                }
                pop[0].chrom[j] = conect[j][erro_point];
	        }
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
void swap_indivi(indivisual *a,indivisual *b){
	indivisual temp;
	temp = *a ;
	*a   = *b;
	*b = temp;
}
void swap(int *a, int *b) {
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
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