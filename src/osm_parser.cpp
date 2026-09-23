#include <cstdint>

#include <osmium/io/reader.hpp>
#include <osmium/io/xml_input.hpp>
#include <osmium/handler.hpp>
#include <osmium/visitor.hpp>
#include "Graph.h"
#include "algorithm.h"

#include <iostream>
#include <unordered_map>


enum roadwayDirection
{
    Twoway,
    Forward,
    Reverse
};

int parseSpeedLimit(const char* maxspeed);
bool isitDrivable(const char* highway);
int estimateSpeed(const char* highway);

struct OSMHandler : public osmium::handler::Handler
{
    std::unordered_map<long long, int> osm_to_graph;
    Graph& graph;

    OSMHandler(Graph& g)
        : graph(g)
    {
    }

    void node(const osmium::Node& node)
    {
        if (node.location().valid())
        {
            int graph_id = graph.addVertex(
            std::to_string(node.id()),
            node.location().lat(),
            node.location().lon()
            );

            osm_to_graph[node.id()] = graph_id;

        }
    }
    void way(const osmium::Way& way)
    {

        const auto& nodes = way.nodes();

        const char* highway = way.tags().get_value_by_key("highway");
        const char* maxspeed = way.tags().get_value_by_key("maxspeed");


        if(highway == nullptr) return;
        if (!isitDrivable(highway)) return;


        int speed_limit = parseSpeedLimit(maxspeed);

        if (speed_limit == -1){
            speed_limit = estimateSpeed(highway);
        }

        if (speed_limit <= 0)
        {
            return;
        }


        const char* oneway = way.tags().get_value_by_key("oneway");
        roadwayDirection direction = Twoway;


        if (oneway != nullptr)
        {
            std::string oneway_str(oneway);

            if (oneway_str == "yes" || oneway_str == "1" || oneway_str == "true")
            {
                direction = Forward;
            }
            else if (oneway_str == "-1")
            {
                direction = Reverse;
            }
        }



        for (size_t i =0; i + 1 < nodes.size(); i++)
        {
            long long osm_source = nodes[i].ref();
            long long osm_destination = nodes[i + 1].ref();

            auto source_iter = osm_to_graph.find(osm_source);
            auto destination_iter = osm_to_graph.find(osm_destination);

            if (source_iter == osm_to_graph.end() || destination_iter == osm_to_graph.end())
            {
                continue;
            }

            int source = source_iter->second;
            int destination = destination_iter->second;

            const Vertex& source_v = graph[source];
            const Vertex& destination_v = graph[destination];


            double distance = haversineDistance(source_v.coordinates.first,source_v.coordinates.second,destination_v.coordinates.first,destination_v.coordinates.second);

            double travel_time = caltraveltime(distance,speed_limit);


            switch(direction)
            {
                case Forward:
                    std::cout
                    << "FORWARD: "
                    << source << "->" <<destination
                    << " | " << distance << " miles"
                    << " | " << speed_limit << " mph"
                    << " | " << travel_time << " min\n";

                    graph.addEdge(source,destination,distance,travel_time,speed_limit);
                    break;

                case Reverse:
                    std::cout
                    << "REVERSE: "
                    << destination << "->" <<source
                    << " | " << distance << " miles"
                    << " | " << speed_limit << " mph"
                    << " | " << travel_time << " min\n";

                    graph.addEdge(destination,source,distance,travel_time,speed_limit);
                    break;

                case Twoway:
                    std::cout
                    << "TWOWAY: "
                    << source << " <-> " <<destination
                    << " | " << distance << " miles"
                    << " | " << speed_limit << " mph"
                    << " | " << travel_time << "min\n";

                    graph.addEdge(source,destination,distance,travel_time,speed_limit);
                    graph.addEdge(destination,source,distance,travel_time,speed_limit);
                    break;
            }

        }


    }
};

void readOSM(const std::string& filename,Graph& graph)
{
    osmium::io::Reader reader{
        filename,
        osmium::osm_entity_bits::node |
        osmium::osm_entity_bits::way
    };

    OSMHandler handler(graph);

    osmium::apply(reader,handler);

    reader.close();

}

int parseSpeedLimit(const char* maxspeed)
{
    if (maxspeed == nullptr) return -1;

    try
    {
        return std::stoi(maxspeed);

    }
    catch(const std::invalid_argument&)
    {
        return -1;

    }
    catch(const std::out_of_range&)
    {
        return -1;
    }
}

bool isitDrivable(const char* highway)
{
    std::string highway_str(highway);

    return (highway_str == "motorway"
        || highway_str == "trunk"
        || highway_str == "primary"
        || highway_str == "secondary"
        || highway_str == "tertiary"
        || highway_str == "residential"
        || highway_str == "service"
    );

}

int estimateSpeed(const char* highway)
{
    std::string road_type(highway);

    if (road_type == "motorway")
        return 65;
    if (road_type == "trunk")
        return 55;
    if (road_type == "primary")
        return 45;
    if (road_type == "secondary")
        return 35;
    if (road_type == "tertiary")
        return 35;
    if (road_type == "residential")
        return 25;
    if (road_type == "service")
        return 30;
    return -1;

}