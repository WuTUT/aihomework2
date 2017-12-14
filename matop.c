Mat* initMat(int row,int col){
	Mat* p=(Mat*)malloc(sizeof(struct Matrix));
	p->col=col;
	p->row=row;
	int i,j;
	for(i=0;i<row;i++){
		for(j=0;j<col;j++){
			p->m[i][j]=0.0;
		}
	}
	return p;
}

Mat* initEMat(int row,int col){
	Mat* p=(Mat*)malloc(sizeof(struct Matrix));
	p->col=col;
	p->row=row;
	int i,j;
	for(i=0;i<row;i++){
		for(j=0;j<col;j++){
			if(i==j)
			p->m[i][j]=1.0;
			else
			p->m[i][j]=0.0;
		}
	}
	
	return p;
}
	
double norm(Mat* g2){
	int i;
	double sum=0.0;
	for(i=0;i<g2->row;i++)
		sum+=g2->m[i][0]*g2->m[i][0];
	//sum=sqrt(sum); too slow and not necessary
 	return sum;	
}

void matmul(Mat* A,Mat* B,Mat* C){
	int i,j,k;
	if(A->col!=B->row){
		printf("A.col!=B.row\n");
	}
	else{
		for(i=0;i<A->row;i++){
			for(j=0;j<B->col;j++){
				C->m[i][j]=0.0;
				for(k=0;k<A->col;k++){
					C->m[i][j]+=A->m[i][k]*B->m[k][j];
				}
			}
		}	
			
	}
	
}

void matadd(Mat* A,Mat* B,Mat* C){
	
	int i,j;	
	if(A->col!=B->col||A->row!=B->row){
		printf("A.size!=B.size\n");
	}
	else{
		for(i=0;i<A->row;i++){
			for(j=0;j<B->col;j++){
				C->m[i][j]=A->m[i][j]+B->m[i][j];
			}
		}
			
	}
}

void matsub(Mat* A,Mat* B,Mat* C){
	
	int i,j;	
	if(A->col!=B->col||A->row!=B->row){
		printf("A.size!=B.size\n");
	}
	else{
		for(i=0;i<A->row;i++){
			for(j=0;j<B->col;j++){
				C->m[i][j]=A->m[i][j]-B->m[i][j];
			}
		}
			
	}
}

void mattf(Mat* A,Mat* B){
	int i,j;
	if(B->col!=A->row||B->row!=A->col){
		printf("A.T.size!=B.size\n");
	}
	else{
		for(i=0;i<A->row;i++){
			for(j=0;j<A->col;j++){
				B->m[j][i]=A->m[i][j];
			}
		}	
	}
}

void nummul(Mat* A,double a,Mat* B){
	int i,j;
	for(i=0;i<A->row;i++){
		for(j=0;j<A->col;j++){
			B->m[i][j]=A->m[i][j]*a;
		}
		
		
	}
}

void matcp(Mat* A,Mat* B){
	int i,j;
	for(i=0;i<A->row;i++){
		for(j=0;j<A->col;j++){
			B->m[i][j]=A->m[i][j];
		}
		
		
	}
}

void PrintMat(Mat* A){
	int i,j;
	for(i=0;i<A->row;i++){
		for(j=0;j<A->col;j++){
			printf("%.2lf ",A->m[i][j]);
		}
		printf("\n");
	}
}

