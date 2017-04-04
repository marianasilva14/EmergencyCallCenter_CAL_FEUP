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
//#include <iterator>
#include <algorithm>
#include "edgetype.h"
#include "graphviewer.h"
#include "Graph.h"
#include <vector>
#include <utility>
#include <unistd.h>

class Way{
public:
	//void printVertex(int source, int destiny, Graph<int> graf, GraphViewer *gv, string color);
	void printPath(int source, int destiny, Graph<int> graf, GraphViewer *gv, string color);
	vector<unsigned int> selectHospital( Graph<int> graf, GraphViewer *gv);
	bool hospitalAlreadyExist(vector<unsigned int> hospitals,unsigned int transport);
	unsigned int  chooseNearestDestiny(int source, Graph<int> graf, GraphViewer *gv, vector<unsigned int> destinies);
	vector<unsigned int> selectVertexIcon(Graph<int> graf, GraphViewer *gv, string image, int nr_images,vector<unsigned int> hospitals);
	void inactiveTransport(GraphViewer *gv,vector<unsigned int>& destinies,int destiny_choosed,unsigned int hospital,vector<unsigned int> hospitals);
};
#endif /* WAY_H_ */
