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

vector<int> Transport::positionsTransport(Graph<int> graf, GraphViewer *gv,vector<int> hospitals){

	vector<int> transports;

	Way way;
	vector<int> ambulances,motorcycles,cars;

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


int Transport::chooseClosestTransport(int source, Graph<int> graf, GraphViewer *gv, vector<int> transports){

	graf.dijkstraShortestPath(source);

	vector<Vertex<int>*> path;
	double dist=1000000;
	int destiny;

	path= graf.getVertexSet();

	for(int i=0; i < path.size();i++){
		for(int j=0; j < transports.size();j++){
			if(path[i]->getDist() < dist && path[i]->getInfo() == transports[j]){
				dist=path[i]->getDist();
				destiny =transports[j];
			}
		}
	}
	return destiny;

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
