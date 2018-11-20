#define POP_SIZE 600
#define MUTATE_PROB 100
#define GENERATION_MAX 100
#define numTown 114 //自治体数
#define Year 5

typedef struct {
	int chrom[numTown];
    int area[numTown];
	double fitness;
}individual;

typedef struct {
	int population[numTown];
	int sumPopulation;
	double idealFitness;
}regionData;

extern int connect[numTown][20];
extern individual pop[POP_SIZE];
extern individual pop_next[POP_SIZE];
extern regionData  data[Year];