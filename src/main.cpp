#include <iostream>
#include <vector>
#include "parser.h"
#include "osm_parser.h"
#include "algorithm.h"
#include "traffic_modifier.h"

int main(){

    std::cout << "STARTING STATION TEST\n";

    std::vector<Station> stations = loadStation("data/d07_text_meta_2026_08_25.txt");

    std::cout << "\nStations loaded: " << stations.size() << '\n';
    for (size_t i = 0; i< stations.size() && i < 5; ++i)
    {
        const Station& station = stations[i];

        std::cout
            << station.id << " "
            << station.freeway << " "
            << station.direction << " "
            << station.latitude << " "
            << station.longitude << " "
            << station.type << " "
            << station.lanes << '\n';

    }


    std::cout << "ENDING STATION TEST\n";

    std::cout << "STARTING MAIN" <<std::endl;


    Graph graph;

    readOSM("sample_osm/socal-260924.osm.pbf",graph);

    for (const auto& vertex : graph.getData())
    {
        for (const auto& edge : vertex.adj)
        {
            if (!edge.road_ref.empty())
            {
                std::cout << "Road ref: " << edge.road_ref << std::endl;
            }
        }
    }

    std::cout << "Graph contains" << graph.size() << " vertices" << std::endl;


    double start_lat = 33.944099;
    double start_lon = -118.396159;

    double goal_lat = 33.951500;
    double goal_lon = -118.398000;


    int start = findNearestVertex(graph, start_lat,start_lon);
    int goal = findNearestVertex(graph, goal_lat,goal_lon);


    Pathway route = a_star(graph,start,goal);
    double total_distance = 0.0;

    for (size_t i=0; i + 1 < route.path.size(); i++)
    {
        int source = route.path[i];
        int destination = route.path[i+1];

        Edge* edge = graph.getEdge(source,destination);

        if (edge !=nullptr)
        {
            total_distance += edge->distance;
        }
    }
    for (int vertex : route.path)
    {
        std::cout<<vertex << " ";
    }

    std::cout <<"\nTotal distance: " << total_distance << " miles" << std::endl;
    std::cout << "\nTravel time: " << route.travel_time << " minutes" << std::endl;


    std::vector<ClosureData> closures = grabbing_data();

    std::cout << "Parsed closures: " <<closures.size() << std::endl;

    if (closures.empty())
    {
        std::cout << "No closures received.\n";
        return 0;
    }

    long long departure_epoch = closures[0].start_epoch;

    applyActiveClosures(graph,closures,departure_epoch);


    Pathway new_route = a_star(graph,start,goal);

    std::cout << "\nAdjusted route:\n";
    total_distance =0.0;

    for (size_t i=0; i + 1 < new_route.path.size(); i++)
    {
        int source = new_route.path[i];
        int destination = new_route.path[i+1];

        Edge* edge = graph.getEdge(source,destination);

        if (edge !=nullptr)
        {
            total_distance += edge->distance;
        }
    }
    for (int vertex : new_route.path)
    {
        std::cout << vertex << " ";
    }

    std::cout <<"\nTotal distance: " << total_distance << " miles" << std::endl;
    std::cout << "\nAdjusted travel time: " << new_route.travel_time << " minutes\n";


    std::cout << "ENDING MAIN"<< std::endl;

    return 0;
}