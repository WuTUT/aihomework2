struct result QN(struct QNparam param, struct problem pb){
	struct result R;
	double error= infinity; 
	R.SW.g_bestf= infinity;
	R.SW.g_id=-1;
	double eps=param.eps;
	eps=eps*eps;
	Mat* B = initEMat(pb.SS.D,pb.SS.D); //n*n
	Mat* dB = initMat(pb.SS.D,pb.SS.D); //n*n
	Mat* g = initMat(pb.SS.D,1);		//n*1
	Mat* g2 = initMat(pb.SS.D,1);		//n*1
	Mat* x = initMat(pb.SS.D,1);		//n*1
	Mat* x2 = initMat(pb.SS.D,1);		//n*1
	Mat* s = initMat(pb.SS.D,1);		//n*1
	Mat* y = initMat(pb.SS.D,1);		//n*1
	Mat* d = initMat(pb.SS.D,1);		//n*1
	Mat* yt = initMat(1,pb.SS.D);  		//1*n
	Mat* st = initMat(1,pb.SS.D);  		//1*n
	double lamda=-0.01;

	
	int id;
	for(id=0;id<pb.SS.D;id++){
		R.SW.X[0].x[id]=x->m[id][0];
	}
	R.SW.X[0].size=pb.SS.D;
	Mat* tmp1=initMat(pb.SS.D,pb.SS.D);//sk*sk.T
	Mat* tmp2=initMat(1,1);			//sk.T*y 
	Mat* tmp3=initMat(pb.SS.D,1);//Bk*yk n*1
	Mat* tmp4=initMat(pb.SS.D,pb.SS.D);//tmp3*yk.T n*n
	Mat* tmp5=initMat(pb.SS.D,pb.SS.D);//tmp4*Bk n*n
	Mat* tmp6=initMat(1,1);//sk.T*tmp3 1*1
	
	double f5=0.0;
	double h=0.00001;
	struct position tmpx;
	tmpx.size=pb.SS.D;
	int dd;
	{
		
		for(id=0;id<pb.SS.D;id++){
			f5=0.0;
			for(dd=0;dd<pb.SS.D;dd++)
			tmpx.x[dd]=x->m[dd][0];
			
			tmpx.x[id]=x->m[id][0]+h;
			f5+=8.0*perf (tmpx, pb.function,pb.SS,pb.objective);
			
			tmpx.x[id]=x->m[id][0]+h;
			f5-=perf (tmpx, pb.function,pb.SS,pb.objective);
			tmpx.x[id]=x->m[id][0]-3*h;
			f5-=8.0*perf (tmpx, pb.function,pb.SS,pb.objective);
			tmpx.x[id]=x->m[id][0]-h;
			f5+=perf (tmpx, pb.function,pb.SS,pb.objective);
			f5=f5/12.0/h;			
			g->m[id][0]=f5;
		}
		
	}
	
	int stop=0;
	int iter=0;
	while(stop==0){
		
		matmul(B,g,d);
		
		nummul(d,lamda,s);
		matadd(x,s,x2);
		{
			double f2=0.0;
			double f1=0.0;
			for(dd=0;dd<pb.SS.D;dd++)
			tmpx.x[dd]=x->m[dd][0];
			f1=perf (tmpx, pb.function,pb.SS,pb.objective);
			for(dd=0;dd<pb.SS.D;dd++)
			tmpx.x[dd]=x2->m[dd][0];
			f2=perf (tmpx, pb.function,pb.SS,pb.objective);
		}
		
		{
		
		for(id=0;id<pb.SS.D;id++){
			f5=0.0;
			for(dd=0;dd<pb.SS.D;dd++)
			tmpx.x[dd]=x2->m[dd][0];
			
			tmpx.x[id]=x2->m[id][0]+h;
			f5+=8.0*perf (tmpx, pb.function,pb.SS,pb.objective);
			tmpx.x[id]=x2->m[id][0]+h;
			f5-=perf (tmpx, pb.function,pb.SS,pb.objective);
			tmpx.x[id]=x2->m[id][0]-3*h;
			f5-=8.0*perf (tmpx, pb.function,pb.SS,pb.objective);
			tmpx.x[id]=x2->m[id][0]-h;
			f5+=perf (tmpx, pb.function,pb.SS,pb.objective);
			f5=f5/12.0/h;			
			g2->m[id][0]=f5;
			}
		
		}
		
		if(norm(g2)<eps)
		break;
		
		matsub(g2,g,y);
		mattf(y,yt);
		mattf(s,st);
		matmul(s,st,tmp1);
			
		matmul(st,y,tmp2);
		matmul(B,y,tmp3);
		matmul(tmp3,yt,tmp4);
		matmul(tmp4,B,tmp5);
		matmul(yt,tmp3,tmp6);
		if(fabs(tmp2->m[0][0])<zero){
			printf("divide error!\n");
			
			int stp;
			scanf("%d",&stp);
		}
		nummul(tmp1,1.0/tmp2->m[0][0],tmp1);
		nummul(tmp5,1.0/tmp6->m[0][0],tmp5);
		matsub(tmp1,tmp5,dB);
		matadd(B,dB,B);
		//for(id=0;id<pb.SS.D;id++){
		//	printf("%lf ",x->m[id][0]);
		//}
		//printf("\n");
		iter++;
		if(iter>10000){
			printf("Max iterations\n");
			break;
		}
		matcp(x2,x);
		matcp(g2,g);
		
	}
	for(id=0;id<pb.SS.D;id++){
		R.SW.X[0].x[id]=x->m[id][0];
	}
	for(dd=0;dd<pb.SS.D;dd++)
	tmpx.x[dd]=x->m[dd][0];
	R.SW.g_bestf=perf (tmpx, pb.function,pb.SS,pb.objective);
	PrintPos(R.SW.X[0]);
	printf("iter=%d\n",iter);
	printf("%.10lf",R.SW.g_bestf );
	return R;
}



