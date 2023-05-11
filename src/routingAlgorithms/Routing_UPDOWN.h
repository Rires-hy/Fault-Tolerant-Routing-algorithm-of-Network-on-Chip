#ifndef __NOXIMROUTING_UPDOWN_H__
#define __NOXIMROUTING_UPDOWN_H__

#include "RoutingAlgorithm.h"
#include "RoutingAlgorithms.h"
#include "../Router.h"

using namespace std;

class Routing_UPDOWN : RoutingAlgorithm {
	public:
		vector<int> route(Router * router, RouteData & routeData);

		static Routing_UPDOWN * getInstance();

	private:
		Routing_UPDOWN(){};
		~Routing_UPDOWN(){};

		static Routing_UPDOWN * routing_UPDOWN;
		static RoutingAlgorithmsRegister routingAlgorithmsRegister;
};

#endif