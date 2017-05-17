/*
 * EmergencyEvent.cpp
 *
 */

#include "EmergencyEvent.h"

EmergencyEvent::EmergencyEvent() {
}

EmergencyEvent::~EmergencyEvent() {
}

void EmergencyEvent::printPictureEmergency(GraphViewer *gv, int local) {
	gv->setVertexIcon(local, "emergency.png");
}

vector<pair<int, unsigned int>> EmergencyEvent::sortPriorityVector(
		vector<pair<int, unsigned int>> priority_vector) {

	vector<pair<int, unsigned int>> sortPriority;

	for (int j = 1; j < 4; j++) {
		for (unsigned int i = 0; i < priority_vector.size(); i++) {
			if (priority_vector[i].first == j)
				sortPriority.push_back(priority_vector[i]);
		}
	}

	return sortPriority;
}

string EmergencyEvent::colorEmergencyPriority(int priority) {
	string color;

	if (priority == 1)
		color = "RED";
	else if (priority == 2)
		color = "YELLOW";
	else
		color = "GREEN";

	return color;
}

vector<int> EmergencyEvent::connectity(Graph<int> graf, GraphViewer *gv) {
	vector<int> results;

	for (Vertex<int>*elem : graf.getVertexSet())
		elem->setVisited(false);

	for (unsigned int i = 0; i < graf.getVertexSet().size(); i++) {
		graf.bfs(graf.getVertexSet()[i], gv);
		int falhas = 0;
		for (Vertex<int>*elem : graf.getVertexSet()) {

			if (!elem->getVisited()) {
				falhas++;
			}
		}

		results.push_back(falhas);

		for (Vertex<int>*elem : graf.getVertexSet())
			elem->setVisited(false);
	}

	return results;
}

float EmergencyEvent::averageConnectivity(Graph<int> graf, GraphViewer *gv) {

	float average;
	int sum = 0;

	vector<int> falhas;
	falhas = connectity(graf, gv);

	for (unsigned int i = 0; i < falhas.size(); i++)
		sum += falhas[i];

	average = (double) sum / falhas.size();
	cout << endl << "Graph's connectivity: " << average << endl << endl;

	return average;
}

void EmergencyEvent::startEmergencies(Graph<int> graf, GraphViewer *gv,
		vector<unsigned int> hospitals,
		vector<unsigned int> transports_positions,
		vector<pair<int, unsigned int>> emergencies) {

	string priority_color;
	unsigned int nearest_transport, nearest_hospital;
	Way way;
	emergencies = sortPriorityVector(emergencies);

	for (unsigned int i = 0; i < emergencies.size(); i++) {
		priority_color = colorEmergencyPriority(emergencies[i].first);
		nearest_transport = way.chooseNearestDestiny(emergencies[i].second,
				graf, gv, transports_positions);
		nearest_hospital = way.chooseNearestDestiny(emergencies[i].second, graf,
				gv, hospitals);
		way.printPath(nearest_transport, emergencies[i].second, graf, gv,
				priority_color);
		way.printPath(emergencies[i].second, nearest_hospital, graf, gv,
				priority_color);
		way.inactiveTransport(gv, transports_positions, nearest_transport,
				nearest_hospital, hospitals);
	}
}

int EmergencyEvent::findLeftNode(Graph<int> graf, int edgeID) {

	int leftNode;
	for (unsigned int i = 0; i < graf.getVertexSet().size(); i++) {
		for (unsigned int j = 0; j < graf.getVertexSet()[i]->getAdj().size(); j++)
			if(graf.getVertexSet()[i]->getIdEdge(graf.getVertexSet()[i]->getAdj()[j].getDest()->getInfo()) == edgeID){
				leftNode= graf.getVertexSet()[i]->getInfo();
				break;
			}
	}
	return leftNode;
}

boolean EmergencyEvent::checkExistenceOfAppeal(Graph<int> graf, int edgeID,
		vector<unsigned int> hospitals,
		vector<unsigned int> transports_positions) {

	unsigned int leftNode, rightNode;

	leftNode = findLeftNode(graf, edgeID);
	rightNode = leftNode++;

	for (unsigned int i = 0; i < hospitals.size(); i++) {
		if (hospitals[i] == leftNode || hospitals[i] == rightNode)
			return true;
	}

	for (unsigned int i = 0; i < transports_positions.size(); i++) {
		if (transports_positions[i] == leftNode
				|| transports_positions[i] == rightNode)
			return true;
	}

	return false;

}


void EmergencyEvent::sortEdgesByDistance(vector<int> &edges_chosen,map<int, string> edges, map<int,int> aux){

	edges_chosen.clear();

	map<int, int>::iterator it;
	int min = 10000;
	int max = 0;
	for (it = aux.begin(); it != aux.end(); ++it) {
		if (it->second < min)
			min = it->second;
		if (it->second > max)
			max = it->second;
	}
	int differences = min;
	int i = 0;
	while (differences < max && i < RESULTS_APROX) {
		for (it = aux.begin(); it != aux.end(); ++it) {
			if (it->second == differences){
				cout << "distance: " << it->second << " -> " << edges.at(it->first) << endl;
				edges_chosen.push_back(it->first);
				i++;
			}
			if (i == RESULTS_APROX)
				break;
		}
		if (i == RESULTS_APROX)
			break;

		differences++;
	}
	if (edges_chosen.size() != 0)
		cout << "Approximate research" << endl << endl;
}
vector<int> EmergencyEvent::researchRoadExact(Graph<int> graf, GraphViewer *gv,
		string road, int priority, map<int, string> edges,
		pair<int, unsigned int> &call, vector<unsigned int> hospitals,
		vector<unsigned int> transports_positions) {

	unsigned int local = 0;
	unsigned int aux_local;
	int node;
	vector<int> edges_chosen;
	Way way;

	//kmp algorithm
	map<int, string>::iterator ite;
	for (ite = edges.begin(); ite != edges.end(); ++ite) {
		aux_local = kmp(ite->second, road);
		if (aux_local > local) {
			local = aux_local;
			edges_chosen.push_back(ite->first);
		}
	}

	//If the kmp algorithm doesn't find any edges
	if (edges_chosen.size() == 0) {
		map<int, int> aux;
		aux = researchRoadApproximate(graf, gv, road, priority, edges);

		sortEdgesByDistance(edges_chosen,edges,aux);

	} else {
		for (unsigned int i = 0; i < edges_chosen.size(); i++) {
			node = findLeftNode(graf, (edges_chosen[i] * 2));
			printPictureEmergency(gv, node);
			call.first = priority;
			call.second = node;
		}
		cout << "Exact research" << endl << endl;
	}

	//If the approximate algorithm finds more than one possible edge
	if (edges_chosen.size() > 1)
		choseRoad(graf, gv, edges, priority, call, hospitals,
				transports_positions);
	else{
		for (unsigned int i = 0; i < edges_chosen.size(); i++) {
			//Check if there is any transport or hospital in the left node of the road
			if (checkExistenceOfAppeal(graf, edges_chosen[i] * 2, hospitals,
					transports_positions))
				cout << endl
				<< "At the intersection between a street there is an emergency feature"
				<< endl;
		}

		//print the chosen road
		way.printChosenRoad(graf, gv, edges_chosen, priority, edges);
	}
	return edges_chosen;
}

map<int, int> EmergencyEvent::researchRoadApproximate(Graph<int> graf,
		GraphViewer *gv, string road, int priority, map<int, string> edges) {

	int aux_dist;
	map<int, int> dists;

	map<int, string>::iterator ite;
	for (ite = edges.begin(); ite != edges.end(); ++ite) {
		aux_dist = editDistance(road, ite->second);
		map<int, int>::iterator it = dists.begin();
		dists.insert(it, pair<int, int>(ite->first, aux_dist));
	}

	return dists;
}

void EmergencyEvent::choseRoad(Graph<int> graf, GraphViewer *gv,
		map<int, string> edges, int priority,
		pair<int, unsigned int> &call, vector<unsigned int> hospitals,
		vector<unsigned int> transports_positions) {

	string name;

	cout << endl << "Choose the road you want the emergency to occur: " << endl;
	getline(cin, name);


	researchRoadExact(graf, gv, name, priority, edges, call, hospitals,
			transports_positions);

}

void EmergencyEvent::calculateKmpTime(map<int, string> edges) {
	vector<string> roads;
	int random_edge;
	string random_road;
	auto t_start = std::chrono::system_clock::now();

	map<int, string>::iterator it;
	for (it = edges.begin(); it != edges.end(); ++it) {
		roads.push_back(it->second);
	}

	for (int i = 0; i < 1000; i++) {
		random_edge = rand() % roads.size();
		random_road = roads[random_edge];

		map<int, string>::iterator ite;
		for (ite = edges.begin(); ite != edges.end(); ++ite)
			kmp(ite->second, random_road);

	}
	auto endt_start = std::chrono::system_clock::now();
	cout << endl << "Time of kmp: ";
	cout
	<< (double) std::chrono::duration_cast<std::chrono::milliseconds>(
			endt_start - t_start).count();
	cout << " milliseconds" << endl;

}

void EmergencyEvent::calculateEditDistanceTime(map<int, string> edges) {
	vector<string> roads;
	int random_edge;
	string random_road;
	auto t_start = std::chrono::system_clock::now();

	map<int, string>::iterator it;
	for (it = edges.begin(); it != edges.end(); ++it) {
		roads.push_back(it->second);
	}

	for (int i = 0; i < 1000; i++) {
		random_edge = rand() % roads.size();
		random_road = roads[random_edge];

		map<int, string>::iterator ite;
		for (ite = edges.begin(); ite != edges.end(); ++ite)
			editDistance(random_road, ite->second);

	}
	auto endt_start = std::chrono::system_clock::now();
	cout << endl << "Time of edit distance:  ";
	cout
	<< (double) std::chrono::duration_cast<std::chrono::milliseconds>(
			endt_start - t_start).count();
	cout << " milliseconds" << endl;

}

void EmergencyEvent::calculateNaiveTime(map<int, string> edges) {

	vector<string> roads;
	int random_edge;
	string random_road;
	auto t_start = std::chrono::system_clock::now();

	map<int, string>::iterator it;
	for (it = edges.begin(); it != edges.end(); ++it) {
		roads.push_back(it->second);
	}

	for (int i = 0; i < 1000; i++) {
		random_edge = rand() % roads.size();
		random_road = roads[random_edge];

		map<int, string>::iterator ite;
		for (ite = edges.begin(); ite != edges.end(); ++ite)
			naiveStringMatch(ite->second, random_road);

	}
	auto endt_start = std::chrono::system_clock::now();
	cout << endl << "Time of naive:  ";
	cout
	<< (double) std::chrono::duration_cast<std::chrono::milliseconds>(
			endt_start - t_start).count();
	cout << " milliseconds" << endl;

}
