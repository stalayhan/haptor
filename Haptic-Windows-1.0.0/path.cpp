#include "path.h"

adjacency_list_t informations::adjacencyListIndoor(NUMBER_OF_DOORS_INDOOR);
adjacency_list_t informations::adjacencyListOutdoor(NUMBER_OF_DOORS_INDOOR);
int informations::directionMatrixIndoor[NUMBER_OF_DOORS_INDOOR][NUMBER_OF_DOORS_INDOOR]={0};
int informations::directionMatrixOutdoor[NUMBER_OF_DOORS_OUTDOOR][NUMBER_OF_DOORS_OUTDOOR]={0};
int informations::coordinateMatrixIndoor[NUMBER_OF_DOORS_INDOOR][NUMBER_OF_DOORS_INDOOR]={0};
int informations::coordinateMatrixOutdoor[NUMBER_OF_DOORS_OUTDOOR][NUMBER_OF_DOORS_OUTDOOR]={0};

void DijkstraComputePaths(vertex_t source,
	const adjacency_list_t &adjacency_list,
	vector<weight_t> &min_distance,
	vector<vertex_t> &previous)
{
	int n = adjacency_list.size();
	min_distance.clear();
	min_distance.resize(n, max_weight);
	min_distance[source] = 0;
	previous.clear();
	previous.resize(n, -1);
	set<pair<weight_t, vertex_t> > vertex_queue;
	vertex_queue.insert(make_pair(min_distance[source], source));

	while (!vertex_queue.empty())
	{
		weight_t dist = vertex_queue.begin()->first;
		vertex_t u = vertex_queue.begin()->second;
		vertex_queue.erase(vertex_queue.begin());

		// Visit each edge exiting u
		const vector<neighbour> &neighbors = adjacency_list[u];
		for (vector<neighbour>::const_iterator neighbor_iter = neighbors.begin();
			neighbor_iter != neighbors.end();
			neighbor_iter++)
		{
			vertex_t v = neighbor_iter->target;
			weight_t weight = neighbor_iter->weight;
			weight_t distance_through_u = dist + weight;
			if (distance_through_u < min_distance[v]) {
				vertex_queue.erase(make_pair(min_distance[v], v));

				min_distance[v] = distance_through_u;
				previous[v] = u;
				vertex_queue.insert(make_pair(min_distance[v], v));
			}
		}
	}
}

list<vertex_t> DijkstraGetShortestPathTo(
	vertex_t vertex, const vector<vertex_t> &previous)
{
	list<vertex_t> path;
	for (; vertex != -1; vertex = previous[vertex])
		path.push_front(vertex);
	return path;
}


int initializeAdjacencyLists(bool isInside, int sourceNodeId, int destNodeId)
{
	/*****************************************IC MEKAN************************************/

	// remember to insert edges both ways for an undirected graph

	// 0 = A Robotik
	informations::adjacencyListIndoor[0].push_back(neighbour(1, 5));  // Robotik-Z02 = 3
	informations::adjacencyListIndoor[0].push_back(neighbour(10, 5)); // Robotik-X4 = 2
	// 1 = B Z02
	informations::adjacencyListIndoor[1].push_back(neighbour(0, 5)); // Z02-Robotik = 3
	informations::adjacencyListIndoor[1].push_back(neighbour(2, 5)); // Z02-arkaKapý = 3
	// 2 = C arkaKapi
	informations::adjacencyListIndoor[2].push_back(neighbour(1, 5)); // arkaKapi-Z04 = 2
	informations::adjacencyListIndoor[2].push_back(neighbour(3, 5)); // arkaKapi-Z02 = 3
	// 2 = D Z04
	informations::adjacencyListIndoor[3].push_back(neighbour(1, 5)); // Z04-arkaKapi = 2
	informations::adjacencyListIndoor[3].push_back(neighbour(3, 5)); // Z04-Z05 = 4
	// 3 = E Z05
	informations::adjacencyListIndoor[4].push_back(neighbour(2, 5)); // Z05-Z04 = 4
	informations::adjacencyListIndoor[4].push_back(neighbour(4, 5)); // Z05-X1 = 1
	// 3 = F Z05-Z10 arasýndaki köþe X1
	informations::adjacencyListIndoor[5].push_back(neighbour(2, 5)); // X1-Z05 = 1
	informations::adjacencyListIndoor[5].push_back(neighbour(4, 5)); // X1-Z10 = 3
	// 4 = G Z10
	informations::adjacencyListIndoor[6].push_back(neighbour(3, 5)); // Z10-X1 = 3
	informations::adjacencyListIndoor[6].push_back(neighbour(5, 5)); // Z10-X2 = 1
	// 4 = H Z10-Mikro arasi duz köse X2
	informations::adjacencyListIndoor[7].push_back(neighbour(3, 5)); // X2-Z10 = 1
	informations::adjacencyListIndoor[7].push_back(neighbour(5, 5)); // X2-X3 = 2
	// 5 = G Z10-Mikro arasi yan kose X3
	informations::adjacencyListIndoor[8].push_back(neighbour(4, 5)); // X3-X2 = 2
	informations::adjacencyListIndoor[8].push_back(neighbour(6, 5)); // X3-MikroLab = 2
	// 5 = H MikroLab
	informations::adjacencyListIndoor[9].push_back(neighbour(4, 5));  // MikroLab-X3 = 2
	informations::adjacencyListIndoor[9].push_back(neighbour(6, 5)); // MikroLab-WcKiz = 2
	// 10 = I WcKiz
	informations::adjacencyListIndoor[10].push_back(neighbour(9, 5));  // WcKýz-MikroLab = 2
	informations::adjacencyListIndoor[10].push_back(neighbour(0, 5)); // WcKýz-DevreLab = 0

	/*****************************************DIS MEKAN************************************/
	// 0 = BilMuh OnKapi Sol Kose
	informations::adjacencyListOutdoor[0].push_back(neighbour(1, 5));
	informations::adjacencyListOutdoor[0].push_back(neighbour(7, 5));
	informations::adjacencyListOutdoor[0].push_back(neighbour(15, 20));
	// 1 = Bil Muh On kapı
	informations::adjacencyListOutdoor[1].push_back(neighbour(0, 5));
	informations::adjacencyListOutdoor[1].push_back(neighbour(2, 5));
	// 2 = Bil Muh On kapı Sag kose
	informations::adjacencyListOutdoor[2].push_back(neighbour(1, 5));
	informations::adjacencyListOutdoor[2].push_back(neighbour(8, 10));
	informations::adjacencyListOutdoor[2].push_back(neighbour(3, 5));
	// 3 = Bil muh Sag Taraf
	informations::adjacencyListOutdoor[3].push_back(neighbour(2, 5));
	informations::adjacencyListOutdoor[3].push_back(neighbour(4, 5));
	// 4 =
	informations::adjacencyListOutdoor[4].push_back(neighbour(3, 5));
	informations::adjacencyListOutdoor[4].push_back(neighbour(5, 5));
	// 5 = Bil Muh Arka Taraf
	informations::adjacencyListOutdoor[5].push_back(neighbour(4, 5));
	informations::adjacencyListOutdoor[5].push_back(neighbour(6, 5));
	// 6 =
	informations::adjacencyListOutdoor[6].push_back(neighbour(5, 5));
	informations::adjacencyListOutdoor[6].push_back(neighbour(7, 5));
	// 7 = Bil muh sol taraf
	informations::adjacencyListOutdoor[7].push_back(neighbour(0, 5));
	informations::adjacencyListOutdoor[7].push_back(neighbour(6, 5));
	// 8 = Bil muh soldaki yol
	informations::adjacencyListOutdoor[8].push_back(neighbour(2, 10));
	informations::adjacencyListOutdoor[8].push_back(neighbour(9, 10));
	// 9 =
	informations::adjacencyListOutdoor[9].push_back(neighbour(8, 10));
	informations::adjacencyListOutdoor[9].push_back(neighbour(10, 20));
	// 10 = kütüphaneye giden uzun yol
	informations::adjacencyListOutdoor[10].push_back(neighbour(9, 20));
	informations::adjacencyListOutdoor[10].push_back(neighbour(11, 20));
	// 11 = kütüphaneden önceki köşe
	informations::adjacencyListOutdoor[11].push_back(neighbour(12, 10));
	informations::adjacencyListOutdoor[11].push_back(neighbour(17, 20));
	// 12 = kütüphane
	informations::adjacencyListOutdoor[12].push_back(neighbour(11, 10));
	informations::adjacencyListOutdoor[12].push_back(neighbour(13, 10));
	// 13 = biyoloji yolu
	informations::adjacencyListOutdoor[13].push_back(neighbour(12, 10));
	informations::adjacencyListOutdoor[13].push_back(neighbour(14, 10));
	// 14 = biyoloji - kimya
	informations::adjacencyListOutdoor[14].push_back(neighbour(13, 10));
	// 15 = Bil Müh sağdaki uzun yol
	informations::adjacencyListOutdoor[15].push_back(neighbour(0, 20));
	informations::adjacencyListOutdoor[15].push_back(neighbour(16, 20));
	// 16 =
	informations::adjacencyListOutdoor[16].push_back(neighbour(15, 20));
	informations::adjacencyListOutdoor[16].push_back(neighbour(17, 10));
	informations::adjacencyListOutdoor[16].push_back(neighbour(18, 10));
	// 17 =
	informations::adjacencyListOutdoor[17].push_back(neighbour(16, 20));
	informations::adjacencyListOutdoor[17].push_back(neighbour(11, 20));
	// 18 =
	informations::adjacencyListOutdoor[18].push_back(neighbour(16, 10));
	informations::adjacencyListOutdoor[18].push_back(neighbour(19, 10));
	// 19 =
	informations::adjacencyListOutdoor[19].push_back(neighbour(18, 10));
	/**************************************************************************************/
	vector<weight_t> min_distance;
	vector<vertex_t> previous;

	// Inside
	if (isInside) {
		cout << "Su anda bulunulan node : " << sourceNodeId << endl;
		cout << "Gidilecek node : " << destNodeId << endl;

		DijkstraComputePaths(sourceNodeId, informations::adjacencyListIndoor, min_distance, previous);
		cout << "Distance from " << sourceNodeId << " to " << destNodeId << "  ->  " << min_distance[destNodeId] << endl;
		list<vertex_t> path = DijkstraGetShortestPathTo(destNodeId, previous);
		cout << "Path : ";
		copy(path.begin(), path.end(), ostream_iterator<vertex_t>(cout, " "));
		cout << endl;
		list<vertex_t>::iterator it2 = path.begin();
		it2++;
		for (list<vertex_t>::iterator it = path.begin(); it != path.end(); ++it) {
			if (it == --path.end())
				break;
			else{
				cout << informations::directionMatrixIndoor[*it][*it2] << " - ";
				it2++;
			}
		}
	}
	// Outside
	else{
		cout << "Su anda bulunulan node : " << sourceNodeId << endl;
		cout << "Gidilecek node : " << destNodeId << endl;

		DijkstraComputePaths(sourceNodeId, informations::adjacencyListOutdoor, min_distance, previous);
		cout << "Distance from " << sourceNodeId << " to " << destNodeId << "  ->  " << min_distance[destNodeId] << endl;
		list<vertex_t> path = DijkstraGetShortestPathTo(destNodeId, previous);
		cout << "Path : ";
		copy(path.begin(), path.end(), ostream_iterator<vertex_t>(cout, " "));
		cout << endl;
		list<vertex_t>::iterator it2 = path.begin();
		it2++;
		for (list<vertex_t>::iterator it = path.begin(); it != path.end(); ++it) {
			if (it == --path.end())
				break;
			else{
				cout << informations::directionMatrixOutdoor[*it][*it2] << " - ";
				it2++;
			}
		}
	}
	return 0;
}

void initializeDirectionMatrixIndoor(){

	// directionMatrixIndoor initialization with zeros
	for (int i = 0; i < NUMBER_OF_DOORS_INDOOR; ++i){
		for (int j = 0; j < NUMBER_OF_DOORS_INDOOR; ++j){
			informations::directionMatrixIndoor[i][j] = 0;
		}
	}
	// directionMatrixIndoor initialization
	informations::directionMatrixIndoor[0][1] = 4;
	informations::directionMatrixIndoor[0][10] = 1;
	informations::directionMatrixIndoor[1][2] = 4;
	informations::directionMatrixIndoor[1][0] = 3;
	informations::directionMatrixIndoor[2][3] = 4;
	informations::directionMatrixIndoor[2][1] = 3;
	informations::directionMatrixIndoor[3][4] = 1;
	informations::directionMatrixIndoor[3][2] = 3;
	informations::directionMatrixIndoor[4][5] = 1;
	informations::directionMatrixIndoor[4][3] = 2;
	informations::directionMatrixIndoor[5][6] = 1;
	informations::directionMatrixIndoor[5][4] = 2;
	informations::directionMatrixIndoor[6][7] = 3;
	informations::directionMatrixIndoor[6][5] = 2;
	informations::directionMatrixIndoor[7][8] = 3;
	informations::directionMatrixIndoor[7][6] = 4;
	informations::directionMatrixIndoor[8][9] = 2;
	informations::directionMatrixIndoor[8][7] = 4;
	informations::directionMatrixIndoor[9][10] = 2;
	informations::directionMatrixIndoor[9][8] = 1;
	informations::directionMatrixIndoor[10][0] = 2;
	informations::directionMatrixIndoor[10][9] = 1;

	/*for (int i = 0; i < numberOfNodesIndoor; ++i){
	for (int j = 0; j < numberOfNodesIndoor; ++j){
	cout << informations::directionMatrixIndoor[i][j];
	}
	}*/
}

void initializeDirectionMatrixOutdoor(){

	// directionMatrixOutdoor initialization with zeros
	for (int i = 0; i < NUMBER_OF_DOORS_OUTDOOR; ++i){
		for (int j = 0; j < NUMBER_OF_DOORS_OUTDOOR; ++j){
			informations::directionMatrixOutdoor[i][j] = 0;

		}
	}
	// directionMatrixOutdoor initialization
	informations::directionMatrixOutdoor[0][1] = 4;
	informations::directionMatrixOutdoor[1][0] = 3;
	informations::directionMatrixOutdoor[1][2] = 1;
	informations::directionMatrixOutdoor[2][1] = 2;
	informations::directionMatrixOutdoor[2][3] = 4;
	informations::directionMatrixOutdoor[3][2] = 3;
	informations::directionMatrixOutdoor[3][4] = 1;
	informations::directionMatrixOutdoor[3][5] = 4;
	informations::directionMatrixOutdoor[4][3] = 2;
	informations::directionMatrixOutdoor[5][3] = 3;
	informations::directionMatrixOutdoor[5][6] = 1;
	informations::directionMatrixOutdoor[5][9] = 4;
	informations::directionMatrixOutdoor[6][5] = 2;
	informations::directionMatrixOutdoor[6][7] = 4;
	informations::directionMatrixOutdoor[6][8] = 3;
	informations::directionMatrixOutdoor[7][6] = 3;
	informations::directionMatrixOutdoor[8][6] = 4;
	informations::directionMatrixOutdoor[9][5] = 3;
	informations::directionMatrixOutdoor[9][10] = 1;
	informations::directionMatrixOutdoor[10][11] = 4;
	informations::directionMatrixOutdoor[10][9] = 2;
	informations::directionMatrixOutdoor[11][10] = 3;

}

void initializeCoordinateMatrixOutdoor(){

	informations::coordinateMatrixOutdoor[0][0] = 40.808004; // Bil muh x : 40.808004
	informations::coordinateMatrixOutdoor[0][1] = 29.356379; // Bil muh y : 29.356379
	informations::coordinateMatrixOutdoor[1][0] = 40.807922; // Bil muh onu x : 40.807922
	informations::coordinateMatrixOutdoor[1][1] = 29.356472; // Bil muh onu y : 29.356472
	informations::coordinateMatrixOutdoor[2][0] = 40.807429; // Uzun yolun basi x : 40.807429
	informations::coordinateMatrixOutdoor[2][0] = 29.356290; // Uzun yolun basi y : 29.356290
	informations::coordinateMatrixOutdoor[3][0] = 40.806910; // Kutuphaneye dönmeden onceki node x : 40.806910
	informations::coordinateMatrixOutdoor[3][1] = 29.359170; // Kutuphaneye dönmeden onceki node y : 29.359170
	informations::coordinateMatrixOutdoor[4][0] = 40.806593; // Kutuphane x : 40.806593
	informations::coordinateMatrixOutdoor[4][1] = 29.359063; // Kutuphane y : 29.359063
	informations::coordinateMatrixOutdoor[5][0] = 40.806865; // Biyolojiye donmeden onceki node x : 40.806865
	informations::coordinateMatrixOutdoor[5][1] = 29.359460; // Biyolojiye donmeden onceki node y : 359460
	informations::coordinateMatrixOutdoor[6][0] = 40.805635; // Biyoloji Kimya arasindaki node x : 40.805635
	informations::coordinateMatrixOutdoor[6][1] = 29.359079; // Biyoloji Kimya arasindaki node x : 29.359079
	informations::coordinateMatrixOutdoor[7][0] = 40.805598; // Biyoloji x : 40.805598
	informations::coordinateMatrixOutdoor[7][1] = 29.359337; // Biyoloji y : 29.359337
	informations::coordinateMatrixOutdoor[8][0] = 40.805643; // Kimya muh x : 40.805643
	informations::coordinateMatrixOutdoor[8][1] = 29.358983; // Kimya muh y : 29.358983
	informations::coordinateMatrixOutdoor[9][0] = 40.806341; // Cevreye donmeden onceki node x : 40.806341
	informations::coordinateMatrixOutdoor[9][1] = 29.362234; // Cevreye donmeden onceki node y : 29.362234
	informations::coordinateMatrixOutdoor[10][0] = 40.805886; // Cevrenin onundeki node x : 40.805886
	informations::coordinateMatrixOutdoor[10][1] = 29.362067; // Cevrenin onundeki node y : 29.362067
	informations::coordinateMatrixOutdoor[11][0] = 40.805878; // Cevre x : 40.805878
	informations::coordinateMatrixOutdoor[11][1] = 29.362121; // Cevre y : 29.362121
}