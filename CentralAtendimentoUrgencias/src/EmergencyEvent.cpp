/*
 * EmergencyEvent.cpp
 *
 */

#include "EmergencyEvent.h"

EmergencyEvent::EmergencyEvent() {
}

EmergencyEvent::~EmergencyEvent() {
}

void EmergencyEvent::printPictureEmergency(GraphViewer *gv, int local){
	gv->setVertexIcon(local, "emergency.png");
}

vector<pair<int,unsigned int>> EmergencyEvent::sortPriorityVector(vector<pair<int,unsigned int>> priority_vector){

	vector<pair<int,unsigned int>> sortPriority;

	for(int j=1; j < 4; j++){
		for(unsigned int i=0; i < priority_vector.size();i++){
			if(priority_vector[i].first == j)
				sortPriority.push_back(priority_vector[i]);
		}
	}

	return sortPriority;
}

string EmergencyEvent::colorEmergencyPriority(int priority){
	string color;

	if(priority==1)
		color="RED";
	else if(priority==2)
		color="YELLOW";
	else
		color="GREEN";

	return color;
}

vector<int> EmergencyEvent::connectity(Graph<int> graf,GraphViewer *gv){
	vector<int> results;

	for(Vertex<int>*elem : graf.getVertexSet())
		elem->setVisited(false);


	for(int i=0; i < graf.getVertexSet().size();i++){
		graf.bfs(graf.getVertexSet()[i],gv);
		int falhas = 0;
		for(Vertex<int>*elem : graf.getVertexSet()){

			if(!elem->getVisited()){
				falhas++;
			}
		}

		results.push_back(falhas);

		for(Vertex<int>*elem : graf.getVertexSet())
				elem->setVisited(false);
	}

	return results;
}

float EmergencyEvent::averageConnectivity(Graph<int> graf,GraphViewer *gv){

	float average;
	int sum = 0;

	vector<int> falhas;
	falhas = connectity(graf,gv);

	for(int i = 0; i < falhas.size(); i++)
		sum += falhas[i];

	average = (double)sum/falhas.size();
	cout << endl << "Graph's connectivity: " << average << endl << endl;

	return average;
}


