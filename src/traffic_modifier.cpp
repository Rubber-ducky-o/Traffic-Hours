#include "traffic_modifier.h"
#include <iostream>
#include <cctype>
#include <fstream>
#include <sstream>
#include <limits>


std::vector<Station> loadStation(const std::string& filename)
{
    std::vector<Station> stations;

    std::ifstream stream(filename);

    if (!stream.is_open())
    {
        std::cerr << "Failed to open station file: " << filename << '\n';
        return stations;
    }

    stream.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

    std::string lines;

    while (std::getline(stream, lines))
    {
        Station station{};
        int column = 0;

        std::stringstream ss(lines);
        std::string value;

        while(std::getline(ss,value,'\t'))
        {
            if (column ==0 && !value.empty())
            {

                station.id = std::stoi(value);

            }
            if (column ==1 && !value.empty())
            {
                station.freeway = std::stoi(value);
            }
            if (column == 2) station.direction = value;

            if (column == 8 && !value.empty())
            {
                station.latitude = std::stod(value);
            }
            if (column == 9 && !value.empty())
            {
                station.longitude = std::stod(value);
            }
            if (column == 11) station.type = value;

            if (column == 12 && !value.empty())
            {
                station.lanes = std::stoi(value);
            }
            column++;
        }

        stations.push_back(station);
    }

    return stations;
}



void applyClosure(Graph& graph, const std::vector<int>& closure_path, const ClosureData& closure)
{
    if (closure.total_existing_lanes <= 0) return;

    if (closure.lanes_closed.size() == closure.total_existing_lanes)
    {
        for (size_t i =0; i+ 1 < closure_path.size(); ++i)
        {
            int source = closure_path[i];
            int dest = closure_path[i+1];

            const Vertex& source_vertex = graph[source];
            const Vertex& dest_vertex = graph[dest];

            std::string edge_direction = determinedirection(source_vertex.coordinates.first,source_vertex.coordinates.second,dest_vertex.coordinates.first,dest_vertex.coordinates.second);

            Edge* e = graph.getEdge(source,dest);

            std::cout << "Caltrans direction: " << closure.direction << " | Edge direction: " << edge_direction << '\n';

            if (edge_direction != closure.direction)
            {
                continue;
            }

            if (e!= nullptr)
            {
                e->travel_time = INF;
            }
        }
    }
    else if (closure.lanes_closed.size() < closure.total_existing_lanes && closure.lanes_closed.size() >= 1)
    {
        int closed_lanes = static_cast<int>(closure.lanes_closed.size());
        int open_lanes = closure.total_existing_lanes - closed_lanes;
        double open = static_cast<double>(open_lanes) / closure.total_existing_lanes;


        for (size_t i =0; i + 1 < closure_path.size(); ++i )
        {
            int source = closure_path[i];
            int dest = closure_path[i+1];

            const Vertex&  source_v = graph[source];
            const Vertex& dest_v = graph[dest];


            std::string edge_dir = determinedirection(source_v.coordinates.first,source_v.coordinates.second,dest_v.coordinates.first,dest_v.coordinates.second);

            std::cout << "Caltrans direction: " << closure.direction << " | Edge direction: " << edge_dir << '\n';
            if (edge_dir != closure.direction) continue;


            Edge *e = graph.getEdge(source,dest);


            if (e != nullptr)
            {
                e-> travel_time = e->base_travel_time / open;
            }
        }

    }

}


bool isClosureActive(const ClosureData& closure, long long departure_epoch)
{
    return (closure.start_epoch <= departure_epoch && closure.end_epoch >= departure_epoch);
}


void applyActiveClosures(Graph& graph,const std::vector<ClosureData>& closures,long long departure_epoch)
{
    for(const auto& closure : closures)
    {
        if(!isClosureActive(closure,departure_epoch)) continue;

        int start = findNearbyVertexRoute(graph,closure.begin_lat,closure.begin_lon,MAX_SNAP_DISTANCE,closure.route);
        int end = findNearbyVertexRoute(graph,closure.end_lat,closure.end_lon,MAX_SNAP_DISTANCE,closure.route);



        std::cout << "Closure route: " << closure.route << " | Direction: "<<closure.direction << " | start: " << start << " | end: " << end << '\n';

        if (start == -1 || end == -1) continue;

        auto pathway = DistancebasedDijkstra(graph,start,end);
        if (pathway.path.empty() || pathway.path[0] == -1) continue;

        applyClosure(graph,pathway.path,closure);

    }

}


std::string normalizeRoute(const std::string& route)
{
    std::string normal;

    for (char c : route)
    {
        if ( std::isdigit(static_cast<unsigned char>(c)))
        {
            normal += c;
        }

    }
    return normal;
}


int findNearbyVertexRoute(const Graph& graph,double latitude,double longitude,double max_distance, const std::string& route)
{
    std::string target = normalizeRoute(route);
    int closest_vertex = -1;
    double closest_distance = INF;

    for (const auto& vertex : graph.getData())
    {
        for (const auto& edge : vertex.adj)
        {
            if (normalizeRoute(edge.road_ref) == target)
            {
                auto coords = vertex.getcoords();

                double distance =haversineDistance(latitude,longitude,coords.first,coords.second);

                if (distance < closest_distance)
                {
                    closest_distance = distance;
                    closest_vertex = vertex.id;
                }

                break;
                }

        }
    }

    if (closest_vertex == -1)
    {
        return -1;
    }
    if (closest_distance > max_distance)
    {
        return -1;
    }
    return closest_vertex;

}


std::string determinedirection(double source_latitude,double source_longitude, double destination_latitude, double destination_longitude)
{
    double d_lat = destination_latitude - source_latitude;
    double d_lon = destination_longitude - source_longitude;

    if (std::abs(d_lat) > std::abs(d_lon))
    {
        if (d_lat > 0)
        return "North";
        if (d_lat < 0)
        {
            return "South";
        }
    }
    if (std::abs(d_lon) > std::abs(d_lat))
    {
        if (d_lon > 0)
        {
            return "East";
        }
        if (d_lon < 0)
        {
            return "West";
        }
    }
    return "Unknown";

}
