#ifndef ALGORITHM_H
#define ALGORITHM_H
#include "Graph.h"
#include <queue>
#include <vector>
#include <utility>

static constexpr double INF = std::numeric_limits<double>::infinity();

struct Pathway
{
    double distance;
    std::vector<int>path;

    Pathway(double dist) : distance(dist) {}
};

std::vector<int> reconstruct_pathway(std::vector<int> came_from,int start,int end);

Pathway dijkstra(const Graph& graph, int src,int end);

double heuristic(double longitude,double latitude);

Pathway a_star(const Graph& graph,int start, int end);


#endif