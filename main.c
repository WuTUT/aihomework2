#include "main.h"

int main(){
	
	E = exp ((long double) 1);  
	pi = acos ((long double) -1); 
	int nbFunc;
	int indFunc;
	struct PSOparam psoparam;
	struct problem pb;  
/*	struct result result3; 
	
	psoparam.u=10;
	psoparam.S=15;
	psoparam.c1=1;
	psoparam.c2=1;
	psoparam.wini=0.9;
	psoparam.wend=0.4;
	psoparam.rePSO=0;
	
	pb=problemDef(6);
	pb.Maxiteration=100000;
	psoparam.iniX.size=	pb.SS.D;	
	result3 = PSO(psoparam, pb);

*/
	 FILE *fpWrite1=fopen("data.txt","w");  
    if(fpWrite1==NULL)  
    {  
        return 0;  
    }  
    
	
	
	struct DEparam deparam;
	
	struct result result1; 
	
	deparam.F=0.5;
	deparam.CR=0.5;
	deparam.S=30;
	deparam.vm=DErand1;
	deparam.paramcontrol=Original;
	deparam.sm=Greedy;
	int nFunc,iFunc;
	nFunc=8;
	time_t ts,te;
	long int ttime=0;
	int iIter=0;
	int nIter=25;
	for(iFunc=8;iFunc<=nFunc;iFunc++){
	
	pb=problemDef(iFunc);
	pb.Maxiteration=100000;
	while(pb.Maxiteration<=100000){
		
	
		
	int success=0;
	int aveEval=0;	
	double besterr=infinity;
	double worsterr=0.0;
	double meanerr=0.0;
	ttime=0;
	
	for(iIter=0;iIter<nIter;iIter++){	
	ts=time(NULL);
	result1 = DE(deparam,pb);
	te=time(NULL);
	ttime+=(te-ts);
	if(result1.error<besterr){
		besterr=result1.error;
	}
	if(result1.error>worsterr){
		worsterr=result1.error;
	}
		meanerr+=result1.error;
	if(result1.nEval<pb.Maxiteration){
		success++;
	}	
	 	aveEval+=result1.nEval;
	}
	printf("%.8lf %.8lf %.8lf %ld %d %.1f\n",besterr,worsterr,meanerr/25.0,ttime,success,aveEval*1.0/25);
	fprintf(fpWrite1,"%.8lf %.8lf %.8lf %ld %d %.1f\n",besterr,worsterr,meanerr/25.0,ttime,success,aveEval*1.0/25);  
	pb.Maxiteration=pb.Maxiteration*10;
		}	
	}
	
	
	
	
/*	struct QNparam qnparam;
	
	struct result result2; 
	pb=problemDef(4);
	qnparam.eps=0.000005;
	result2 = QN(qnparam,pb);
*/	
	fclose(fpWrite1); 
	
	return 0;
}
