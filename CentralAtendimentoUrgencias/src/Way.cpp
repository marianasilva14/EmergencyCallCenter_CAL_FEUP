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

	for(unsigned int i = 0; i <path.size()-1; i++){
		cout << path[i]<< endl;
		if(color.find('.')!=std::string::npos)
			gv->setVertexIcon(path[i], color);
		else
			gv->setVertexColor(path[i], color);
	}

}

vector<int> Way::selectVertexIcon(Graph<int> graf, GraphViewer *gv, string image, int nr_images){
	int random_vertex;
	vector<int> places;

	for(unsigned int i=0; i <= nr_images;i++){
		random_vertex= rand() % nr_images;
		gv->setVertexIcon(graf.getVertexSet()[random_vertex]->getInfo(),image);
		places.push_back(random_vertex);
	}

	return places;

}

vector<int> Way::selectHospital( Graph<int> graf, GraphViewer *gv){

	vector<Vertex<int>*> vet = graf.getVertexSet();
	int random_vertex;
	vector<int> hospitals;

	for(unsigned int i=0; i < 5;i++){
		random_vertex= rand() % vet.size();
		hospitals.push_back(vet[random_vertex]->getInfo());
		gv->setVertexIcon(vet[random_vertex]->getInfo(),"hospital.png");
	}

	return hospitals;
}

void  Way::chooseShortestWayHospital(int source, Graph<int> graf, GraphViewer *gv){


	vector<int> hospitals =selectHospital(graf,gv);

	graf.dijkstraShortestPath(source);

	vector<Vertex<int>*> path;
	double dist=1000000;
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

	printPath(source, vertex, graf,gv,"ambulance.png");

}

void Way::chooseShortestWayTransport(int source, Graph<int> graf, GraphViewer *gv){

	Transport t;
	vector<pair<Transport::transport,int>> transports = t.positionsTransport(graf,gv);

	graf.dijkstraShortestPath(source);

	vector<Vertex<int>*> path;
	double dist=1000000;
	Transport::transport vertex;
	string transport_type;

	path= graf.getVertexSet();

	for(int i=0; i < path.size();i++){
		for(int j=0; j < transports.size();j++){
			if(path[i]->getDist() < dist && path[i]->getInfo() == transports[j].second){
				dist=path[i]->getDist();
				vertex =transports[j].first;
			}
		}
	}

	transport_type=t.associateImageTransport(vertex);
	printPath(source, vertex, graf,gv,transport_type);

}

