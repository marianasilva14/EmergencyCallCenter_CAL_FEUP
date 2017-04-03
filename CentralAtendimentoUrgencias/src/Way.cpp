/*
 * Way.cpp
 *
 *  Created on: 31/03/2017
 *      Author: Sissi
 */

#include "Way.h"

/*
void Way::printVertex(int source, int destiny, Graph<int> graf, GraphViewer *gv, string color){
	vector<int> vertex;

	if((graf.getVertex(source) != NULL) && (graf.getVertex(destiny) != NULL))
		vertex = graf.getPath(source,destiny);

	for(unsigned int i = 0; i <vertex.size()-1; i++){
		if(color.find('.')!=std::string::npos)
			gv->setVertexIcon(vertex[i], color);
		else
			gv->setVertexColor(vertex[i], color);
	}

}*/

void Way::printPath(int source, int destiny, Graph<int> graf, GraphViewer *gv, string color){
	vector<int> path;
	cout << "funcao print path" <<endl;
	if((graf.getVertex(source) != NULL) && (graf.getVertex(destiny) != NULL)){
		path = graf.getPath(source,destiny);
		cout << path.size() << endl;
		for(unsigned int i = 0; i <path.size()-1; i++){
			gv->setEdgeColor(graf.getVertex(path[i])->getIdEdge(path[i+1]),color);
			cout << path[i] << endl;
			cout << "ligado por " << graf.getVertex(path[i])->getIdEdge(path[i+1]) << endl;
			cout << path[i+1] << endl;
			gv->setEdgeThickness(graf.getVertex(path[i])->getIdEdge(path[i+1]), 5);
			gv->rearrange();
			//sleep(1000);
		}
	}

}
vector<int> Way::selectVertexIcon(Graph<int> graf, GraphViewer *gv, string image, int nr_images){
	int random_vertex;
	vector<int> places;

	for(unsigned int i=0; i < nr_images;i++){
		random_vertex= rand() % graf.getVertexSet().size()-1;
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

int  Way::chooseClosestHospital(int source, Graph<int> graf, GraphViewer *gv, vector<int> hospitals){

	int hospital_choosed;
	graf.dijkstraShortestPath(source);

	vector<Vertex<int>*> path;
	double dist=1000000;


	path= graf.getVertexSet();

	for(int i=0; i < path.size();i++){
		for(int j=0; j < hospitals.size();j++){
			if(path[i]->getDist() < dist && path[i]->getInfo()== hospitals[j]){
				dist=path[i]->getDist();
				hospital_choosed=hospitals[j];
			}
		}
	}

	return hospital_choosed;
}

