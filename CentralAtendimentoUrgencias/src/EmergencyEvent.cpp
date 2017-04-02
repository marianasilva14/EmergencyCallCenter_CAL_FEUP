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
