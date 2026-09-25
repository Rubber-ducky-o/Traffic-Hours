#ifndef TRAFFIC_H
#define TRAFFIC_H

#include <vector>

#include "Graph.h"
#include "parser.h"
#include "algorithm.h"


const double MAX_SNAP_DISTANCE = 0.1;

void applyClosure(Graph& graph,const std::vector<int>& closure_path, const ClosureData& closure);
bool isClosureActive(const ClosureData& closure, long long departure_epoch);
void applyActiveClosures(Graph& graph,const std::vector<ClosureData>& closures,long long departure_epoch);


#endif