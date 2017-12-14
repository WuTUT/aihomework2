struct result DE (struct DEparam param, struct problem pb) 
{  
	int s,d;
	int jrand;
	struct result R;
	double F=param.F;
	double CR=param.CR;
	double lamda=param.lamda;
	enum VariationMethod vm=param.vm;
	enum ParamControl paramcontrol=param.paramcontrol;
	enum SelectionMethod sm=param.sm;
	R.SW.S=param.S;
	int Maxiteration=pb.Maxiteration;
	struct position U[S_max]; 
	struct position V[S_max];
	int index[R.SW.S];
	R.SW.g_bestf= infinity;
	R.SW.g_id=-1;	
	double xMax,xMin;
	int errorflag=0;
	double error= infinity; 
	
	for (s = 0; s < R.SW.S; s++)   
	{
		
		R.SW.X[s].size = pb.SS.D;
		V[s].size = pb.SS.D;
		U[s].size = pb.SS.D;
		for (d = 0; d < pb.SS.D; d++)  
		{  
			xMin=pb.SS.min[d];
		 	xMax=pb.SS.max[d];
			R.SW.X[s].x[d] = alea (xMin,xMax);		
		}
	}

	for (s = 0; s < R.SW.S; s++) 
	{	
		R.SW.X[s].f =
			perf (R.SW.X[s], pb.function,pb.SS,pb.objective);
		//printf("%lf\n",pb.objective);
	//	printf("%lf \n",R.SW.X[s].f);
		//PrintPos(R.SW.X[s]);
		if(R.SW.g_bestf>R.SW.X[s].f){
			R.SW.g_bestf=R.SW.X[s].f;
			R.SW.g_id=s;
		}
				
	}

	int stop=0;
	int iter=0;
	while(stop==0){
		iter++;
	for (s = 0; s < R.SW.S; s++){
		switch(vm){
			case DErand1:{
				//printf("GO");
				aleaIndex(index,R.SW.S,3);
				for(d = 0; d < pb.SS.D; d++)
					//V[s].x[d]=R.SW.X[index[0]].x[d]+(F*(alea(0,1)+1))*(R.SW.X[index[1]].x[d]-R.SW.X[index[2]].x[d]);
					V[s].x[d]=R.SW.X[index[0]].x[d]+F*(R.SW.X[index[1]].x[d]-R.SW.X[index[2]].x[d]);				
				break;				
			}
			case DEbest2:{
				aleaIndex(index,R.SW.S,4);
				for(d = 0; d < pb.SS.D; d++)
					V[s].x[d]=R.SW.X[R.SW.g_id].x[d]+F*(R.SW.X[index[0]].x[d]+R.SW.X[index[1]].x[d]-R.SW.X[index[2]].x[d]-R.SW.X[index[3]].x[d]);
				break;
			}
			case DEcurrent2best:{
				aleaIndex(index,R.SW.S,2);
				for(d = 0; d < pb.SS.D; d++)
					V[s].x[d]=R.SW.X[s].x[d]+lamda*(R.SW.X[R.SW.g_id].x[d]-R.SW.X[s].x[d])+F*(R.SW.X[index[0]].x[d]-R.SW.X[index[1]].x[d]);				
				break;
			}
		}
		
		switch(paramcontrol){
			case Original:{
				jrand=alea_integer(0,pb.SS.D-1);
				for (d = 0; d < pb.SS.D; d++){
				//if(alea(0,1)<CR || d==jrand) 
				if(alea(0,1)<CR*(alea(0,1)+1) || d==jrand) 
					U[s].x[d]=V[s].x[d];
				else 
					U[s].x[d]=R.SW.X[s].x[d];
				}
				break;
			}
			case Linear:{
				//To Do
				break;
			}
		}
		switch(sm){
			case Greedy:{
				U[s].f=perf(U[s],pb.function, pb.SS,pb.objective);
				
				if(U[s].f<R.SW.X[s].f){
					for(d = 0; d < pb.SS.D; d++){
						R.SW.X[s].x[d]=U[s].x[d];
						
					}
					R.SW.X[s].f=U[s].f;
					if(U[s].f<R.SW.g_bestf){
						
							
						R.SW.g_bestf=U[s].f;
						R.SW.g_id=s;
					}
				}
				break;
			}
		}	
			
	}	
	
	

//	printf("g_bestf=%lf\n",R.SW.g_bestf);
		error=R.SW.g_bestf;
		if(error<0)
		error=-error;
		
		if(error<pb.epsilon&&errorflag==0){
			//printf("error is less than eps\n");
		R.nEval=iter;
		errorflag=1;
		//	break;
		}
		
		if(iter>Maxiteration){
		//	printf("Max iterations\n");
			break;
		}
	}
	R.error=R.SW.g_bestf;
	
//	PrintPos(R.SW.X[R.SW.g_id]);
//	printf("g_bestf=%.9lf\n",R.SW.g_bestf);
	if(errorflag==0)
	R.nEval=iter-1;
//	printf("iter=%d\n",R.nEval);
	return R;
}

