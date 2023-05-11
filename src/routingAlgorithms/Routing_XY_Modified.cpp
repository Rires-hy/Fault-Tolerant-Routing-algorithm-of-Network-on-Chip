#include "Routing_XY_Modified.h"
#include <iostream>
#include <ctime>
RoutingAlgorithmsRegister Routing_XY_Modified::routingAlgorithmsRegister("XY_Modified", getInstance());

Routing_XY_Modified * Routing_XY_Modified::routing_XY_Modified = 0;

Routing_XY_Modified * Routing_XY_Modified::getInstance() {
	if ( routing_XY_Modified == 0 )
		routing_XY_Modified = new Routing_XY_Modified();
    
	return routing_XY_Modified;
}

vector<int> Routing_XY_Modified::route(Router * router,  RouteData & routeData)
{
  //  printf("state: %d  ", *(routeData.state));
    Coord current = id2Coord(routeData.current_id);
    Coord destination = id2Coord(routeData.dst_id);
    vector <int> directions;
    int CHOSEN_DIRECTION=0;

    //kean
    bool X_notend_notbroken_east = (destination.x > current.x) && 
    						!(router->broken_direction[DIRECTION_EAST]);
    bool X_notend_notbroken_west = (destination.x < current.x) && 
    						!(router->broken_direction[DIRECTION_WEST]);
    bool Y_notend_notbroken_north = (destination.y < current.y) && 
    						!(router->broken_direction[DIRECTION_NORTH]);   						   
    bool Y_notend_notbroken_south = (destination.y > current.y) && 
    						!(router->broken_direction[DIRECTION_SOUTH]);

    bool X_equal_notbroken = (destination.x==current.x) && (
 !(router->broken_direction[DIRECTION_EAST])|| !(router->broken_direction[DIRECTION_WEST]));

    bool Y_equal_notbroken =  (destination.y==current.y) && (
 !(router->broken_direction[DIRECTION_NORTH])|| !(router->broken_direction[DIRECTION_SOUTH]));
    
    bool X_notend_broken_east = (destination.x > current.x) && 
    						(router->broken_direction[DIRECTION_EAST]);
    bool X_notend_broken_west = (destination.x < current.x) && 
    						(router->broken_direction[DIRECTION_WEST]);
    bool Y_notend_broken_north = (destination.y < current.y) && 
    						(router->broken_direction[DIRECTION_NORTH]);   						   
    bool Y_notend_broken_south = (destination.y > current.y) && 
    						(router->broken_direction[DIRECTION_SOUTH]);

    bool X_equal_broken =  (destination.x==current.x) && (
 (router->broken_direction[DIRECTION_EAST])&&(router->broken_direc\
tion[DIRECTION_WEST]));

    bool Y_equal_broken =  (destination.y==current.y) && (
 (router->broken_direction[DIRECTION_NORTH])&&(router->broken_direc\
tion[DIRECTION_SOUTH]));
    //we use negative first routing algorithm as the basic, only allowed when neg = 1
    bool neg = !((destination.x > current.x) && (destination.y > current.y));
    std::srand(std::time(nullptr));
    int rand_num = std::rand() % 2;
  	bool X_arrive = (destination.x == current.x);
  	bool Y_arrive = (destination.y == current.y);
  	///!!!!!!!!!!!!!!!!!!!!!
  	int laststep=routeData.dir_in;
	printf("state = %d  ",routeData.state);
	cout<<",laststep = "<<laststep<<"  ";
	//cout<<"lastdir = "<<routeData.dir_in<<"  ";

	/*	if(routeData.state!= goX||routeData.state!= goY||
	   routeData.state!= backtraceX||routeData.state!= arrive||
	   routeData.state!= backtraceY){
	  routeData.state= goX;
	  printf("errorstate\n");
	    }
	*/			    
    if (routeData.state == goX)
    {
      printf("gx ");
    	if (X_notend_notbroken_east)
    	{
    		directions.push_back(DIRECTION_EAST);
            CHOSEN_DIRECTION=DIRECTION_EAST;
            routeData.state = goX;
    	}else if (X_notend_notbroken_west)
    	{
    		directions.push_back(DIRECTION_WEST);
            CHOSEN_DIRECTION=DIRECTION_WEST;
            routeData.state = goX;
    	}else if (X_notend_broken_east||X_notend_broken_west)
    	{
    		if (Y_notend_broken_south||Y_notend_broken_north||
		    Y_equal_broken)
    		{
    			if (X_notend_broken_east)
			    {
			    	directions.push_back(DIRECTION_WEST);
			        CHOSEN_DIRECTION=DIRECTION_WEST;
			    }else if (X_notend_broken_west)
			    {
			    	directions.push_back(DIRECTION_EAST);
			        CHOSEN_DIRECTION=DIRECTION_EAST;
			    }
    			routeData.state = backtraceX;
    		}else if (Y_notend_notbroken_south)
    		{
		  //change from south to north
    			directions.push_back(DIRECTION_SOUTH);
            	CHOSEN_DIRECTION=DIRECTION_SOUTH;
    			routeData.state = backtraceY;
    		}else if (Y_notend_notbroken_north)
    		{
    			directions.push_back(DIRECTION_NORTH);
            	CHOSEN_DIRECTION=DIRECTION_NORTH;
    			routeData.state = backtraceY;
    		}else if(Y_equal_notbroken){
		  if((!router->broken_direction[DIRECTION_NORTH])){
		     directions.push_back(DIRECTION_NORTH);
            	CHOSEN_DIRECTION=DIRECTION_NORTH;
    			routeData.state = backtraceY;
		  }else {
    			directions.push_back(DIRECTION_SOUTH);
            	CHOSEN_DIRECTION=DIRECTION_SOUTH;
    			routeData.state = backtraceY;
		  }
		}
		else
            {
    			printf("error in goX!!\n");
    		}
    	}else if (X_arrive)
    	{
    		if (Y_arrive)
    		{
    			printf("arrive\n");
    			routeData.state = arrive;
    		} else {
	    		if (Y_notend_notbroken_south)
	    		{
			  //change from south to north
	    			directions.push_back(DIRECTION_SOUTH);
	            	CHOSEN_DIRECTION=DIRECTION_SOUTH;
	    			routeData.state = goY;
	    		}else if (Y_notend_notbroken_north)
	    		{
			  cout<<Y_notend_notbroken_north<<"  ";
	    			directions.push_back(DIRECTION_NORTH);
	            	CHOSEN_DIRECTION=DIRECTION_NORTH;
	    			routeData.state = goY;
	    		}else if (Y_notend_broken_south||Y_notend_broken_north)
	    		{
	    			if (router->broken_direction[DIRECTION_EAST])
			    	{
			    		directions.push_back(DIRECTION_WEST);
			            CHOSEN_DIRECTION=DIRECTION_WEST;
			    	}else if (router->broken_direction[DIRECTION_WEST])
			    	{
			    		directions.push_back(DIRECTION_EAST);
			            CHOSEN_DIRECTION=DIRECTION_EAST;
			    	}else{
			    		//should be random
			    		directions.push_back(DIRECTION_WEST);
			            CHOSEN_DIRECTION=DIRECTION_WEST;
			    	}
	    			routeData.state = backtraceX;
	    		}
			cout<<CHOSEN_DIRECTION<<"  ";
    		}
    	}
    }else if (routeData.state == backtraceX)
    {
      printf("bX ");
		if (Y_notend_notbroken_south)
		{
			directions.push_back(DIRECTION_SOUTH);
        	CHOSEN_DIRECTION=DIRECTION_SOUTH;
			routeData.state = backtraceY;
		}else if (Y_notend_notbroken_north)
		{
			directions.push_back(DIRECTION_NORTH);
        	CHOSEN_DIRECTION=DIRECTION_NORTH;
			routeData.state = backtraceY;
		}else if(Y_equal_notbroken){
		  if((!router->broken_direction[DIRECTION_SOUTH])){
                     directions.push_back(DIRECTION_SOUTH);
                CHOSEN_DIRECTION=DIRECTION_SOUTH;
                        routeData.state = backtraceY;
                  }else {
                        directions.push_back(DIRECTION_NORTH);
                CHOSEN_DIRECTION=DIRECTION_NORTH;
                        routeData.state = backtraceY;
                  }
		}
		else{
			if (router->broken_direction[DIRECTION_EAST])
			{
				directions.push_back(DIRECTION_WEST);
        		CHOSEN_DIRECTION=DIRECTION_WEST;
			} else if (router->broken_direction[DIRECTION_WEST]) 
			{
				directions.push_back(DIRECTION_EAST);
        		CHOSEN_DIRECTION=DIRECTION_EAST;	
			}else{
			  //cout<<"laststep = "<<laststep;
			  if(laststep == DIRECTION_WEST) {
			      directions.push_back(DIRECTION_EAST);
                              CHOSEN_DIRECTION=DIRECTION_EAST;
			      cout<<"a";
			  }else if( laststep == DIRECTION_EAST){
				directions.push_back(DIRECTION_WEST);
				CHOSEN_DIRECTION=DIRECTION_WEST;				cout<<"b";
			  }else if(X_notend_notbroken_east)
			    {
			                                      directions.push_back(DIRECTION_EAST);
                        CHOSEN_DIRECTION=DIRECTION_EAST;
			cout<<"c";
			    }else if(X_notend_notbroken_west){
			                                    directions.push_back(DIRECTION_WEST);
                        CHOSEN_DIRECTION=DIRECTION_WEST;
			cout<<"d";
			  }else {
			                                                               directions.push_back(DIRECTION_EAST);
                        CHOSEN_DIRECTION=DIRECTION_EAST;
			cout<<"f";
			  }
			 }
			routeData.state = backtraceX;
		}
    }else if (routeData.state == goY)
    {
      printf("goY ");
    	if ((destination.x == current.x)&&(destination.y == current.y))
    	{
    		printf("arrive\n");
    		routeData.state = arrive;
    	}else if(destination.y == current.y){
	      	if (X_notend_notbroken_east){
    		directions.push_back(DIRECTION_EAST);
		CHOSEN_DIRECTION=DIRECTION_EAST;
		routeData.state = goX;
		}else if (X_notend_notbroken_west){
    		directions.push_back(DIRECTION_WEST);
		CHOSEN_DIRECTION=DIRECTION_WEST;
		routeData.state = goX;
		}else if(!router->broken_direction[DIRECTION_SOUTH]){
    			directions.push_back(DIRECTION_SOUTH);
            	CHOSEN_DIRECTION=DIRECTION_SOUTH;
    			routeData.state = backtraceY;		  
		}else{
		 directions.push_back(DIRECTION_NORTH);
                CHOSEN_DIRECTION=DIRECTION_NORTH;
                 routeData.state = backtraceY;
		}
	}else {
     		if (Y_notend_notbroken_south)
    		{
    			directions.push_back(DIRECTION_SOUTH);
            	CHOSEN_DIRECTION=DIRECTION_SOUTH;
		//printf("1  ");
    			routeData.state = goY;
    		}else if (Y_notend_notbroken_north)
    		{
		  //printf("2  ");
		  //change from north to south
    			directions.push_back(DIRECTION_NORTH);
            	CHOSEN_DIRECTION=DIRECTION_NORTH;
    			routeData.state = goY;
    		}else if (X_notend_notbroken_west)
    		{
     			directions.push_back(DIRECTION_WEST);
            	CHOSEN_DIRECTION=DIRECTION_WEST; 
            	routeData.state = backtraceX;  			
    		}else if (X_notend_notbroken_east)
    		{
    			directions.push_back(DIRECTION_EAST);
            	CHOSEN_DIRECTION=DIRECTION_EAST;   
            	routeData.state = backtraceX;
		}else if(X_equal_notbroken){
                  if((!router->broken_direction[DIRECTION_EAST])){
                     directions.push_back(DIRECTION_EAST);
                CHOSEN_DIRECTION=DIRECTION_EAST;
                        routeData.state = backtraceX;
                  }else {
                        directions.push_back(DIRECTION_WEST);
                CHOSEN_DIRECTION=DIRECTION_WEST;
                        routeData.state = backtraceX;
                  }		  
		}else {
            	if (Y_notend_broken_south)
			    {
			    	directions.push_back(DIRECTION_NORTH);
			        CHOSEN_DIRECTION=DIRECTION_NORTH;
			    }else if (Y_notend_broken_north)
			    {
			    	directions.push_back(DIRECTION_SOUTH);
			        CHOSEN_DIRECTION=DIRECTION_SOUTH;
			    }
            	routeData.state = backtraceY;
            }

    	}
    } else if (routeData.state == backtraceY)
    {
		if (X_notend_notbroken_east)
		{
			directions.push_back(DIRECTION_EAST);
        	CHOSEN_DIRECTION=DIRECTION_EAST;
			routeData.state = goX;
		}else if (X_notend_notbroken_west)
		{
			directions.push_back(DIRECTION_WEST);
        	CHOSEN_DIRECTION=DIRECTION_WEST;
			routeData.state = goX;
		}else if(X_equal_notbroken){
                  if((!router->broken_direction[DIRECTION_EAST])){
                     directions.push_back(DIRECTION_EAST);
                CHOSEN_DIRECTION=DIRECTION_EAST;
                        routeData.state = backtraceX;
                  }else {
                        directions.push_back(DIRECTION_WEST);
                CHOSEN_DIRECTION=DIRECTION_WEST;
                        routeData.state = backtraceX;
                  }
		}else{
			if (router->broken_direction[DIRECTION_SOUTH])
			{
				directions.push_back(DIRECTION_NORTH);
        		CHOSEN_DIRECTION=DIRECTION_NORTH;
			} else if (router->broken_direction[DIRECTION_NORTH]) 
			{
				directions.push_back(DIRECTION_SOUTH);
        		CHOSEN_DIRECTION=DIRECTION_SOUTH;	
			}else{
			  if(laststep == DIRECTION_SOUTH) 
			    {
			    cout<<"laststep=  "<<laststep<<"  ";
				directions.push_back(DIRECTION_NORTH);
				CHOSEN_DIRECTION=DIRECTION_NORTH;
			   }else if(laststep == DIRECTION_NORTH){
			         cout<<"laststep=  "<<laststep<<"  ";
                                directions.push_back(DIRECTION_SOUTH);
                                CHOSEN_DIRECTION=DIRECTION_SOUTH;
			  }
			  else if(Y_notend_notbroken_south){
			    directions.push_back(DIRECTION_SOUTH);
			    CHOSEN_DIRECTION=DIRECTION_SOUTH;
			  }else if (Y_notend_notbroken_north){
			    directions.push_back(DIRECTION_NORTH);
			    CHOSEN_DIRECTION=DIRECTION_NORTH;
			  }else if(Y_equal_notbroken){
			    directions.push_back(DIRECTION_SOUTH);
			    CHOSEN_DIRECTION=DIRECTION_SOUTH;
			  }			  
			}
			routeData.state = backtraceY;
		}
    }else if (routeData.state == arrive)
    {
    	printf("arrive\n");
    }else if(routeData.state == vibration_w){
       directions.push_back(laststep);
       CHOSEN_DIRECTION=laststep;
       routeData.state = goX;
    }else if(routeData.state == vibration_s){
       directions.push_back(laststep);
       CHOSEN_DIRECTION=laststep;
       routeData.state = goY;
    }else if(routeData.state == livelockw_s1){
      if(!(router->broken_direction[DIRECTION_WEST])){
	directions.push_back(DIRECTION_WEST);
	CHOSEN_DIRECTION=DIRECTION_WEST;
	routeData.state = livelockw_s2;
      }else{
	cout << " ? ";
	directions.push_back(DIRECTION_SOUTH);
	CHOSEN_DIRECTION=DIRECTION_SOUTH;
	routeData.state = backtraceY;
      }
    }else if(routeData.state == livelockw_s2){
      directions.push_back(DIRECTION_NORTH);
      CHOSEN_DIRECTION=DIRECTION_NORTH;
      routeData.state = livelockw_s3;
    }else if(routeData.state == livelockw_s3){
      directions.push_back(DIRECTION_EAST);
      CHOSEN_DIRECTION=DIRECTION_EAST;
      routeData.state = goX;
    }else if(routeData.state == uturnxs_s1){
      directions.push_back(DIRECTION_EAST);
      CHOSEN_DIRECTION=DIRECTION_EAST;
      routeData.state = uturnxs_s2;
    }else if(routeData.state == uturnxn_s1){
      directions.push_back(DIRECTION_EAST);
      CHOSEN_DIRECTION=DIRECTION_EAST;
      routeData.state = uturnxn_s2;
    }else if(routeData.state == uturnxs_s2){
      directions.push_back(DIRECTION_NORTH);
      CHOSEN_DIRECTION=DIRECTION_NORTH;
      routeData.state = uturnxs_s3;
    }else if(routeData.state == uturnxn_s2){
      //vibraion since negative first
      if(!(router->broken_direction[DIRECTION_NORTH])){
	directions.push_back(DIRECTION_NORTH);
        CHOSEN_DIRECTION=DIRECTION_NORTH;
        routeData.state = uturnxn_s3;
      }else if(!(router->broken_direction[DIRECTION_EAST])){
        directions.push_back(DIRECTION_EAST);
        CHOSEN_DIRECTION=DIRECTION_EAST;
        routeData.state = uturnxn_s3;
      }else{
	cout<<"error Uturnxn!! ";
      }
    }else if(routeData.state == uturnxs_s3){
      if( !(router->broken_direction[DIRECTION_NORTH])){
	directions.push_back(DIRECTION_NORTH);
	CHOSEN_DIRECTION=DIRECTION_NORTH;
	routeData.state = goY;
      }else if(!(router->broken_direction[DIRECTION_EAST])){
	directions.push_back(DIRECTION_EAST);
	CHOSEN_DIRECTION=DIRECTION_EAST;
	routeData.state = backtraceX;
      } else {
	cout << "error UturnXs!!  ";
      }
    }else if(routeData.state == uturnxn_s3){
      directions.push_back(laststep);
      CHOSEN_DIRECTION=laststep;
      routeData.state = uturnxn_s4;
    }else if(routeData.state == uturnxn_s4){
      directions.push_back(DIRECTION_SOUTH);
      CHOSEN_DIRECTION=DIRECTION_SOUTH;
      routeData.state = uturnxn_s5;
    }else if(routeData.state == uturnxn_s5){
      if( !(router->broken_direction[DIRECTION_SOUTH])){
        directions.push_back(DIRECTION_SOUTH);
        CHOSEN_DIRECTION=DIRECTION_SOUTH;
        routeData.state = goY;
      }else if(!(router->broken_direction[DIRECTION_EAST])){
        directions.push_back(DIRECTION_EAST);
        CHOSEN_DIRECTION=DIRECTION_EAST;
        routeData.state = backtraceX;
      } else {
        cout << "error UturnXn5!!  ";
      }  //uturny!
    }else if(routeData.state == uturnyw_s1){
      directions.push_back(DIRECTION_NORTH);
      CHOSEN_DIRECTION=DIRECTION_NORTH;
      routeData.state = uturnyw_s2;
    }else if(routeData.state == uturnye_s1){
      directions.push_back(DIRECTION_NORTH);
      CHOSEN_DIRECTION=DIRECTION_NORTH;
      routeData.state = uturnye_s2;
    }else if(routeData.state == uturnyw_s2){
      directions.push_back(DIRECTION_EAST);
      CHOSEN_DIRECTION=DIRECTION_EAST;
      routeData.state = uturnyw_s3;
    }else if(routeData.state == uturnye_s2){
      //vibraion since negative first
      if(!(router->broken_direction[DIRECTION_NORTH])){
        directions.push_back(DIRECTION_NORTH);
        CHOSEN_DIRECTION=DIRECTION_NORTH;
        routeData.state = uturnye_s3;
      }else if(!(router->broken_direction[DIRECTION_EAST])){
        directions.push_back(DIRECTION_EAST);
        CHOSEN_DIRECTION=DIRECTION_EAST;
        routeData.state = uturnye_s3;
      }else{
        cout<<"error Uturnye!! ";
      }
    }else if(routeData.state == uturnyw_s3){
      if( !(router->broken_direction[DIRECTION_NORTH])){
        directions.push_back(DIRECTION_NORTH);
        CHOSEN_DIRECTION=DIRECTION_NORTH;
        routeData.state = backtraceY;
      }else if(!(router->broken_direction[DIRECTION_EAST])){
        directions.push_back(DIRECTION_EAST);
        CHOSEN_DIRECTION=DIRECTION_EAST;
        routeData.state = goX;
      } else {
        cout << "error Uturnyw!!  ";
      }
    }else if(routeData.state == uturnye_s3){
      directions.push_back(laststep);
      CHOSEN_DIRECTION=laststep;
      routeData.state = uturnye_s4;
    }else if(routeData.state == uturnye_s4){
      directions.push_back(DIRECTION_WEST);
      CHOSEN_DIRECTION=DIRECTION_WEST;
      routeData.state = uturnye_s5;
    }else if(routeData.state == uturnye_s5){
      if( !(router->broken_direction[DIRECTION_NORTH])){
        directions.push_back(DIRECTION_NORTH);
        CHOSEN_DIRECTION=DIRECTION_NORTH;
        routeData.state = backtraceY;
      }else if(!(router->broken_direction[DIRECTION_WEST])){
        directions.push_back(DIRECTION_WEST);
        CHOSEN_DIRECTION=DIRECTION_WEST;
        routeData.state = goX;
      } else {
        cout << "error Uturnye5!!  ";
      }  
    }
    else{
      printf("error in arrive state!!\n");
    }


    /*    //live lock
    if(routeData.state==backtraceX&&laststep!=DIRECTION_EAST&&laststep!=DIRECTION_WEST&&
       !(router->broken_direction[DIRECTION_EAST])&&!(router->broken_direction[DIRECTION_WEST])){
      directions.pop_back();
      if(rand_num==0) {
	directions.push_back(DIRECTION_WEST);
	 CHOSEN_DIRECTION=DIRECTION_WEST;
      }else{
	directions.push_back(DIRECTION_EAST);
	CHOSEN_DIRECTION=DIRECTION_EAST;
      }
      cout << "rand = "<<rand_num<<"  ";
    }

     if(routeData.state==backtraceY&&laststep!=DIRECTION_NORTH&&laststep!=DIRECTION_SOUTH&&
        !(router->broken_direction[DIRECTION_NORTH])&&!(router->broken_direction[DIRECTION_SOUTH])){
       directions.pop_back();
       if(rand_num==0) {
         directions.push_back(DIRECTION_NORTH);
         CHOSEN_DIRECTION=DIRECTION_NORTH;
       }else{
         directions.push_back(DIRECTION_SOUTH);
         CHOSEN_DIRECTION=DIRECTION_SOUTH;
       }
        cout << "rand = "<<rand_num<<"  ";
     }   
    */
    
    //negative first
    if(laststep==DIRECTION_SOUTH&&CHOSEN_DIRECTION==DIRECTION_WEST){
      if(!(router->broken_direction[DIRECTION_EAST])){
	directions.pop_back();
	directions.push_back(DIRECTION_EAST);
	CHOSEN_DIRECTION=DIRECTION_EAST;
	routeData.state = vibration_w;
      }else if(!(router->broken_direction[DIRECTION_NORTH])){
	directions.pop_back();
        directions.push_back(DIRECTION_NORTH);
        CHOSEN_DIRECTION=DIRECTION_NORTH;
        routeData.state = vibration_w;
      }else{
	directions.pop_back();
        directions.push_back(DIRECTION_SOUTH);
        CHOSEN_DIRECTION=DIRECTION_SOUTH;
        routeData.state = livelockw_s1;
      }
    }

     if(laststep==DIRECTION_WEST&&CHOSEN_DIRECTION==DIRECTION_SOUTH){
      if(!(router->broken_direction[DIRECTION_NORTH])){
        directions.pop_back();
        directions.push_back(DIRECTION_NORTH);
        CHOSEN_DIRECTION=DIRECTION_NORTH;
        routeData.state = vibration_s;
      }else if(!(router->broken_direction[DIRECTION_EAST])){
        directions.pop_back();
        directions.push_back(DIRECTION_EAST);
        CHOSEN_DIRECTION=DIRECTION_EAST;
        routeData.state = vibration_s;
      }else{
        directions.pop_back();
        directions.push_back(DIRECTION_WEST);
        CHOSEN_DIRECTION=DIRECTION_WEST;
        routeData.state = backtraceX;
      }
    }


     	//no U-turn for X
     if(laststep==DIRECTION_EAST&&CHOSEN_DIRECTION==DIRECTION_EAST){
       if(!(router->broken_direction[DIRECTION_NORTH])){
	 directions.pop_back();
	 directions.push_back(DIRECTION_NORTH);
	 CHOSEN_DIRECTION=DIRECTION_NORTH;
	 routeData.state = uturnxn_s1;
       }else if(!(router->broken_direction[DIRECTION_SOUTH])){
	 directions.pop_back();
	 directions.push_back(DIRECTION_SOUTH);
	 CHOSEN_DIRECTION=DIRECTION_SOUTH;
	 routeData.state = uturnxs_s1;
       }else{
	 cout<<"error,uturnx?? ";
	 directions.pop_back();
	 directions.push_back(DIRECTION_WEST);
	 CHOSEN_DIRECTION=DIRECTION_WEST;
	 routeData.state = backtraceY;
       }
     }

	//no U-turn for Y
     if(laststep==DIRECTION_NORTH&&CHOSEN_DIRECTION==DIRECTION_NORTH){
       if(!(router->broken_direction[DIRECTION_WEST])){
	 directions.pop_back();
	 directions.push_back(DIRECTION_WEST);
	 CHOSEN_DIRECTION=DIRECTION_WEST;
	 routeData.state = uturnyw_s1;
       }else if(!(router->broken_direction[DIRECTION_EAST])){
	 directions.pop_back();
	 directions.push_back(DIRECTION_EAST);
	 CHOSEN_DIRECTION=DIRECTION_EAST;
	 routeData.state = uturnye_s1;
       }else{
	 cout<<"error,uturny?? ";
	 directions.pop_back();
	 directions.push_back(DIRECTION_SOUTH);
	 CHOSEN_DIRECTION=DIRECTION_SOUTH;
	 routeData.state = backtraceX;
       }
    }

    //test
        printf("dest= %d %d , current = %d  %d,   state= %d  ,broken_ewsn = %d  %d  %d  %d ", destination.x, destination.y,
        current.x, current.y, routeData.state,
        router->broken_direction[DIRECTION_EAST],
        router->broken_direction[DIRECTION_WEST],
        router->broken_direction[DIRECTION_SOUTH],
	       router->broken_direction[DIRECTION_NORTH]);

	for(int i = 0; i < directions.size(); i++){
	  cout << directions[i]<< "  ";
	}
	cout << endl;
	
    if (directions.size()==0){
        // random
        for(int i=0;i<DIRECTIONS;i++){
            if (!(router->broken_direction[i])){
                CHOSEN_DIRECTION=i;
                directions.push_back(CHOSEN_DIRECTION);
            }
        }
    }
    //printf("state: %d  ", routeData.state);
    return directions;
}
