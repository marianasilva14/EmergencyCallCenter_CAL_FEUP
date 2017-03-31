/*
 * Way.cpp
 *
 *  Created on: 31/03/2017
 *      Author: Sissi
 */

#include "Way.h"

void Way::printPath(int source, int destiny, Graph<int> graf, GraphViewer *gv, string color){
	vector<int> path;

	if((graf.getVertex(source) != NULL) && (graf.getVertex(destiny) != NULL))
		path = graf.getPath(source,destiny);

	for(unsigned int i = 0; i <path.size(); i++){
		cout << path[i]<< endl;
		gv->setVertexColor(path[i], color);
	}

}

