#ifndef __NOXIMROUTING_XY_MODIFIED_H__
#define __NOXIMROUTING_XY_MODIFIED_H__

#include "RoutingAlgorithm.h"
#include "RoutingAlgorithms.h"
#include "../Router.h"

using namespace std;

class Routing_XY_Modified : RoutingAlgorithm {
	public:
		vector<int> route(Router * router,  RouteData & routeData);

		static Routing_XY_Modified * getInstance();

	private:
		Routing_XY_Modified(){};
		~Routing_XY_Modified(){};

		static Routing_XY_Modified * routing_XY_Modified;
		static RoutingAlgorithmsRegister routingAlgorithmsRegister;
};

#endif