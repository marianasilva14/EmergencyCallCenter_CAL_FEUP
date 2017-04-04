/*
 * Way.h
 *
 *  Created on: 31/03/2017
 *      Author: Sissi
 */

#ifndef WAY_H_
#define WAY_H_

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
#include <algorithm>
#include "edgetype.h"
#include "graphviewer.h"
#include "Graph.h"
#include <vector>
#include <utility>
#include <unistd.h>

class Way{
public:
	/**
	 * Receives the origin and the destination and paints the shortest path between them
	 * @param source source
	 * @param destiny destination
	 * @param graf Graph
	 * @param gv GraphViewer
	 * @param color path color
	 */
	void printPath(int source, int destiny, Graph<int> graf, GraphViewer *gv, string color);
	/**
	 * Selects five hospitals randomly
	 * @param graf Graph
	 * @param gv GraphViewer
	 * @return vector of generated hospitals positions
	 */
	vector<unsigned int> selectHospital( Graph<int> graf, GraphViewer *gv);
	/**
	 * Check if the transport position is in one of the hospitals positions
	 * @param hospitals hospitals positions
	 * @param transport transport
	 * @return true if the transport position is in one of the hospitals positions
	 */
	bool hospitalAlreadyExist(vector<unsigned int> hospitals,unsigned int transport);
	/**
	 * Generates two random positions for each transport and places them in the graph.
	 * Save these positions in a vector
	 * @param graf Graph
	 * @param gv GraphViewer
	 * @param hospitals hospitals positions
	 * @return vector of generated transports positions
	 */
	vector<unsigned int> positionsTransport(Graph<int> graf, GraphViewer *gv,vector<unsigned int> hospitals);
	/**
	 * Choose the nearest hospital or transport of emergency's local
	 * @param source emergency local
	 * @param graf Graph
	 * @param gv GraphViewer
	 * @param destinies transports or hospitals vector
	 * @return nearest hospital or transport
	 */
	unsigned int  chooseNearestDestiny(int source, Graph<int> graf, GraphViewer *gv, vector<unsigned int> destinies);
	/**
	 * Generates random positions that aren't hospitals positions
	 * @param graf Graph
	 * @param gv GraphViewer
	 * @param image image path or color
	 * @param nr_images number of random positions
	 * @param hospitals hospitals positions
	 * @return vector of generated positions
	 */
	vector<unsigned int> rafflePositions(Graph<int> graf, GraphViewer *gv, string image, int nr_images,vector<unsigned int> hospitals);
	/**
	 * Makes transport inactive
	 * @param gv GraphViewer
	 * @param transports transports positions
	 * @param hospital hospital
	 * @param hospitals hospitals positions
	 */
	void inactiveTransport(GraphViewer *gv,vector<unsigned int>& transports,int destiny_choosed,unsigned int hospital,vector<unsigned int> hospitals);
};
#endif /* WAY_H_ */
