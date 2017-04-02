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

vector<pair<Transport::transport,int>> Transport::positionsTransport(Graph<int> graf, GraphViewer *gv){

	vector<pair<transport,int>> transports;


	Way way;
	vector<int> ambulances,motorcycles,cars;

	ambulances=way.selectVertexIcon(graf,gv, "ambulance.png", 2);
	motorcycles=way.selectVertexIcon(graf,gv, "motorcycle.png", 2);
	cars=way.selectVertexIcon(graf,gv, "car.png", 2);

	for(int i=0; i < ambulances.size();i++){
		transports.push_back(std::make_pair(AMBULANCE,ambulances[i]));
	}

	for(int i=0; i < motorcycles.size();i++){
		transports.push_back(std::make_pair(MOTORCYCLE,ambulances[i]));
	}

	for(int i=0; i < ambulances.size();i++){
		transports.push_back(std::make_pair(CAR,ambulances[i]));
	}

	return transports;
}

string Transport::associateImageTransport(Transport::transport t){


	switch(t){
	case AMBULANCE:
		return "ambulance.png";
		break;
	case MOTORCYCLE:
		return "motorcycle.png";
		break;
	case CAR:
		return "car.png";
		break;
	default:
		return NULL;

	}

	return NULL;
}


