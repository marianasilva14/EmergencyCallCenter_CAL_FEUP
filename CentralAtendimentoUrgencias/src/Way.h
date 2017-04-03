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
	vector<int> selectHospital( Graph<int> graf, GraphViewer *gv);
	bool hospitalAlreadyExist(vector<int> hospitals, int transport);
	int  chooseClosestHospital(int source, Graph<int> graf, GraphViewer *gv, vector<int> hospitals);
	vector<int> selectVertexIcon(Graph<int> graf, GraphViewer *gv, string image, int nr_images,vector<int> hospitals);

};
#endif /* WAY_H_ */
