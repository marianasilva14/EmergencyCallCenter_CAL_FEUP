/*
 * EmergencyEvent.h
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

/**
 * Enumerates that define emergencies priority
 */
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
	/**
	 * Constructor of class EmergencyEvent
	 */
	EmergencyEvent();
	/**
	 * Destructor of class EmergencyEvent
	 */
	virtual ~EmergencyEvent();
	/**
	 * Draw the emergency symbol at the node of the emergency local
	 * @param gv GraphViewer
	 * @param local emergency local
	 */
	void printPictureEmergency(GraphViewer *gv,int local);
	/**
	 * Sort emergencies according to the priority
	 * @param priority_vector priority emergencies vector
	 */
	vector<pair<int,unsigned int>> sortPriorityVector(vector<pair<int,unsigned int>> priority_vector);
	/**
	 * Find the color of the path
	 * @param priority emergency priority
	 */
	string colorEmergencyPriority(int priority);
	/**
	 * Calculate the connectivity of the graph
	 * @param graf Graph
	 * @param gv GraphViewer
	 */
	vector<int> connectity(Graph<int> graf,GraphViewer *gv);
	/**
	 * Calculate the average connectivity
	 * @param graf Graph
	 * @param gv GraphViewer
	 */
	float averageConnectivity(Graph<int> graf,GraphViewer *gv);

};

#endif /* EMERGENCYEVENT_H_ */
