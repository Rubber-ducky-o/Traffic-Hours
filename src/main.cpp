#include <iostream>
#include <vector>
#include "parser.h"
#include "osm_parser.h"
#include "algorithm.h"
#include "traffic_modifier.h"

int main(){

    std::cout << "STARTING MAIN" <<std::endl;
    Graph graph;

    readOSM("sample_osm/map.osm",graph);
    std::cout << "Graph contains" << graph.size() << " vertices" << std::endl;


    double start_lat = 33.944099;
    double start_lon = -118.396159;

    double goal_lat = 33.951500;
    double goal_lon = -118.398000;


    int start = findNearestVertex(graph, start_lat,start_lon);
    int goal = findNearestVertex(graph, goal_lat,goal_lon);

    std::cout << "Start vertex: " << start << std::endl;
    std::cout << "Goal vertex: " << goal << std::endl;

    Pathway route = a_star(graph,start,goal);

    std::cout << "A* route: ";
    for (int vertex : route.path)
    {
        std::cout << vertex << " ";

    }
    std::cout << std::endl;

    std::cout << "Travel time: " << route.travel_time << " minutes" << std::endl;


    std::vector<ClosureData> closures = grabbing_data();

    std::cout << "Parsed closures: " <<closures.size() << std::endl;

    const ClosureData& test_closure = closures[0];

    int closure_start = findNearestVertex(graph,test_closure.begin_lat,test_closure.begin_lon);
    int closure_end = findNearestVertex(graph,test_closure.end_lat,test_closure.end_lon);

    std::cout << "Closure maps to: " << closure_start << " -> " << closure_end << std::endl;

    Pathway closure_path = dijkstra(graph,closure_start,closure_end);

    std::cout << "Closure path: ";
    for (int vertex : closure_path.path)
    {
        std::cout << vertex << " ";
    }
    std::cout << std::endl;

    long long departure_epoch = test_closure.start_epoch;

    if(isClosureActive(test_closure, departure_epoch))
    {
        std::cout << "Closure is Active\n";
        applyClosure(graph,closure_path.path,test_closure);
    }
    else
    {
        std::cout << "Closure is Inactive\n";
    }

    Pathway adjusted_route = a_star(graph,start,goal);

    Edge* edge0 = graph.getEdge(0,1);
    Edge* edge1 = graph.getEdge(1,2);

    if (edge0 != nullptr)
    {
        std::cout << "0 -> 1 base: " << edge0->base_travel_time << " adjusted: " << edge0->travel_time <<std::endl;
    }
    if (edge1 != nullptr)
    {
        std::cout << "1 -> 2 base: " << edge1->base_travel_time << " adjusted: " << edge1->travel_time <<std::endl;
    }

    std::cout << "Route after closure: ";
    for (int vertex : adjusted_route.path)
    {
        std::cout <<vertex << " ";
    }

    std::cout << "\nAdjusted travel time: " << adjusted_route.travel_time << " minutes\n";


    std::cout << "ENDING MAIN"<< std::endl;

    return 0;
}