#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <conio.h>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
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
#include "matcher.h"

#define xwindow 1000
#define ywindow 650

class Edge_temp{
public:
	bool istwoway;
	int idRoad;
	string nameRoad;

};
vector<Edge_temp> edge_vector;
map<int,string> edges;
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
 * @param FileNodes nodes file
 * @param FileRoads roads file
 * @param FileConnection connection file
 */
void readFiles(GraphViewer *gv, Graph<int> & graf, string FileNodes, string FileRoads, string FileConnection){
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
	string road_name;
	Edge_temp edge;
	line.clear();


	while(std::getline(inFile2, line))
	{
		std::stringstream linestream(line);
		std::string data;
		linestream >> road_id;
		std::getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		std::getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		road_name = data;
		linestream >> isTwoWay;


		if(isTwoWay=="True")
			edge.istwoway=true;
		else
			edge.istwoway=false;


		edge.idRoad=road_id;
		edge.nameRoad=road_name;

		map<int,string>::iterator it=edges.begin();
		edges.insert(it,pair<int,string>(road_id,road_name));

		edge_vector.push_back(edge);


	}

	map<int,string>::iterator ite;
	for(ite=edges.begin();ite != edges.end();++ite){
		cout << ite->first << " " << ite->second << endl;
		gv->setEdgeLabel((2*ite->first+1), ite->second);
		// gv->setEdgeLabel(2*ite->first, ite->second);
	}

	inFile2.close();

	ifstream inFile3;
	//Read the FileConnection.txt
	inFile3.open(FileConnection);

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
		i++;

		for(unsigned int j=0; j < edge_vector.size();j++){

			if(roadId == edge_vector[j].idRoad){

				if(edge_vector[j].istwoway){
					gv->addEdge(i, node2_id, node1_id, EdgeType::DIRECTED);
					graf.addEdge(destiny,source,haversine_km(graf.getVertex(source)->getX(),graf.getVertex(source)->getY(),graf.getVertex(destiny)->getX(),graf.getVertex(destiny)->getY()),i);
					i++;
				}
			}
		}
	}

	inFile3.close();
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
		files.push_back("FileNodes3.txt");
		files.push_back("FileRoads3.txt");
		files.push_back("FileConnection3.txt");
		break;
	case 2:
		files.push_back("FileNodes2.txt");
		files.push_back("FileRoads2.txt");
		files.push_back("FileConnection2.txt");
		break;
	case 3:
		files.push_back("FileNodes.txt");
		files.push_back("FileRoads.txt");
		files.push_back("FileConnection.txt");
		break;
	}

	return files;
}

vector<int> researchRoadExact(Graph<int> graf, GraphViewer *gv, vector<Edge_temp> edge_vector,string road, int priority){

	unsigned int local=0;
	unsigned int aux_local;
	vector<int> edges_choose;
	EmergencyEvent emergency;
	Way way;

	map<int,string>::iterator ite;
	for(ite=edges.begin();ite != edges.end();++ite){
		aux_local=kmp(ite->second,road);
		if(aux_local > local){
			local=aux_local;
			edges_choose.push_back(ite->first);
		}
	}

	way.printChoosenRoads(graf,gv,edges_choose,priority);

	return edges_choose;
}

vector<int> researchRoadApproximate(Graph<int> graf, GraphViewer *gv, vector<Edge_temp> edge_vector,string road, int priority){

	unsigned int dist=100000000;
	unsigned int aux_dist;
	vector<int> edges_choose;
	EmergencyEvent emergency;
	Way way;

	map<int,string>::iterator ite;
	for(ite=edges.begin();ite != edges.end();++ite){
		aux_dist=editDistance(road, ite->second);
		edges_choose.push_back(ite->first);

	}

	way.printChoosenRoads(graf,gv,edges_choose,priority);

	return edges_choose;
}

unsigned int localMenu(Graph<int> graf, GraphViewer *gv, pair<int,unsigned int> &call, int priority){

	char option;
	int node;
	vector<int> edges;
	int local=1000;
	EmergencyEvent emergency;
	string road;

	cout << "Select the local: " << endl;
	cout << "1: By name" << endl;
	cout << "2: By ID node" << endl;

	while(option != '1' && option!='2')
		cin >> option;

	switch(option){
	case '1':
		cin.ignore(1000, '\n');
		getline(cin,road);
		edges=researchRoadExact(graf,gv, edge_vector, road,priority);
		if(edges.size()==0){
			researchRoadApproximate(graf,gv, edge_vector, road,priority);
		}
		return local=-1;
		break;
	case '2':
		while(local > graf.getVertexSet().size())
			cin >> local;

		break;
	default:
		break;
	}

	return local;

}
/**
 * Priority menu
 * @param graf Graph
 * @param call pair that saves the priority and location of the emergency
 */
int priorityMenu(Graph<int> graf,GraphViewer *gv, pair<int,unsigned int> &call){

	string option = "";
	unsigned int local=1000000;
	EmergencyEvent emergency;
	int userOption;

	cout << "Select the emergency type: " << endl;
	cout << "1: High" << endl;
	cout << "2: Medium" << endl;
	cout << "3: Low" << endl;


	while(option != "1" && option!="2" && option !="3")
		cin >> option;


	stringstream teste(option);
	int op;
	teste >> op;
	userOption=localMenu(graf,gv,call,op);

	if(userOption>0){
		call.first= op;
		call.second=userOption;
	}

	return userOption;
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
	case 1:
		if(priorityMenu(graf,gv,call)<0)
			return 6;
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
		case 6:
			option=6;
		}
	}
	getchar();

	cout << "END";
	return 0;

}
