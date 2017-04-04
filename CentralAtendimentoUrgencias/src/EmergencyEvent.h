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


class Emergency{
public:
	typedef enum {
		HIGH,
		MEDIUM,
		LOW
	}emergency;
};

class EmergencyEvent {

public:
	EmergencyEvent();
	virtual ~EmergencyEvent();
	void printPictureEmergency(GraphViewer *gv,int local);
	vector<pair<int,unsigned int>> sortPriorityVector(vector<pair<int,unsigned int>> priority_vector);
	bool verifyIfPositionOfEmergencyIsValid(vector<int> hospitals, vector<int> transports, int position_emergency);
	string colorEmergencyPriority(int priority);
	vector<int> connectity(Graph<int> graf,GraphViewer *gv);
	float averageConnectivity(Graph<int> graf,GraphViewer *gv);

};












#endif /* EMERGENCYEVENT_H_ */
