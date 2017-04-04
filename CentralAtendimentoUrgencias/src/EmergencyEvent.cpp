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

EmergencyEvent::EmergencyEvent(	vector<int> transports_positions,vector<int> hospitals){
	this->transports_positions=transports_positions;
	this->hospitals=hospitals;
}

vector<int> EmergencyEvent::getTransports(){
	return transports_positions;
}

vector<int> EmergencyEvent::getHospitals(){
	return hospitals;
}

void  EmergencyEvent::setTransports(vector<int> transports){
	 this->transports_positions= transports;
}
void EmergencyEvent::setHospitals(vector<int> hospitals){
	this->hospitals=hospitals;
}

void EmergencyEvent::printPictureEmergency(GraphViewer *gv, int local){
	gv->setVertexIcon(local, "emergency.png");
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

bool EmergencyEvent::verifyIfPositionOfEmergencyIsValid(vector<int> hospitals, vector<int> transports,  int position_emergency){

	for(int i = 0; i < hospitals.size(); i++){
		if(hospitals[i] == position_emergency)
			return false;
	}

	for(int i = 0; i < transports.size(); i++){
		if(transports[i] == position_emergency)
			return false;
	}

	return true;

}

string EmergencyEvent::colorEmergencyPriority(int priority){
	Way way;
	string color;

	if(priority==1)
		color="RED";
	else if(priority==2)
		color="YELLOW";
	else
		color="GREEN";

	return color;
}

void EmergencyEvent::conectity(GraphViewer *gv, Graph<int> graf){

}


