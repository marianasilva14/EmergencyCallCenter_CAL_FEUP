/*
 * Way.cpp
 *
 *  Created on: 31/03/2017
 *      Author: Sissi
 */

#include "Way.h"

void Way::printPath(int source, int destiny, Graph<int> graf, GraphViewer *gv, string color){
	vector<int> path;

	if((graf.getVertex(source) != NULL) && (graf.getVertex(destiny) != NULL)){
		graf.dijkstraShortestPath(source);
		path = graf.getPath(source,destiny);
		for(unsigned int i = 0; i <path.size()-1; i++){
			sleep(3);
			gv->setEdgeColor(graf.getVertex(path[i])->getIdEdge(path[i+1]),color);
			gv->setEdgeThickness(graf.getVertex(path[i])->getIdEdge(path[i+1]), 3);
			gv->rearrange();
		}
	}

}

bool Way::hospitalAlreadyExist(vector<unsigned int> hospitals, unsigned int transport){
	for(int i=0; i < hospitals.size();i++)
	{
		if(hospitals[i]==transport)
			return true;
	}
	return false;
}
vector<unsigned int> Way::selectVertexIcon(Graph<int> graf, GraphViewer *gv, string image, int nr_images, vector<unsigned int> hospitals){
	int random_vertex;
	vector<unsigned int> places;

	for(unsigned int i=0; i < nr_images;i++){
			do{
				random_vertex= rand() % graf.getVertexSet().size()-1;
			}while(hospitalAlreadyExist(hospitals,random_vertex));

		gv->setVertexIcon(graf.getVertexSet()[random_vertex-1]->getInfo(),image);
		places.push_back(random_vertex);
	}

	return places;

}

vector<unsigned int> Way::selectHospital( Graph<int> graf, GraphViewer *gv){

	vector<Vertex<int>*> vet = graf.getVertexSet();
	int random_vertex;
	vector<unsigned int> hospitals;

	for(unsigned int i=0; i < 5;i++){
		random_vertex= rand() % vet.size();
		hospitals.push_back(vet[random_vertex]->getInfo()-1);
		gv->setVertexIcon(random_vertex,"hospital.png");
	}

	return hospitals;
}

unsigned int  Way::chooseNearestDestiny(int source, Graph<int> graf, GraphViewer *gv, vector<unsigned int> destinies){

	unsigned int destiny_choosed;
	graf.dijkstraShortestPath(source);

	vector<Vertex<int>*> path;
	double dist=1000000;

	path= graf.getVertexSet();

	for(int i=0; i < path.size();i++){
		for(int j=0; j < destinies.size();j++){
			if(path[i]->getDist() < dist && path[i]->getInfo()== destinies[j]){
				dist=path[i]->getDist();
				destiny_choosed=destinies[j];
			}
		}
	}

	return destiny_choosed;
}

void Way::inactiveTransport(GraphViewer *gv,vector<unsigned int>& destinies, int destiny_choosed,unsigned int hospital, vector<unsigned int> hospitals){

	bool changeHospitalIcon;
	for(int i=0; i < hospitals.size();i++){
		if(destiny_choosed==hospitals[i])
			changeHospitalIcon=true;
	}

	if(changeHospitalIcon)
		gv->setVertexIcon(destiny_choosed,"hospital.png");
	else{
		gv->setVertexIcon(destiny_choosed,"");
		gv->setVertexColor(destiny_choosed,"GRAY");
		gv->rearrange();
	}

	auto destinies1 = find(destinies.begin(), destinies.end(), destiny_choosed);
		if(destinies1 == destinies.end())
			cout << "Não encontrou" << endl;
		destinies.erase(destinies1);

		destinies.push_back(hospital);

		gv->setVertexIcon(hospital,"shop.png");

}

