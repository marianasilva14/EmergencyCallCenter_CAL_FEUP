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

class Way{
public:
	void printPath(int source, int destiny, Graph<int> graf, GraphViewer *gv, string color);
	vector<int> selectHospital( Graph<int> graf, GraphViewer *gv);
	int  chooseHospitalShortestWay(int source, Graph<int> graf, GraphViewer *gv, vector<int> hospitals);
	vector<int> selectVertexIcon(Graph<int> graf, GraphViewer *gv, string image, int nr_images);

};
#endif /* WAY_H_ */
