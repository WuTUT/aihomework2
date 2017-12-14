struct problem problemDef(int functionCode){
	int d;
	struct problem pb;
	pb.function=functionCode;	
	pb.epsilon = 0.00000;	// Acceptable error (default). May be modified below
	pb.objective = 0;       // Objective value (default). May be modified below
	switch (pb.function)
	{   
	
	case 1:
 			pb.SS.D =30;
			for (d = 0; d < pb.SS.D; d++)
			{   
				pb.SS.min[d] = -100; 
				pb.SS.max[d] = 100;	
				
  
			}
			pb.evalMax = pb.SS.D*10000;
			pb.epsilon = 0.00000001;	//Acceptable error
			pb.objective =-450;       // Objective value
			break;
						
	 case 2:		// Rosenbrock. CEC 2005 F6
		pb.SS.D = 30;	// 10
				
					// Boundaries
		for (d = 0; d < pb.SS.D; d++)
		{	
			pb.SS.min[d] = -100;
		 	pb.SS.max[d] = 100; 			
			
      
		}
			
		pb.evalMax = pb.SS.D*10000;
		pb.epsilon = 0.00000001; ///220793652865;	//0.01 Acceptable error
		pb.objective =390; 

		break;
		
     case 3:		// CEC 2005 F9, Rastrigin
		pb.SS.D = 30;	 
		for (d = 0; d < pb.SS.D; d++)
		{
			pb.SS.min[d] =-5.12; 
			pb.SS.max[d] =5.12; 	  
			

		 }
		pb.epsilon =0.01; // 0.01;	// Acceptable error
		pb.objective =-330;       // Objective value
		pb.evalMax=pb.SS.D*10000;

		break;
		
     case 4:// CEC 2005 F2  Schwefel
		pb.SS.D = 30;	 
		for (d = 0; d < pb.SS.D; d++)
		{
			pb.SS.min[d] =-100; 
			pb.SS.max[d] =100; 	  
			
		 }
		pb.epsilon =0.00000001;	// Acceptable error
		pb.objective =-450;       // Objective value
		pb.evalMax=pb.SS.D*10000;
		
		pb.epsilon=0.000001	; pb.evalMax=100000;	


		break;
				
		
     case 5:// CEC 2005 F7  Griewank (NON rotated)
		pb.SS.D = 30;	 
		for (d = 0; d < pb.SS.D; d++)
		{
			pb.SS.min[d] =-600; 
			pb.SS.max[d] =600; 	  
				

		 }
		pb.epsilon = 0.00000001;	//Acceptable error
		pb.objective =-180;       // Objective value
		pb.evalMax=pb.SS.D*10000;

		break;
				
				
     case 6:// CEC 2005 F8 Ackley (NON rotated)
				pb.SS.D =30;	
		for (d = 0; d < pb.SS.D; d++)
		{
			pb.SS.min[d] =-32; 
			pb.SS.max[d] =32; 	  
				
		 }
		pb.epsilon = 0.00000001;	// Acceptable error
		pb.objective =-140;       // Objective value
		pb.evalMax= pb.SS.D*10000;

		break;
	
	 case 7: // Sine sine function
			pb.SS.D=10;
		pb.objective=-10;// Arbitrary large negative number
		// Remember that the error is abs(f - objective), though
		// Best known (2010-09: -9.5983769). 
		pb.epsilon = 0.00000001;
		for (d = 0; d < pb.SS.D; d++)
		{
			pb.SS.min[d] = 0;
			pb.SS.max[d] = pi;
				
		}
		pb.evalMax = 60000;

		break;
		case 8:		// Penalized
			pb.SS.D = 30; //30;	

		// Boundaries
		for (d = 0; d < pb.SS.D; d++) 
		{	
			pb.SS.min[d] = -50; 
			pb.SS.max[d] = 50;
			
		}

		pb.evalMax = 50000; 
		pb.epsilon = 0.00000001;
		pb.objective=0;

		break;
	
	}
//	printf("pbdef %lf\n\n",pb.objective);
	return pb;
}

