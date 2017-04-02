#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <conio.h>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <queue>
#include <iomanip>
#include <unistd.h>
#include "edgetype.h"
#include "graphviewer.h"
#include "Graph.h"
#include "Way.h"

#define xwindow 1000
#define ywindow 1000


class Edge_temp{
public:
	bool istwoway;
	long long idRoad;
};

//calculate haversine distance for linear distance
double haversine_km(int x, int y, int x2, int y2) {

	double dx,dy,d;

	dx=x2-x;
	dy=y2-y;

	d=sqrt(dx*dx+dy*dy);

	return d;

}

void readFiles(GraphViewer *gv, Graph<int> & graf){
	gv->createWindow(xwindow, ywindow);
	Way way;

	gv->defineEdgeColor("blue");
	gv->defineVertexColor("yellow");



	ifstream inFile;

	//Read the FileNodes.txt
	inFile.open("FileNodes.txt");

	if (!inFile) {
		cerr << "Unable to open file datafile.txt";
		exit(1);   // call system to stop
	}

	std::string   line;

	int id_No=0;
	int x,y;

	while(std::getline(inFile, line))
	{
		std::stringstream linestream(line);
		std::string data;

		linestream >> id_No;
		std::getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> x;
		std::getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> y;

		gv->addNode(id_No, x,y );

		graf.addVertex(id_No,x,y);
	}

	inFile.close();


	ifstream inFile2;

	//Read the FileRoads.txt
	inFile2.open("FileRoads.txt");

	if (!inFile2) {
		cerr << "Unable to open file datafile.txt";
		exit(1);   // call system to stop
	}


	int road_id=0;
	string isTwoWay;
	vector<Edge_temp> edge_vector;


	while(std::getline(inFile2, line))
	{
		std::stringstream linestream(line);
		std::string data;

		linestream >> road_id;
		std::getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> isTwoWay;

		Edge_temp edge;
		if(isTwoWay=="True")
			edge.istwoway=true;
		else
			edge.istwoway=false;


		edge.idRoad=road_id;

		edge_vector.push_back(edge);

	}

	inFile2.close();

	ifstream inFile3;
	//Read the FileConection.txt
	inFile3.open("FileConection.txt");

	if (!inFile3) {
		cerr << "Unable to open file datafile.txt";
		exit(1);   // call system to stop
	}

	int roadId=0;
	int node1_id=0;
	int node2_id=0;
	int i = 0;

	while(std::getline(inFile3, line))
	{
		std::stringstream linestream(line);
		std::string data;

		linestream >> roadId;
		std::getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> node1_id;
		std::getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> node2_id;
		std::getline(linestream, data, ';');  // read up-to the first ; (discard ;).

		gv->addEdge(i, node1_id, node2_id, EdgeType::DIRECTED);
		int source =node1_id;
		int destiny = node2_id;
		graf.addEdge(source,destiny,haversine_km(graf.getVertex(source)->getX(),graf.getVertex(source)->getY(),graf.getVertex(destiny)->getX(),graf.getVertex(destiny)->getY()));
		i++;

		for(int j=0; j < edge_vector.size();j++){
			if(roadId == edge_vector[j].idRoad){
				if(edge_vector[j].istwoway){
					gv->addEdge(i, node2_id, node1_id, EdgeType::DIRECTED);
					graf.addEdge(destiny,source,haversine_km(graf.getVertex(source)->getX(),graf.getVertex(source)->getY(),graf.getVertex(destiny)->getX(),graf.getVertex(destiny)->getY()));
					i++;
				}
			}
		}
	}

	inFile3.close();
	//way.selectVertexIcon(graf,gv, "shop.png", 3);

	gv->rearrange();


}
/*
void menu(){

	cout << " WELCOME TO EMERGENCY SERVICE CENTER " << endl;
	cout << "Make the call!" << endl;

	cout << "Select the emergency type: " << endl;
	cout << "1: High" << endl;
	cout << "2: Medium" << endl;
	cout << "3: Low" << endl;

	int option;
	while(option !=1 | option!=2 | option !=3)
		cin >> option;

}
*/



int main() {
	Graph<int> graf;
	GraphViewer *gv = new GraphViewer(xwindow, ywindow, false);
	gv->defineEdgeCurved(false);
	Way way;
	EmergencyEvent emergency;
	vector<int> hospitals, ambulances,motorcycles,cars;
	int position_emergency;
	unsigned int microseconds=50;

	readFiles(gv, graf);
	ambulances=way.selectVertexIcon(graf,gv, "ambulance.png", 2);
	motorcycles=way.selectVertexIcon(graf,gv, "motorcycle.png", 2);
	cars=way.selectVertexIcon(graf,gv, "car.png", 2);

	for(int i=0; i < 3;i++){
		position_emergency=emergency.raflleEmergency(graf,gv);
		way.chooseShortestWay(position_emergency,graf,gv);
		usleep(microseconds);
	}
	//menu();

	graf.dijkstraShortestPath(1);

	//	vector<Vertex<NoInfo>*> vet = graf.getVertexSet();
	//	for(unsigned int i = 0; i < vet.size(); i++)
	//		cout << vet[i]->getInfo().idNo  << endl;

	getchar();
	cout << "END";
	return 0;

}
