/*
 * EmergencyEvent.h
 *
 *  Created on: 01/04/2017
 *      Author: Sissi
 */

#ifndef EMERGENCYEVENT_H_
#define EMERGENCYEVENT_H_

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <conio.h>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <iomanip>
#include "Graph.h"
#include "graphviewer.h"
#include "Transport.h"


class Emergency{
public:
	typedef enum {
		HIGH,
		MEDIUM,
		LOW
	}emergency;
};

class EmergencyEvent {
private:
	vector<int> transports_positions;
	vector<int> hospitals;
public:
	EmergencyEvent();
	EmergencyEvent(	vector<int> transports_positions,vector<int> hospitals);
	virtual ~EmergencyEvent();
	vector<int> getTransports();
	vector<int> getHospitals();
	void setTransports(vector<int> transports);
	void setHospitals(vector<int> hospitals);
	void printPictureEmergency(GraphViewer *gv,int local);
	vector<pair<int,unsigned int>> sortPriorityVector(vector<pair<int,unsigned int>> priority_vector);
	bool verifyIfPositionOfEmergencyIsValid(vector<int> hospitals, vector<int> transports, int position_emergency);
	string colorEmergencyPriority(int priority);
	void conectity(GraphViewer *gv, Graph<int> graf);

};












#endif /* EMERGENCYEVENT_H_ */
