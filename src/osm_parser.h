#ifndef OSM_PARSER_H
#define OSM_PARSER_H

#include "Graph.h"
#include <string>


void readOSM(const std::string& filename,Graph& graph);
int parseSpeedLimit(const char* maxspeed);

#endif