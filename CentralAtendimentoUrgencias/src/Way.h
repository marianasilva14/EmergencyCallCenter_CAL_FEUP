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

class Way{
public:
	void printPath(int source, int destiny, Graph<int> graf, GraphViewer *gv, string color);


};
#endif /* WAY_H_ */
