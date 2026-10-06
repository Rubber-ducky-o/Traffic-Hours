#ifndef TRAFFIC_H
#define TRAFFIC_H

#include <unordered_map>
#include <vector>
#include <string>

#include "Graph.h"
#include "parser.h"
#include "algorithm.h"

struct Station
{
    int id;
    int freeway;
    std::string direction;

    double latitude;
    double longitude;

    std::string type;
    int lanes;

};

struct TrafficObservation
{
    std::string timestamp;
    std::string type;

    int station_id;


    double speed;
    bool has_speed;

    double flow;
    double occupancy;

};

struct SpeedBucket
{
    double total_speed;
    int count;
};

using HistoricalData = std::unordered_map<int, std::vector<SpeedBucket>>;


int getTimeBucket(const std::string& timestamp);
HistoricalData buildHistoricalData(const std::vector<TrafficObservation>& observations);
double getHistoricalSpeed(const HistoricalData& data, int station_id, const std::string& timestamp);
int findStationVertex(const Graph& graph, const Station& station);
void applyHistoricalTraffic(Graph& graph, const std::vector<Station>& stations, const HistoricalData& historical,const std::string& timestamp);



std::vector<TrafficObservation> loadTraffic(const std::string& filename);
std::vector<Station> loadStation(const std::string& filename);




const double MAX_SNAP_DISTANCE = 0.1;

void applyClosure(Graph& graph,const std::vector<int>& closure_path, const ClosureData& closure);

bool isClosureActive(const ClosureData& closure, long long departure_epoch);

void applyActiveClosures(Graph& graph,const std::vector<ClosureData>& closures,long long departure_epoch);

std::string normalizeRoute(const std::string& route);

int findNearbyVertexRoute(const Graph& graph,double latitude,double longitude,double max_distance, const std::string& route);

std::string determinedirection(double source_latitude,double source_longitude, double destination_latitude,double destination_longitude);
#endif