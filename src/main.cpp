#include <iostream>
#include <vector>
#include "parser.h"
#include "osm_parser.h"
#include "algorithm.h"
#include "traffic_modifier.h"

int main(){

    std::vector<Station> stations = loadStation("data/d07_text_meta_2026_08_25.txt");

    std::cout << "Station loaded: " << stations.size() << '\n';

    std::vector<TrafficObservation> observations = loadTraffic("data/d07_text_station_5min_2026_10_02.txt");

    std::cout << "Traffic observations loaded: " <<observations.size() <<'\n';

    HistoricalData historical = buildHistoricalData(observations);

    Graph graph;

    readOSM("sample_osm/i5_test.osm",graph);

    std::cout << "Graph contains " << graph.size() <<" vertices\n";

    std::string timestamp = "10/02/2026 00:00:00";

    applyHistoricalTraffic(graph,stations,historical,timestamp);

    std::cout << "Historical traffic applied\n";


    double start_lat = 33.8801;
    double start_lon = -118.021;

    double goal_lat = 33.8834;
    double goal_lon = -118.027;

    int start = findNearbyVertex(graph,start_lat,start_lon,MAX_SNAP_DISTANCE);

    int goal = findNearbyVertex(graph,goal_lat,goal_lon,MAX_SNAP_DISTANCE);

    if (start == -1 || goal ==  -1)
    {
        std::cerr << "Could not map start or goal onto graph.\n";
        return 1;
    }

    Pathway route = a_star(graph,start,goal);

    double total_distance = 0.0;

    for (size_t i =0; i+ 1 < route.path.size(); i++)
    {
        int src = route.path[i];
        int dest = route.path[i+1];
        Edge* edge = graph.getEdge(src,dest);

        if (edge !=nullptr)
        {
            total_distance += edge->distance;
        }

    }

    std::cout << "\nHistorical Traffic Route:\n";
    for(int vertex : route.path)
    {
        std::cout << vertex << " ";
    }

    std::cout << "\nTotal distance: "
            << total_distance
            << " miles\n";

    std::cout << "Travel time: "
            << route.travel_time
            << " minutes\n";


    std::vector<ClosureData> closures = grabbing_data();

    std::cout << "\nClosures received: "
            << closures.size()
            << '\n';

    if (closures.empty())
    {
        std::cout << "No closure data recieved.\n";
        return 0;
    }

    long long departure_epoch = closures[0].start_epoch;

    applyActiveClosures(graph,closures,departure_epoch);


    Pathway adjusted_route = a_star(graph,start,goal);

    total_distance = 0.0;

    for (size_t i =0; i+ 1 < adjusted_route.path.size(); i++)
    {
        int source = adjusted_route.path[i];
        int destination = adjusted_route.path[i+1];
        Edge * edge = graph.getEdge(source, destination);

        if (edge != nullptr)
        {
            total_distance += edge->distance;
        }
    }

    std::cout << "\nHistorical Traffic + Closures Route:\n";

    for (int vertex : adjusted_route.path)
    {
        std::cout << vertex << " ";
    }

    std::cout << "\nTotal distance: "
            << total_distance
            << " miles\n";

    std::cout << "Adjusted travel time: "
            << adjusted_route.travel_time
            << " minutes\n";

    return 0;
}