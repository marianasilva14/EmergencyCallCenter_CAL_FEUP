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
#include <pair>
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
	vector<pair<Transport::transport,int>> positionsTransport(Graph<int> graf, GraphViewer *gv);
	string associateImageTransport(Transport::transport);
};

#endif /* TRANSPORT_H_ */
