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

vector<int> Way::selectHospital( Graph<int> graf, GraphViewer *gv, string color){

	vector<Vertex<int>*> vet = graf.getVertexSet();
	int random_vertex;
	vector<int> hospitals;

	for(unsigned int i=0; i < 15;i++){
		random_vertex= rand() % vet.size();
		hospitals.push_back(vet[random_vertex]->getInfo());
		gv->setVertexColor(vet[random_vertex]->getInfo(), color);
	}

	for(unsigned int i = 0; i < vet.size(); i++)
		cout << vet[i]->getInfo() << endl;

	return hospitals;
}

void  Way::chooseShortestWay(int source, Graph<int> graf, GraphViewer *gv){


	vector<int> hospitals =selectHospital(graf,gv,RED);

	graf.dijkstraShortestPath(source);

	vector<Vertex<int>*> path;
	double dist=0;
	int vertex;

	path= graf.getVertexSet();

	for(int i=0; i < path.size();i++){
		for(int j=0; j < hospitals.size();j++){
			if(path[i]->getDist() < dist && path[i]->getInfo()== hospitals[j]){
				dist=path[i]->getDist();
				vertex=hospitals[j];
			}
		}
	}

	printPath(source, vertex, graf,gv,BLUE);
}

