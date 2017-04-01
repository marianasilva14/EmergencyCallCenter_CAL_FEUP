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
#include <map>
#include <iomanip>
#include "edgetype.h"
#include "graphviewer.h"
#include "Graph.h"
#include "Way.h"

#define xwindow 1000
#define ywindow 500
#define latitude_max 41.15094
#define latitude_min 41.14853
#define longitude_max -8.61090
#define longitude_min -8.61728


//calculate haversine distance for linear distance // coordinates in radians
long double haversine_km(long double lat1, long double long1, long double lat2, long double long2) {
	long double dlong = (long2 - long1);
	long double dlat = (lat2 - lat1);
	long double a = pow(sin(dlat / 2.0), 2) + cos(lat1) * cos(lat2) * pow(sin(dlong / 2.0), 2);
	long double c = 2 * atan2(sqrt(a), sqrt(1 - a));
	long double d = 6367 * c;

	return d;
}

void readFiles(GraphViewer *gv, Graph<int> & graf){
	gv->createWindow(1000, 500);

	gv->defineEdgeColor("blue");
	gv->defineVertexColor("yellow");

	ifstream inFile;

	//Ler o ficheiro FileNodes.txt
	inFile.open("FileNodes.txt");

	if (!inFile) {
		cerr << "Unable to open file datafile.txt";
		exit(1);   // call system to stop
	}

	std::string   line;

	long long id_No=0;
	double latitude_degrees=0;
	double longitude_degrees=0;
	double longitude_radians=0;
	double latitude_radians=0;

	double delta_x, delta_y;

	delta_x = longitude_max-longitude_min;
	delta_y = latitude_max-latitude_min;

	while(std::getline(inFile, line))
	{
		std::stringstream linestream(line);
		std::string data;

		linestream >> id_No;
		std::getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> latitude_degrees;
		std::getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> longitude_degrees;

		std::getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> longitude_radians;
		std::getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> latitude_radians;

		int xw,yw;

		xw = (longitude_degrees - longitude_min) / delta_x * xwindow;
		yw = (latitude_degrees - latitude_min) / delta_y * ywindow;

		gv->addNode(id_No % numeric_limits<int>::max(), xw,ywindow-yw);

		graf.addVertex(id_No % numeric_limits<int>::max(),longitude_radians, latitude_radians);
	}

	ifstream inFile2;
	//Ler o ficheiro FileConection.txt
	inFile2.open("FileConection.txt");

	if (!inFile2) {
		cerr << "Unable to open file datafile.txt";
		exit(1);   // call system to stop
	}

	long long roadId=0;
	long long node1_id=0;
	long long node2_id=0;
	long i = 0;

	while(std::getline(inFile2, line))
	{
		std::stringstream linestream(line);
		std::string data;

		linestream >> roadId;
		std::getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> node1_id;
		std::getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> node2_id;
		std::getline(linestream, data, ';');  // read up-to the first ; (discard ;).

		gv->addEdge(i, node1_id % numeric_limits<int>::max(), node2_id % numeric_limits<int>::max(), EdgeType::DIRECTED);
		int source =node1_id % numeric_limits<int>::max();
		int destiny = node2_id % numeric_limits<int>::max();
		graf.addEdge(source,destiny,haversine_km(graf.getVertex(source)->getLatitude_radians(),graf.getVertex(source)->getLongitude_radians(),graf.getVertex(destiny)->getLongitude_radians(),graf.getVertex(destiny)->getLatitude_radians()));
		i++;

	}

	gv->rearrange();


}

void menu(){

	cout << " WELCOME TO EMERGENCY SERVICE CENTER " << endl;
	cout << "Make the call!" << endl;

	cout << "Select the priority type: " << endl;
	cout << "Option a: High" << endl;
	cout << "Option b: Medium" << endl;
	cout << "Option c: Low" << endl;

	char option;
	cin >> option;
}


int main() {
	Graph<int> graf;
	GraphViewer *gv = new GraphViewer(1000, 500, false);
	gv->defineEdgeCurved(false);
	gv->setBackground("map2.png");
	Way way;
	vector<int> hospitals;

	readFiles(gv, graf);
	//menu();

	graf.dijkstraShortestPath(25620516);

//	vector<Vertex<NoInfo>*> vet = graf.getVertexSet();
//	for(unsigned int i = 0; i < vet.size(); i++)
//		cout << vet[i]->getInfo().idNo  << endl;


	way.printPath(25620516,231594184, graf,gv,BLACK);
	hospitals= way.selectHospital(graf,gv,RED);
	way.chooseShortestWay(25620516, graf,gv);
	for(unsigned int i = 0; i < 20 ; i++)
		gv->setEdgeColor(i,GREEN);


	getchar();
	cout << "END";
	return 0;

}
