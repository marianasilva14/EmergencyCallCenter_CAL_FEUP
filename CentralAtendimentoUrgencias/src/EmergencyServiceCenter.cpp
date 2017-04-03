#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <conio.h>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <sys/types.h>
#include <stdio.h>
#include <queue>
#include <iomanip>
#include <unistd.h>
#include "edgetype.h"
#include "EmergencyEvent.h"
#include "graphviewer.h"
#include "Graph.h"
#include "Way.h"
#include "Transport.h"

#define xwindow 1000
#define ywindow 650


class Edge_temp{
public:
	bool istwoway;
	int idRoad;
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

	gv->defineEdgeColor("black");
	gv->defineVertexColor("gray");



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

		gv->addNode(id_No, x,y-300 );

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

		graf.addEdge(source,destiny,haversine_km(graf.getVertex(source)->getX(),graf.getVertex(source)->getY(),graf.getVertex(destiny)->getX(),graf.getVertex(destiny)->getY()),i);
		//gv->setEdgeLabel(i,to_string(i));
		i++;

		for(unsigned int j=0; j < edge_vector.size();j++){
			if(roadId == edge_vector[j].idRoad){
				if(edge_vector[j].istwoway){
					gv->addEdge(i, node2_id, node1_id, EdgeType::DIRECTED);
					//gv->setEdgeLabel(i,to_string(i));
					graf.addEdge(destiny,source,haversine_km(graf.getVertex(source)->getX(),graf.getVertex(source)->getY(),graf.getVertex(destiny)->getX(),graf.getVertex(destiny)->getY()),i);
					i++;
				}
			}
		}
	}

	inFile3.close();
	//way.selectVertexIcon(graf,gv, "shop.png", 3);

	gv->rearrange();


}
void priorityMenu(Graph<int> graf, pair<int,unsigned int> &call){

	string option = "";
	unsigned int local=1000000;
	EmergencyEvent emergency;

	cout << "Select the emergency type: " << endl;
	cout << "1: High" << endl;
	cout << "2: Medium" << endl;
	cout << "3: Low" << endl;


	while(option != "1" && option!="2" && option !="3")
		cin >> option;


	cout << "Select the local: " << endl;
	while(local > graf.getVertexSet().size())
		cin >> local;

	stringstream teste(option);
	int op;
	teste >> op;
	call.first= op;
	call.second=local;
}

int menu(Graph<int> graf, pair<int,unsigned int> &call){
	cout << " WELCOME TO EMERGENCY SERVICE CENTER " << endl;
	cout << "1. Make the call" << endl;
	cout << "2. Evaluate conectivity"<<endl;
	cout << "3. Exit"<< endl;

	int option;

	cin >> option;

	switch(option){
	case 1: priorityMenu(graf,call);
	break;
	case 2:
		break;
	case 3:
		break;
	}

	return option;
}




int main() {
	srand(time(NULL));
	Graph<int> graf;
	GraphViewer *gv = new GraphViewer(xwindow, ywindow, false);
	gv->defineEdgeCurved(false);
	Way way;
	EmergencyEvent emergency;
	vector<int> hospitals;
	vector<pair<int,unsigned int>> emergencies;
	Transport t;
	vector<int> transports_positions;
	int transport;
	int hospital;

	unsigned int microseconds=50;

	readFiles(gv, graf);
	string end;
	pair<int,unsigned int> call;
	call.first=1;
	call.second=2;

	hospitals= way.selectHospital(graf,gv);
	for(int i=0; i < hospitals.size();i++){
		cout << endl << hospitals[i] << endl;
	}
	transports_positions=t.positionsTransport(graf,gv,hospitals);

	for(int i=0; i < transports_positions.size();i++){
		cout << endl << transports_positions[i] << endl;
	}

	 while(menu(graf,call) != 3){
		 cout << "emergencia aqui "<< call.second << end;
		emergencies.push_back(call);
		emergency.printPictureEmergency(gv,call.second);
	}
	getchar();

	emergencies= emergency.sortPriorityVector(emergencies);
	cout <<"tamanho urgencias: " << emergencies.size() <<endl;
	for(unsigned int i=0; i < emergencies.size();i++){
		cout << "dentro do for" << endl;
		transport= t.chooseClosestTransport(emergencies[i].first,graf,gv, transports_positions);
		hospital= way.chooseClosestHospital(emergencies[i].first,graf,gv,hospitals);
		cout << transport << " " << hospital << endl;
		way.printPath(transport, emergencies[i].first,graf, gv, RED);
		way.printPath(emergencies[i].first, hospital, graf,gv, RED);
		//usleep(microseconds);
	}

	getchar();
	cout << "END";
	return 0;

}
