struct result PSO (struct PSOparam param, struct problem pb) 
{  
	int s,d;
	struct result R;
	double c1=param.c1;
	double c2=param.c2;
	double u = param.u;
	R.SW.S=param.S;
	double wini=param.wini;
	double wend=param.wend;
	double vMax[pb.SS.D];
	double vMin[pb.SS.D];
	double xMax[pb.SS.D];
	double xMin[pb.SS.D];
	double w=wini;
	R.SW.g_bestf= infinity;
	R.SW.g_id=-1;
	double error= infinity; 
	int Maxiteration=pb.Maxiteration;	
	struct position P[S_max]; // Memory (good known positions)
	struct position V[S_max];
	
	 
	for (s = 0; s < R.SW.S; s++)   
	{
		V[s].size=pb.SS.D;
		R.SW.X[s].size = pb.SS.D;
		P[s].size = pb.SS.D;
		for (d = 0; d < pb.SS.D; d++)  
		{  
			if(param.rePSO==0){
				xMin[d]=pb.SS.min[d];
		 		xMax[d]=pb.SS.max[d];	
			}
			else{
				xMin[d]=param.iniX.x[d]-0.1*(pb.SS.max[d]-pb.SS.min[d]);
		 		xMax[d]=param.iniX.x[d]+0.1*(pb.SS.max[d]-pb.SS.min[d]);
			}
		 	vMax[d]=xMax[d]/u;
		 	vMin[d]=xMin[d]/u;
		 	
		 	R.SW.X[s].x[d] = alea (xMin[d],xMax[d]);	
		 	
			
			V[s].x[d] = alea (vMin[d],vMax[d]);		
		}
	}
	
	
	for (s = 0; s < R.SW.S; s++) 
	{	
		R.SW.X[s].f =
			perf (R.SW.X[s], pb.function,pb.SS,pb.objective);
		//printf("%lf\n",pb.objective);
		//printf("%lf \n",R.SW.X[s].f);
		//PrintPos(R.SW.X[s]);
		P[s].f=R.SW.X[s].f;
		for(d = 0; d < pb.SS.D; d++){
			P[s].x[d]=R.SW.X[s].x[d];
		}
		if(R.SW.g_bestf>P[s].f){
			R.SW.g_bestf=P[s].f;
			R.SW.g_id=s;
			
		}
	}
//	printf("\n\n");
//	PrintSW(R.SW);
	
	//Start iterations
	int stop=0;
	int iter=0;
	while(stop==0){
		iter++;
		for (s = 0; s < R.SW.S; s++){
			double rand1,rand2;
			
			for(d = 0; d < pb.SS.D; d++){
				rand1=1+alea(-0.5,0.5);
				rand2=1+alea(-0.5,0.5);
				//rand1=alea(0.0,1.0);
				//rand2=alea(0.0,1.0);
				V[s].x[d]=w*V[s].x[d]+(c1*rand1*(P[s].x[d]-R.SW.X[s].x[d])+c2*rand2*(P[R.SW.g_id].x[d]-R.SW.X[s].x[d]));
				if(V[s].x[d]>vMax[d]){
					V[s].x[d]=vMax[d];
				}
				if(V[s].x[d]<vMin[d]){
					V[s].x[d]=vMin[d];
				}
				//PrintPos(R.SW.V[s]);
				R.SW.X[s].x[d]+=V[s].x[d];
				if(R.SW.X[s].x[d]>xMax[d]){
					R.SW.X[s].x[d]=xMax[d];
				}
				if(R.SW.X[s].x[d]<xMin[d]){
					R.SW.X[s].x[d]=xMin[d];
				}
				//PrintPos(R.SW.X[s]);
			}
			
		
			R.SW.X[s].f = perf (R.SW.X[s], pb.function,pb.SS,pb.objective);
			if(R.SW.X[s].f<P[s].f){
				P[s].f=R.SW.X[s].f;
				for(d = 0; d < pb.SS.D; d++){
					P[s].x[d]=R.SW.X[s].x[d];
				}
				if(R.SW.X[s].f<R.SW.g_bestf){
					R.SW.g_id=s;
					R.SW.g_bestf=R.SW.X[s].f;
				}
			}
		
			//print p_bestf
		//	printf("p_bestf[%d]=%lf\n",s,R.SW.P[s].f);
			
		}

	
		//print g_bestf
		printf("g_bestf=%lf\n",R.SW.g_bestf);
		error=fabs(R.SW.g_bestf);
		
		
		if(error<pb.epsilon){
			printf("error is less than eps\n");
			break;
		}
		
		if(iter>Maxiteration){
			printf("Max iterations\n");
			break;
		}
			w=wend+(wini-wend)*(Maxiteration-iter)/Maxiteration;
		
	}
	R.error=R.SW.g_bestf;
	R.nEval=iter;
	for(d = 0; d < pb.SS.D; d++){
		R.SW.X[R.SW.g_id].x[d]=P[R.SW.g_id].x[d];
	}
	PrintPos(P[R.SW.g_id]);
	printf("g_bestf=%.12lf\n",R.SW.g_bestf);
	printf("iter=%d",iter);
	return R;
}
