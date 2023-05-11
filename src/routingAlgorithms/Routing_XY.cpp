#include "Routing_XY.h"

RoutingAlgorithmsRegister Routing_XY::routingAlgorithmsRegister("XY", getInstance());

Routing_XY * Routing_XY::routing_XY = 0;

Routing_XY * Routing_XY::getInstance() {
	if ( routing_XY == 0 )
		routing_XY = new Routing_XY();
    
	return routing_XY;
}

vector<int> Routing_XY::route(Router * router, RouteData& routeData)
{
    Coord current = id2Coord(routeData.current_id);
    Coord destination = id2Coord(routeData.dst_id);
    vector <int> directions;

    // router->state=State_0;

    // switch (router->state){
    //     case State_0:
    //         if (current.x>destination.x){
    //             directions.push_back(DIRECTION_WEST);
    //         }
    //         else{
    //             directions.push_back(DIRECTION_EAST);
    //         }

    //         if  ( (   ((current.x>destination.x)&& (router->broken_direction[DIRECTION_WEST])   ) 
    //             || ((current.x<destination.x)&& (router->broken_direction[DIRECTION_EAST])  )  )
    //             &&(( (current.y>destination.y)&&(!router->broken_direction[DIRECTION_SOUTH]))
    //             ||  ((current.y<destination.y)&&(!router->broken_direction[DIRECTION_NORTH]))))
    //             {
    //                 router->state=State_3;
    //             }
    //             else if  (current.x=destination.x)&& (
    //                     (
    //                     (!router->broken_direction[DIRECTION_SOUTH]) &&
    //                      (current.y>destination.d)
    //                     )||(
    //                         (!router->broken_direction[DIRECTION_NORTH])&&(current.y<destination.y)
    //                     )
    //             )                   
    //             {
    //                 router->state=State_2;
    //             }
    //             else if (
    //                 (current.x>destination.x)&&
    //                 (!(router->broken_direction[DIRECTION_WEST]))||
    //                 (current.x>destination.x)&&
    //                 (!(router->broken_direction[DIRECTION_EAST]))                        
    //             )
    //             {
    //                 router->state=State_0;
    //             }
    //             else if (
    //                 (current.x=destination.x)&&((current.y<destination.y))
    //             )
    //             {
    //                 router->state=State_4;
    //             }
    //             else if(
    //                  (current.x!=destination.x)&&
    //                  (
    //                     (router->broken_direction[DIRECTION_WEST])&&(router->broken_direction[DIRECTION_EAST])
    //                  )&&(
    //                     (router->broken_direction[DIRECTION_NORTH])&&(router->broken_direction[DIRECTION_SOUTH])
    //                  )

    //             )
    //             {
    //                 router->state=State_1;
    //             }
    //         break;
    //     case State_1:

    //          directions.push_back(DIRECTION_WEST);       


    //         if(( (current.y>destination.y)&&(!router->broken_direction[DIRECTION_SOUTH]))
    //             ||  ((current.y<destination.y)&&(!router->broken_direction[DIRECTION_NORTH])))
    //             {
    //                 router.state=State_3;
    //             }
    //             else{
    //                 router.state=State_1;
    //             }
    //         break;
    //     case State_2:
    //         if(
    //             (current.x=destination.x)&&((current.y<destination.y))
    //         )
    //         {
    //             router->state=State_4;
    //         }
    //         else if(
    //             (current.y!=destination.y)&&
    //                  (
    //                     (router->broken_direction[DIRECTION_WEST])&&(router->broken_direction[DIRECTION_EAST])
    //                  )&&(
    //                     ((!router->broken_direction[DIRECTION_NORTH])||(!router->broken_direction[DIRECTION_SOUTH]))
    //                  )
    //         )
    //         {
    //             router->state=State_1;
    //         }
    //         else if(
    //             (current.y!=destination.y)&&
    //                  (
    //                     (router->broken_direction[DIRECTION_WEST])&&(router->broken_direction[DIRECTION_EAST])
    //                  )&&(
    //                     (router->broken_direction[DIRECTION_NORTH])&&(router->broken_direction[DIRECTION_SOUTH])
    //                  )
    //         )
    //         {
    //             router->state=State_3;
    //         }
    //         else{
    //             router.state=State_2;
    //         }
    //         break;
    //     case State_3:
    //         if(
    //             ((current.x>destination.x)&& (!router->broken_direction[DIRECTION_WEST])   )||
    //             ((current.x<destination.x)&& (!router->broken_direction[DIRECTION_EAST])   )
    //         ){
    //              router.state=State_0;
    //         }
    //         else{
    //              router.state=State_3;
    //         }
    //         break;
    //     case State_4:

    //         break;
    // } 



    // Fault-tolerant XY Routing Algorithm. (Kiyan Nan)
    if ((routeData.dir_in != DIRECTION_EAST) && destination.x > current.x && !(router->broken_direction[DIRECTION_EAST]))
       directions.push_back(DIRECTION_EAST);
    else if ((routeData.dir_in != DIRECTION_WEST) && destination.x < current.x && !(router->broken_direction[DIRECTION_WEST]))
        directions.push_back(DIRECTION_WEST);
    else if ((routeData.dir_in != DIRECTION_SOUTH) && destination.y > current.y && !(router->broken_direction[DIRECTION_SOUTH]))
        directions.push_back(DIRECTION_SOUTH);
    else if ((routeData.dir_in != DIRECTION_NORTH) && !(router->broken_direction[DIRECTION_NORTH]))
        directions.push_back(DIRECTION_NORTH);
    else {
        int CHOSEN_DIRECTION=0;
        for(int i=0;i<DIRECTIONS;i++){
            if (!(router->broken_direction[i])){
                CHOSEN_DIRECTION=i;
                break;
            }
        }
        directions.push_back(CHOSEN_DIRECTION);
    }
    return directions;
}


// vector<int> Routing_XY::route(Router * router, RouteData& routeData)
// {
//     Coord current = id2Coord(routeData.current_id);
//     Coord destination = id2Coord(routeData.dst_id);
//     vector <int> directions;

//     // Fault-tolerant XY Routing Algorithm. (Kiyan Nan)
//     if (destination.x > current.x && !(router->broken_direction[DIRECTION_EAST]))
//        directions.push_back(DIRECTION_EAST);
//     else if (destination.x < current.x && !(router->broken_direction[DIRECTION_WEST]))
//         directions.push_back(DIRECTION_WEST);
//     else if (destination.y > current.y && !(router->broken_direction[DIRECTION_SOUTH]))
//         directions.push_back(DIRECTION_SOUTH);
//     else if (!(router->broken_direction[DIRECTION_NORTH]))
//         directions.push_back(DIRECTION_NORTH);
//     else {
//         int CHOSEN_DIRECTION=0;
//         for(int i=0;i<DIRECTIONS;i++){
//             if (!(router->broken_direction[i])){
//                 CHOSEN_DIRECTION=i;
//                 break;
//             }
//         }
//         directions.push_back(CHOSEN_DIRECTION);
//     }
        
//     return directions;
//    } 

// vector<int> Routing_XY::route(Router * router, RouteData& routeData)
// {
//     Coord current = id2Coord(routeData.current_id);
//     Coord destination = id2Coord(routeData.dst_id);
//     vector <int> directions;

//     if (destination.x > current.x)
//        directions.push_back(DIRECTION_EAST);
//     else if (destination.x < current.x)
//         directions.push_back(DIRECTION_WEST);
//     else if (destination.y > current.y)
//         directions.push_back(DIRECTION_SOUTH);
//     else
//         directions.push_back(DIRECTION_NORTH);

//     return directions;
//    } 