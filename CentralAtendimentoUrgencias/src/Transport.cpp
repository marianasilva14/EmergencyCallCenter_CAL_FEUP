/*
 * Transport.cpp
 *
 *  Created on: 01/04/2017
 *      Author: Sissi
 */

#include "Transport.h"

Transport::Transport() {
	// TODO Auto-generated constructor stub

}

Transport::~Transport() {
	// TODO Auto-generated destructor stub
}

vector<unsigned int> Transport::positionsTransport(Graph<int> graf, GraphViewer *gv,vector<unsigned int> hospitals){

	vector<unsigned int> transports;

	Way way;
	vector<unsigned int> ambulances,motorcycles,cars;

	ambulances=way.selectVertexIcon(graf,gv, "ambulance.png", 2,hospitals);
	motorcycles=way.selectVertexIcon(graf,gv, "motorcycle.png", 2,hospitals);
	cars=way.selectVertexIcon(graf,gv, "car.png", 2,hospitals);


	for(int i=0; i < ambulances.size();i++){
		transports.push_back(ambulances[i]);
	}
	for(int i=0; i < motorcycles.size();i++){
		transports.push_back(motorcycles[i]);
	}
	for(int i=0; i < cars.size();i++){
		transports.push_back(cars[i]);
	}


	return transports;

}





