#ifndef TRAFFIC_H
#define TRAFFIC_H

#include <vector>

#include "Graph.h"
#include "parser.h"
#include "algorithm.h"

void applyClosure(Graph& graph,const std::vector<int>& closure_path, const ClosureData& closure);
bool isClosureActive(const ClosureData& closure, long long departure_epoch);



#endif