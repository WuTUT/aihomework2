double perf (struct position x, int function, struct SS SS, double objective) 
{
	  
	double c;
	int d;
	int k;
	int n;
	double f, p, xd;	
	double sum1,sum2;
	double u;
	struct position xs;
	double tt;
	double beta;
	xs=x; 
	
	#include "cec2005data.c"
	
	
	
	switch (function)
	{
	case 1: // Parabola (Sphere) CEC 2005
		
		f=-450;
		for (d = 0; d < xs.size; d++) 
	  {
		xd =xs.x[d]-offset_0[d];
			f = f + xd * xd;  
		}
		break;
			
		case 2:  // Rosenbrock 
				// Solution point on offset_2 => fitness value = 390
				for (d = 0; d < xs.size; d++) 
		{
			xs.x[d]=xs.x[d]-offset_2[d]+1;
		}

		f=390;
	
 		for (d = 1; d < xs.size; d++)
	  {     	      	      
			tt=xs.x[d-1]-1;
			f =f+tt*tt;
			
			tt=xs.x[d-1]*xs.x[d-1]-xs.x[d];     
			f =f+ 100 * tt*tt;	   
		}

//f=log(1+f);
		break;
		
		case 3: // Rastrigin 
		for (d = 0; d < xs.size; d++) 
		{
			xs.x[d]=xs.x[d]-offset_3[d];
		}
		f=-330;
	  k = 10;  
	
		for (d = 0; d < xs.size; d++)    
	  {     
			xd = xs.x[d];	      
			f =f+ xd * xd - k * cos (2 * pi * xd);	    
		}	  
		f =f+ xs.size * k;  
		break;	

		case 4: // Schwefel (F2)
		for (d = 0; d < xs.size; d++) 
		{
			xs.x[d]=xs.x[d]-offset_4[d];
		}

    f = -450;
    for (d=0; d<xs.size; d++)
    {
        sum2 = 0.0;
        for (k=0; k<=d; k++)
        {
            sum2 += xs.x[k];
        }
        f += sum2*sum2;
    }
		break;


		case 5: // Griewank. WARNING: in the CEC 2005 benchmark it is rotated
	   sum1 = 0.0;
	   sum2 = 1.0;
		 f=-180;
	   for (d=0; d<xs.size; d++)
		 {
		    xd=xs.x[d]-offset_5[d];
				sum1 += xd*xd;
        sum2 *= cos(xd/sqrt(1.0+d));
 		 }
    f =f+ 1.0 + sum1/4000.0 - sum2;
		break;

		case 6: // Ackley 
		
		f=-140;

	    sum1 = 0.0;
	    sum2 = 0.0;
	    for (d=0; d<xs.size; d++)
	    {
	        xd = xs.x[d]-offset_6[d];
					sum1 += xd*xd;
	        sum2 += cos(2.0*pi*xd);
	    }
	    sum1 = -0.2*sqrt(sum1/xs.size);
	    sum2 /= xs.size;
	    f = f+ 20.0 + E - 20.0*exp(sum1) - exp(sum2);
			break;
			
			
		case 7: // Sine-sine function
			f=0;
			for (d=0;d<x.size;d++)
		{
			xd = xs.x[d];
			f=f-sin(xd)*pow(sin((d+1)*xd*xd/pi),20);
	
		}
		break;
		
		
		case 8: // Penalized
		f=pow(sin(pi*xs.x[0]),2);
		for (d=1;d<x.size-1;d++)
		{
			f=f+pow(xs.x[d],2)*(1+pow(sin(3*pi*xs.x[d+1]) ,2));
		}
		f=0.1*(f+pow(xs.x[x.size-2],2)*(1+pow(sin(2*pi*xs.x[x.size-1]),2)));
		
		for (d=0;d<x.size;d++)
		{
			xd=xs.x[d];
			if(xd>5) {u=100*pow(xd-5,4); f=f+u;}
			if(xd<-5) {u=100*pow(-xd-5,4); f=f+u;}
		}
		
		break;
			
	}
	
	f=f-objective;  

// Warning. These meaningful only for runs on a single problem
//if(f<errMin) errMin=f; // For information
//if(f>errMax) {if(f<infinity) errMax=f; else errMax=infinity;} // For information

return f;
}



