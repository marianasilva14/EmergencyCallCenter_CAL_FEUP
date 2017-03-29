#include <cstdio>
#include "graphviewer.h"
#include "Graph.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "NoInfo.h"

#define xwindow 600
#define ywindow 600
#define latitude_max 41.15020
#define latitude_min 41.14859
#define longitude_max -8.61153
#define longitude_min -8.61398


//calculate haversine distance for linear distance // coordinates in radians
long double haversine_km(long double lat1, long double long1, long double lat2, long double long2) {
	long double dlong = (long2 - long1);
	long double dlat = (lat2 - lat1);
	long double a = pow(sin(dlat / 2.0), 2) + cos(lat1) * cos(lat2) * pow(sin(dlong / 2.0), 2);
	long double c = 2 * atan2(sqrt(a), sqrt(1 - a));
	long double d = 6367 * c;

	return d;
}

void readFiles(GraphViewer *gv, Graph<NoInfo> graf){
	gv->createWindow(600, 600);

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
		int delta_x, delta_y;

		delta_x= xwindow/(longitude_max-longitude_min);
		delta_y= ywindow/(latitude_max-latitude_min);

		xw=(longitude_radians-longitude_min)*delta_x;
		yw=(latitude_radians-latitude_min)*delta_y;

		gv->addNode(id_No%100000000, xw,ywindow-yw);

		NoInfo no(id_No,longitude_radians, latitude_radians);

		//gv->addNode(id_No%100000000);
		graf.addVertex(no);
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

		gv->addEdge(i, node1_id%100000000, node2_id%100000000, EdgeType::DIRECTED);
		NoInfo origem =graf.getVertex(NoInfo(node1_id,0,0))->getInfo();
		NoInfo destino = graf.getVertex(NoInfo(node2_id,0,0))->getInfo();
		graf.addEdge(origem,destino,haversine_km(origem.getLatitude_radians(),origem.getLongitude_radians(),destino.getLongitude_radians(),destino.getLatitude_radians()));
		i++;

	}

	gv->rearrange();
}

int main() {
	GraphViewer *gv = new GraphViewer(600, 600, true);
	gv->setBackground("mapa.png");
	Graph<NoInfo> graf;
	readFiles(gv, graf);

	if((graf.getVertex(NoInfo(25620737,0,0)) != NULL) &&(graf.getVertex(NoInfo(25620516,0,0)) != NULL)){
		vector<NoInfo> caminho = graf.getPath(NoInfo(25620737,0,0),NoInfo(25620516,0,0));

//		for(unsigned int i = 0; i <caminho.size(); i++){
//			Sleep(100);
//
//			cout << caminho[i].idNo << endl;
//			gv->setVertexColor(caminho[i].idNo,GREEN);
//		}

		for(unsigned int i = 0; i < 20 ; i++)
			gv->setEdgeColor(i,GREEN);
	}

	getchar();
	cout << "END";
	return 0;
}
