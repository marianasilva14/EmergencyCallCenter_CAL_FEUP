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
	Emergency::emergency emergency_type;
	Transport::transport transport_type;
public:
	EmergencyEvent();
	EmergencyEvent(Emergency::emergency e, Transport::transport t);
	virtual ~EmergencyEvent();
	int raflleEmergency(Graph<int> graf, GraphViewer *gv);
	vector<pair<int,unsigned int>> sortPriorityVector(vector<pair<int,unsigned int>> priority_vector);

};












#endif /* EMERGENCYEVENT_H_ */
