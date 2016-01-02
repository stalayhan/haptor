
#ifndef PATH_H
#define PATH_H


#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include <set>
#include <utility>
#include <limits> // for numeric_limits
#include <vector>

#define NUMBER_OF_DOORS_INDOOR 26
#define NUMBER_OF_DOORS_OUTDOOR 12

using namespace std;

typedef int vertex_t; /*integer tipinde vertex*/
typedef double weight_t;


class neighbour
{
public:
	vertex_t target;
	weight_t weight;
	neighbour(vertex_t arg_target, weight_t arg_weight)
		: target(arg_target), weight(arg_weight) { }
};
typedef vector< vector<neighbour> > adjacency_list_t;

class informations{
	public:
	// nodelar arasinda gidilecek yon bilgisini tutar.
	static int directionMatrixIndoor[NUMBER_OF_DOORS_INDOOR][NUMBER_OF_DOORS_INDOOR];
	static int directionMatrixOutdoor[NUMBER_OF_DOORS_OUTDOOR][NUMBER_OF_DOORS_OUTDOOR];

	// nodelarin merkez koodinatlarini tutar.
	static int coordinateMatrixIndoor[NUMBER_OF_DOORS_INDOOR][NUMBER_OF_DOORS_INDOOR];
	static int coordinateMatrixOutdoor[NUMBER_OF_DOORS_OUTDOOR][NUMBER_OF_DOORS_OUTDOOR];

	static adjacency_list_t adjacencyListIndoor;
	static adjacency_list_t adjacencyListOutdoor;
    static std::list<vertex_t> path;
};

void initializeDirectionMatrixIndoor();
void initializeDirectionMatrixOutdoor();
void initializeCoordinateMatrixOutdoor();
void initializeCoordinateMatrixIndoor();

std::list<vertex_t> initializeAdjacencyLists(bool isInside, int sourceNodeId, int destNodeId);
const weight_t max_weight = std::numeric_limits<double>::infinity();

#endif

