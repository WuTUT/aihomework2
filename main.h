#include "stdio.h"
#include "math.h"
#include <stdlib.h>
#include <time.h>

#define	DMax 30 			// Max number of dimensions of the search space
#define funcMax 15		// Max number of functions sequentially solved
#define R_max 1000		// Max number of runs
#define	S_max 500 		// Max swarm size
#define zero  1.0e-40	// To avoid numerical instabilities on some machines
#define infinity 1.e+40

#define ulong unsigned long // To generate pseudo-random numbers with KISS
#define RAND_MAX_KISS ((unsigned long) 4294967295) //  Needs ISO C90

#define randNbMax 50000 // When using a list of previously generated random numbers

#define ERROR(a) {printf("\nERROR: %s\n", a);exit(-1);}

struct SS
{
	int D;							// Dimension of the search space (D-rectangle)
	double max[DMax];		// Maximum value on each dimension 
	double min[DMax]; 	// Minimum value on each dimension
};

struct Matrix{
	int col;
	int row;
	double m[DMax][DMax];	
};
typedef struct Matrix Mat;

struct position
{
	double f;				// Fitness value 
	int size;				// Number of dimensions  D
	double x[DMax];			// Coordinates
};


struct PSOparam
{
	double u;          //=Maxx/Maxv
	
	int S;				// group numbers
	double c1;
	double c2;	
	double wini;
	double wend;
	int rePSO;
	struct position iniX;
};
struct DEparam
{
	double F;
	double CR;
	double lamda;
	int S;	
	enum VariationMethod{DErand1,DErand2,DEbest1,DEbest2,
	DErand2best,DEcurrent2best,DEcurrent2rand};
	enum VariationMethod vm;
	enum ParamControl{Linear,Original};
	enum ParamControl paramcontrol;
	enum SelectionMethod{Greedy,Method23,Method29};
	enum SelectionMethod sm;
	//rand1 and best2 are best methods of all
	
};
struct QNparam{
	double eps;
};
struct problem
{
	int Maxiteration;
	double epsilon; 					// Admissible error
	int evalMax; 							// Maximum number of fitness evaluations
	int function; 						// Function code
	double objective; 				// Objective value
	struct SS SS;							// Search space
};



struct vector
{
	int size;
	double v[DMax];
};

struct swarm
{
	int S;								// Swarm size
	struct position X[S_max];	// Positions 
	int g_id;
	double g_bestf;
};

struct result
{
	int nEval; 		// Number of evaluations  
	struct swarm SW;	// Final swarm
	double error;		// Numerical result of the run
};



// In alea.c
double alea(double a, double b);
int alea_q(int q[], int n);
void aleaIndex(int index[], int S,int length);
int alea_integer(int a, int b);
double alea_binom(double p, int n);
double alea_normal(double mean, double stdev);
struct vector alea_sphere(int D, double radius, int option, double mean, double sigma);
double alea_stable(double alpha, double beta, double nu, double delta);

// For the pseudo-random number generator KISS
ulong	rand_kiss();
void	seed_rand_kiss(ulong seed);
// In matop.c
Mat* initMat(int row,int col);
Mat* initEMat(int row,int col);
double norm(Mat* g2);
void matmul(Mat* A,Mat* B,Mat* C);
void matadd(Mat* A,Mat* B,Mat* C);
void matsub(Mat* A,Mat* B,Mat* C);
void mattf(Mat* A,Mat* B);
void nummul(Mat* A,double a,Mat* B);
void matcp(Mat* A,Mat* B);
void PrintMat(Mat* A);
// In perf.c
double perf(struct position x, int function, struct SS SS, double objective);

// In problemDef.c
struct problem problemDef(int functionCode);

// In PSO.c	
struct result PSO(struct PSOparam param, struct problem pb);
// In DE.c
struct result DE (struct DEparam param, struct problem pb); 
// In QN.c
struct result QN(struct QNparam param, struct problem pb);
double nEval;
long double	E;  // exp(1). Useful for some test functions
double errMax, errMin;
long double	pi; // Useful for some test functions
void PrintPos(struct position pos){
	int d;
	printf("D=%d\n",pos.size);
	for(d=0;d<pos.size;d++){
		printf("%lf ",pos.x[d]);
	}
	printf("\n");
}
void PrintSW(struct	swarm SW){
	int s;int d;
	for ( s = 0; s < SW.S; s++){
		for( d = 0; d < SW.X[s].size; d++){
			printf("%lf ",SW.X[s].x[d]);
		}
		printf("\n");
	}
	printf("bestf=%lf id=%d\n\n",SW.g_bestf,SW.g_id);
}
#include "matop.c"
#include "perf.c"
#include "problemDef.c"
#include "pso.c"
#include "alea.c"
#include "DE.c"
#include "QN.c"


