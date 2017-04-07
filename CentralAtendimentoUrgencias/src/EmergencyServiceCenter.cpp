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

#define xwindow 1000
#define ywindow 650

class Edge_temp{
public:
	bool istwoway;
	int idRoad;
};

/**
 * Calculate the distance between two nodes
 * @param x x position of source
 * @param y y position of source
 * @param x2 x position of destiny
 * @param y2 y position of destiny
 * @return distance between two nodes
 */
double haversine_km(int x, int y, int x2, int y2) {

	double dx,dy,d;

	dx=x2-x;
	dy=y2-y;

	d=sqrt(dx*dx+dy*dy);

	return d;

}

/**
 * Read the files that represents the graph
 * @param gv GraphViewer
 * @param graf Graph
 */
void readFiles(GraphViewer *gv, Graph<int> & graf, string FileNodes, string FileRoads, string FileConection){
	gv->createWindow(xwindow, ywindow);
	Way way;

	gv->defineEdgeColor("black");
	gv->defineVertexColor("gray");



	ifstream inFile;

	//Read the FileNodes.txt
	inFile.open(FileNodes);

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
	inFile2.open(FileRoads);

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
	inFile3.open(FileConection);

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

/**
 * Graph Menu
 */
vector<string> graphMenu(){

	int option=0;
	vector<string> files;

	cout << "Select the graph: " << endl;
	cout << "1: Big" << endl;
	cout << "2: Medium" << endl;
	cout << "3: Small" << endl;

	while(option != 1 && option!=2 && option !=3)
			cin >> option;

	switch(option){
	case 1:
		files.push_back("FileNodes.txt");
		files.push_back("FileRoads.txt");
		files.push_back("FileConection.txt");
		break;
	case 2:
		files.push_back("FileNodes2.txt");
		files.push_back("FileRoads2.txt");
		files.push_back("FileConection2.txt");
		break;
	case 3:
		files.push_back("FileNodes3.txt");
		files.push_back("FileRoads3.txt");
		files.push_back("FileConection3.txt");
		break;
	}

	return files;
}
/**
 * Priority menu
 * @param graf Graph
 * @param call pair that saves the priority and location of the emergency
 */
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

/**
 * Main menu
 * @param graf Graph
 * @param gv GraphViewer
 * @param call pair that saves the priority and location of the emergency
 * @return option the option selected by the user
 */
int menu(Graph<int> graf,GraphViewer *gv, pair<int,unsigned int> &call){
	cout << endl << " WELCOME TO EMERGENCY SERVICE CENTER " << endl << endl;
	cout << "1. Make the call" << endl;
	cout << "2. Evaluate connectivity"<<endl;
	cout << "3. Calculation of algorithm time" << endl;
	cout << "4. End the calls"<< endl;
	cout << "5. Exit"<< endl;

	int option;
	EmergencyEvent emergency;

	cin >> option;

	switch(option){
	case 1: priorityMenu(graf,call);
	break;
	case 2: emergency.averageConnectivity(graf,gv);
	break;
	case 3:
		graf.calculateTime(graf);
		break;
	case 4:
		break;
	case 5:
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
	vector<unsigned int> hospitals,transports_positions;
	vector<pair<int,unsigned int>> emergencies;
	vector<string> files=graphMenu();

	int option;
	string end;
	pair<int,unsigned int> call;
	bool end_calls=false;


	readFiles(gv, graf, files[0],files[1],files[2]);

	call.first=1;
	call.second=2;

	hospitals= way.selectHospital(graf,gv);
	transports_positions=way.positionsTransport(graf,gv,hospitals);

	while(option != 5){
		switch(menu(graf,gv,call)){
		case 1:
			option=1;
			if(!end_calls)
			{
				emergencies.push_back(call);
				emergency.printPictureEmergency(gv,call.second);
			}
			break;
		case 2:
			option=2;
			break;
		case 3:
			option=3;
			break;
		case 4:
			option=4;
			end_calls=true;
			emergency.startEmergencies(graf,gv, hospitals, transports_positions, emergencies);
			break;
		case 5:
			option=5;
			break;
		}
	}
	getchar();

	cout << "END";
	return 0;

}
