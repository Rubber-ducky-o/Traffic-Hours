#ifndef ALGORITHM_H
#define ALGORITHM_H
#include "Graph.h"
#include <queue>
#include <vector>
#include <utility>
#include <cmath>


static constexpr double INF = std::numeric_limits<double>::infinity();

struct Pathway
{
    double travel_time;
    std::vector<int>path;

    Pathway(double dist) : travel_time(dist) {}
};

int findNearestVertex(const Graph& graph, double latitude, double longitude);

int findNearbyVertex(const Graph& graph, double latitude, double longitude, double max_distance);


std::vector<int> reconstruct_pathway(std::vector<int> came_from,int start,int end);

Pathway dijkstra(const Graph& graph, int src,int end);

double heuristic(const Graph& graph,double current,double goal);

double haversineDistance(double lat1,double lon1,double lat2,double lon2);

double radian_conversion(double coord);

double intermediate_value(double lat1,double lat2,double phi,double lambda);

double haversine(double theta);

double central_angle(double a);

double caltraveltime(double distance, int speed_limit);


Pathway a_star(const Graph& graph,int start, int end);

Pathway DistancebasedDijkstra(const Graph& graph, int src, int goal);


#endif