#include <cstdint>

#include <osmium/io/reader.hpp>
#include <osmium/io/xml_input.hpp>
#include <osmium/handler.hpp>
#include <osmium/visitor.hpp>
#include "Graph.h"
#include "algorithm.h"

#include <iostream>
#include <unordered_map>

int parseSpeedLimit(const char* maxspeed);

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
        const char* maxspeed = way.tags().get_value_by_key("maxspeed");
        int speed_limit = parseSpeedLimit(maxspeed);


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

            std::cout << "Source coords: "
                        << source_v.coordinates.first << ", "
                        << source_v.coordinates.second << '\n';

            std::cout << "Destination coords: "
                        << destination_v.coordinates.first << ", "
                        << destination_v.coordinates.second << '\n';


            double distance = haversineDistance(source_v.coordinates.first,source_v.coordinates.second,destination_v.coordinates.first,destination_v.coordinates.second);


            double travel_time = caltraveltime(distance,speed_limit);
            std::cout
            << "Edge " << source
            << " -> " << destination
            << " | distance: " << distance
            << " miles"
            << " | speed: "<< speed_limit
            << " mph"
            << " | time: "<< travel_time
            << " minutes"
            << std::endl;



            graph.addEdge(source,destination,distance,travel_time,speed_limit);
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