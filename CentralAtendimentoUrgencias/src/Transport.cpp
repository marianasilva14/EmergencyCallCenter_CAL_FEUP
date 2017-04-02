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

	for(unsigned int i=0; i < ambulances.size();i++){
		transports.push_back(std::make_pair(AMBULANCE,ambulances[i]));
	}

	for(unsigned int i=0; i < motorcycles.size();i++){
		transports.push_back(std::make_pair(MOTORCYCLE,motorcycles[i]));
	}

	for(unsigned int i=0; i < cars.size();i++){
		transports.push_back(std::make_pair(CAR,cars[i]));
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

pair<Transport::transport,int> Transport::chooseTransportShortestWay(int source, Graph<int> graf, GraphViewer *gv, vector<pair<Transport::transport,int>> transports){

	Transport t;
	pair<Transport::transport,int> destiny_choosed;
	graf.dijkstraShortestPath(source);

	vector<Vertex<int>*> path;
	double dist=1000000;
	int destiny;
	string transport_type;
	Transport::transport transport;

	path= graf.getVertexSet();

	for(int i=0; i < path.size();i++){
		for(int j=0; j < transports.size();j++){
			if(path[i]->getDist() < dist && path[i]->getInfo() == transports[j].second){
				dist=path[i]->getDist();
				destiny =transports[j].second;
				transport=transports[j].first;

			}
		}
	}

	destiny_choosed.first=transport;
	destiny_choosed.second=destiny;

	return destiny_choosed;

}

/*
void  Transport::printEmergencyPath(int priority, int source, int hospital, Graph<int> graf, GraphViewer *gv, Transport::transport transport){
	Way way;


	if(priority==1)
		way.printPath(source,hospital, graf,gv,RED);
	else if(priority==2)
		way.printPath(source, hospital, graf,gv,YELLOW);
	else
		way.printPath(source, hospital, graf,gv,GREEN);
}

*/
