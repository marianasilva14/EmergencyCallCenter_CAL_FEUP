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
#include <map>
#include "Graph.h"
#include "graphviewer.h"
#include "Way.h"
#include "matcher.h"

#define RESULTS_APROX 10

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
	/**
	 * Start the emergencies
	 * @param graf Graph
	 * @param gv GraphViewer
	 * @param hospitals hospitals positions
	 * @param transport_positions transport positions
	 * @param emergencies pair with the priority and local of the emergency
	 */
	void startEmergencies(Graph<int> graf,GraphViewer *gv,vector<unsigned int> hospitals, vector<unsigned int> transports_positions, vector<pair<int,unsigned int>> emergencies);

	/**
	 * Discovers the left node of the street to put the emergency
	 * @param graf Graph
	 * @param edgeId road
	 * @return left node id
	 */
	int findLeftNode(Graph<int> graf, int edgeID);

	/**
	 * Discovers if there is any transport or hospital in the left node of the street
	 * @param graf Graph
	 * @param edgeId road
	 * @param hospitals hospitals positions
	 * @param transports_positions transports positions
	 * @return true if there is a transport or hospital in the left node of the street
	 */
	boolean checkExistenceOfAppeal(Graph<int> graf, int edgeID,vector<unsigned int> hospitals,vector<unsigned int> transports_positions);

	/**
	 * Presents the first RESULTS_APROX streets sorted by the shortest distance calculated by the algorithm edit distance.
	 * @param edges_chosen roads chosen by algorithm
	 * @param edges map that includes all the streets of the map associating the edge id and the name of the street
	 * @param aux map that associates the edge id and its distance calculated by the algorithm edit distance
	 */
	void sortEdgesByDistance(vector<int> &edges_chosen, map<int, string> edges, map<int,int> aux);

	/**
	 * Searches the street through the algorithm kmp.
	 * If this algorithm doesn't find any street, the function searches the street through the approximate algorithm.
	 * @param graf Graph
	 * @param gv GraphViewer
	 * @param road road that the user want to search
	 * @param priotity emergency priority
	 * @param edges map that includes all the streets of the map associating the edge id and the name of the street
	 * @param call pair that saves the priority and location of the emergency
	 * @param hospitals hospitals positions
	 * @param transports_positions transports positions
	 * @return vector with the edges id's chosen
	 */
	vector<int> researchRoadExact(Graph<int> graf, GraphViewer *gv, string road, int priority, map<int,string> edges,pair<int,unsigned int> &call,vector<unsigned int> hospitals,vector<unsigned int> transports_positions);

	/**
	 * Searches the street through the algorithm edit distance.
	 * @param graf Graph
	 * @param gv GraphViewer
	 * @param road road that the user want to search
	 * @param priotity emergency priority
	 * @param edges map that includes all the streets of the map associating the edge id and the name of the street
	 * @return map that associates the edge id and its distance calculated by the algorithm edit distance
	 */
	map<int,int>  researchRoadApproximate(Graph<int> graf, GraphViewer *gv, string road, int priority, map<int,string> edges);

	/**
	 * Asks the user to choose the street that belongs to those that the algorithm edit distance found
	 * After choosing the street, search for it again using the kmp algorithm
	 * @param graf Graph
	 * @param gv GraphViewer
	 * @param edges map that includes all the streets of the map associating the edge id and the name of the street
	 * @param edges_chosen roads chosen by algorithm
	 * @param priotity emergency priority
	 * @param call pair that saves the priority and location of the emergency
	 * @param hospitals hospitals positions
	 * @param transports_positions transports positions
	 */
	void choseRoad(Graph<int> graf, GraphViewer *gv,map<int,string>  edges,vector<int> edges_chosen, int &priority,pair<int,unsigned int> &call,vector<unsigned int> hospitals,vector<unsigned int> transports_positions);

	/**
	 * Calculate the Kmp algorithm time
     * @param edges map that includes all the streets of the map associating the edge id and the name of the street
	 */
	void calculateKmpTime(map<int,string> edges);

	/**
	 * Calculate the edit distance algorithm time
	 * @param edges map that includes all the streets of the map associating the edge id and the name of the street
	 */
	void calculateEditDistanceTime(map<int,string> edges);

	/**
	 * Calculate the naive algorithm time
	 * @param edges map that includes all the streets of the map associating the edge id and the name of the street
	 */
	void calculateNaiveTime(map<int,string> edges);
};

#endif /* EMERGENCYEVENT_H_ */
