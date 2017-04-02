/*
 * EmergencyEvent.cpp
 *
 *  Created on: 01/04/2017
 *
 */

#include "EmergencyEvent.h"

EmergencyEvent::EmergencyEvent() {
}

EmergencyEvent::~EmergencyEvent() {
}

EmergencyEvent::EmergencyEvent(Emergency::emergency e, Transport::transport t){
	this->emergency_type=e;
	this->transport_type=t;
}

int EmergencyEvent::raflleEmergency(Graph<int> graf, GraphViewer *gv){
	vector<Vertex<int>*> vet = graf.getVertexSet();
	int random_vertex;

	random_vertex= rand() % vet.size();
	gv->setVertexIcon(vet[random_vertex]->getInfo(),"emergency.png");

	return random_vertex;
}

vector<pair<int,unsigned int>> EmergencyEvent::sortPriorityVector(vector<pair<int,unsigned int>> priority_vector){

	vector<pair<int,unsigned int>> sortPriority;

	for(int j=1; j < 4; j++){
	for(unsigned int i=0; i < priority_vector.size();i++){
		if(priority_vector[i].first == j)
			sortPriority.push_back(priority_vector[i]);
	}
	}

	return sortPriority;
}
