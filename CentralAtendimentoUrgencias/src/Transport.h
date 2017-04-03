/*
 * Transport.h
 *
 *  Created on: 01/04/2017
 *      Author: Sissi
 */

#ifndef TRANSPORT_H_
#define TRANSPORT_H_

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <conio.h>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <queue>
#include <iomanip>
#include <unistd.h>
#include <utility>
#include "edgetype.h"
#include "graphviewer.h"
#include "Graph.h"
#include "Way.h"


class Transport {
public:
	Transport();
	virtual ~Transport();
	enum transport {AMBULANCE,CAR,MOTORCYCLE};
	vector<int> positionsTransport(Graph<int> graf, GraphViewer *gv);
	string associateImageTransport(Transport::transport);
	int chooseClosestTransport(int source, Graph<int> graf, GraphViewer *gv, vector<int> transports);
	vector<int> transportsLocal(vector<pair<Transport::transport,int>> transports);
	void printEmergencyPath(int priority, int source, int destiny, Graph<int> graf, GraphViewer *gv, Transport::transport transport);
};

#endif /* TRANSPORT_H_ */
