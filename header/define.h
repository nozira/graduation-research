#define POP_SIZE 200
#define MUTATE_PROB 100
#define GENERATION_MAX 10
#define numTown 188 //自治体数
#define Year 5

typedef struct {
	int chrom[numTown];
    int area[numTown];
	double fitness;
}individual;

extern int connect[numTown][20];
extern int population[Year][numTown];
extern individual pop[POP_SIZE];
extern individual pop_next[POP_SIZE];

