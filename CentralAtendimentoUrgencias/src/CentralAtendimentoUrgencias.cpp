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

#define xwindow 1000
#define ywindow 500
#define latitude_max 41.15094
#define latitude_min 41.14853
#define longitude_max -8.61090
#define longitude_min -8.61728

class NoInfo{
public:
	long long idNo;
	double longitude_radians;
	double latitude_radians;
	NoInfo(long long idNo, double longitude_radians, double latitude_radians){
		this->idNo = idNo;
		this->longitude_radians = longitude_radians;
		this->latitude_radians = latitude_radians;
	}

	long long getIdNo(){
		return idNo;
	}

	double getLongitude_radians(){
		return longitude_radians;
	}

	double getLatitude_radians(){
		return latitude_radians;
	}

	friend bool operator==(NoInfo const & left,NoInfo const & right){
		return left.idNo == right.idNo;
	}

	friend bool operator!=(NoInfo const & left,NoInfo const & right){
		return left.idNo != right.idNo;
	}
};
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

		NoInfo no(id_No% numeric_limits<int>::max(),longitude_radians, latitude_radians);

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

		gv->addEdge(i, node1_id % numeric_limits<int>::max(), node2_id % numeric_limits<int>::max(), EdgeType::DIRECTED);
		NoInfo origem =graf.getVertex(NoInfo(node1_id % numeric_limits<int>::max(),0,0))->getInfo();
		NoInfo destino = graf.getVertex(NoInfo(node2_id % numeric_limits<int>::max(),0,0))->getInfo();
		//		graf.addEdge(origem,destino,haversine_km(origem.getLatitude_radians(),origem.getLongitude_radians(),destino.getLongitude_radians(),destino.getLatitude_radians()));
		i++;

	}

	ifstream inFile3;
	//Ler o ficheiro FileRoads.txt
	inFile3.open("FileRoads.txt");

	if (!inFile3) {
		cerr << "Unable to open file datafile.txt";
		exit(1);   // call system to stop
	}

	long long roadId=0;
	string road_name;
	bool is_two_way;
	long i = 0;

	map<long,vector<string,bool>> wayInfo;

	while(std::getline(inFile3, line))
	{
		std::stringstream linestream(line);
		std::string data;
		vector<string,bool> type_road;

		linestream >> roadId;
		std::getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> road_name;
		std::getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> is_two_way;

		type_road.insert(road_name, is_two_way);

		//gv->addEdge(i, EdgeType::DIRECTED);
		//NoInfo origem =graf.getVertex(NoInfo(node1_id % numeric_limits<int>::max(),0,0))->getInfo();
		//NoInfo destino = graf.getVertex(NoInfo(node2_id % numeric_limits<int>::max(),0,0))->getInfo();
		//		graf.addEdge(origem,destino,haversine_km(origem.getLatitude_radians(),origem.getLongitude_radians(),destino.getLongitude_radians(),destino.getLatitude_radians()));
		i++;

	}


	gv->rearrange();
}


int main() {
	GraphViewer *gv = new GraphViewer(1000, 500, false);
	gv->defineEdgeCurved(false);
	gv->setBackground("map2.png");
	Graph<NoInfo> graf;
	readFiles(gv, graf);
	vector<NoInfo> caminho;
	if((graf.getVertex(NoInfo(25620653% numeric_limits<int>::max(),0,0)) != NULL) &&(graf.getVertex(NoInfo(747467609% numeric_limits<int>::max(),0,0)) != NULL))
		caminho = graf.getPath(NoInfo(25620653% numeric_limits<int>::max(),0,0),NoInfo(747467609% numeric_limits<int>::max(),0,0));

	for(unsigned int i = 0; i <caminho.size(); i++){
		cout << caminho[i].idNo << endl;
		gv->setVertexColor(caminho[i].idNo,BLACK);
	}

	for(unsigned int i = 0; i < 20 ; i++)
		gv->setEdgeColor(i,GREEN);
	//
	//	}

	getchar();
	cout << "END";
	return 0;

}
