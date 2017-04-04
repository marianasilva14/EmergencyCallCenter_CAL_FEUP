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
#include "Way.h"

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
	 * @return priority vector sorted
	 */
	vector<pair<int,unsigned int>> sortPriorityVector(vector<pair<int,unsigned int>> priority_vector);
	/**
	 * Find the color of the path
	 * @param priority emergency priority
	 * @return color of the path
	 */
	string colorEmergencyPriority(int priority);
	/**
	 * Calculate the connectivity of the graph
	 * @param graf Graph
	 * @param gv GraphViewer
	 * @return vector with the nodes that aren't connected
	 */
	vector<int> connectity(Graph<int> graf,GraphViewer *gv);
	/**
	 * Calculate the average connectivity
	 * @param graf Graph
	 * @param gv GraphViewer
	 * @return average
	 */
	float averageConnectivity(Graph<int> graf,GraphViewer *gv);
	void startEmergencies(Graph<int> graf,GraphViewer *gv,vector<unsigned int> hospitals, vector<unsigned int> transports_positions, vector<pair<int,unsigned int>> emergencies);

};

#endif /* EMERGENCYEVENT_H_ */
