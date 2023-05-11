#include "Routing_UPDOWN.h"

RoutingAlgorithmsRegister Routing_UPDOWN::routingAlgorithmsRegister("UPDOWN", getInstance());

Routing_UPDOWN * Routing_UPDOWN::routing_UPDOWN = 0;

Routing_UPDOWN * Routing_UPDOWN::getInstance() {
	if ( routing_UPDOWN == 0 )
		routing_UPDOWN = new Routing_UPDOWN();
    
	return routing_UPDOWN;
}

vector<int> Routing_UPDOWN::route(Router * router, RouteData & routeData)
{
    Coord current = id2Coord(routeData.current_id);
    Coord destination = id2Coord(routeData.dst_id);
    vector <int> directions;
    int nextIndex=0;
    int randomNode = routeData.current_id;
    int randomEndNode = routeData.dst_id;
    // cout << "The current is: " << current.x << " " << current.y << "The destination is: " << destination.x << " " << destination.y << endl;
    // if (routeData.flitDir!=NO_INCOMING_INDEX){
        // nextIndex=routeData.flitDir;
    // } else {
        DOWNUP dir = UP;
        int incomingIndex=0;
        if (routeData.dir_in==DIRECTION_LOCAL){
            incomingIndex = NO_INCOMING_INDEX;
        } else if(routeData.dir_in==DIRECTION_SOUTH){
            incomingIndex = randomNode+16;
        } else if(routeData.dir_in==DIRECTION_NORTH){
            incomingIndex = randomNode-16;
        } else if(routeData.dir_in==DIRECTION_EAST){
            incomingIndex = randomNode+1;
        } else if(routeData.dir_in==DIRECTION_WEST){
            incomingIndex = randomNode-1;
        }


        dir = router->globalGraph->findPath(randomNode,randomEndNode,incomingIndex);
        if (dir == UP){
            nextIndex = router->globalGraph->nodes[randomNode]->up[0]->id;
        } else {
            // router->isDown = true;
            nextIndex = router->globalGraph->tempPath.back();
            router->globalGraph->tempPath.pop_back();
        }
    // }
    if ((nextIndex-randomNode) == 1){
        directions.push_back(DIRECTION_EAST);
    } else if ((nextIndex-randomNode) == -1){
        directions.push_back(DIRECTION_WEST);
    } else if ((nextIndex-randomNode) == 16){
        directions.push_back(DIRECTION_SOUTH);
    } else if ((nextIndex-randomNode) == -16){
        directions.push_back(DIRECTION_NORTH);
    } 
    if (directions.size() == 0){
        cout << "No path found!" << endl;
    }

    // if (routeData.src_id == 32){
    //     cout << "routing algorithm 32. routed to" << directions[0] << endl;
    // }
    return directions;
}