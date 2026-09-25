#include <iostream>
#include "algorithm.h"
#include "parser.h"



int findNearestVertex(const Graph& graph, double latitude, double longitude)
{
    int closest_vertex = -1;
    double closest_distance = INF;

    for (const auto& vertex : graph.getData())
    {
        double dist = haversineDistance(latitude,longitude,vertex.coordinates.first,vertex.coordinates.second);
        if (dist < closest_distance)
        {
            closest_distance = dist;
            closest_vertex = vertex.id;
        }

    }

    return closest_vertex;
}

int findNearbyVertex(const Graph& graph, double latitude, double longitude, double max_distance)
{
    int nearest_vertex = findNearestVertex(graph,latitude,longitude);

    if (nearest_vertex == -1) return -1;

    auto vertex_coords = graph[nearest_vertex].getcoords();

    double distance = haversineDistance(latitude,longitude,vertex_coords.first,vertex_coords.second);

    if (distance > max_distance) return -1;

    return nearest_vertex;


}


std::vector<int> reconstruct_pathway(std::vector<int> came_from,int start,int goal){
    int val = goal;

    std::vector<int>con_path;
    con_path.push_back(goal);

    while(start != val)
    {
        con_path.push_back(came_from[val]);
        val = came_from[val];
    }
    int starts = 0;
    int end = con_path.size() -1;

    while(starts < end)
    {
        std::swap(con_path[starts],con_path[end]);
        starts++;
        end--;
    }

    return con_path;
}



Pathway dijkstra(const Graph& graph, int src, int goal)
{
    int size = static_cast<int>(graph.size());

    if (src < 0 || src >= size || goal < 0 || goal >= size)
    {
        Pathway pth(-1.0);
        pth.path.push_back(-1);
        return pth;
    }


    std::vector<double> dist(size,INF);
    std::vector<int> prev(size,-1);

    //{DISTANCE, VERTEX}
    std::priority_queue<std::pair<double,int>,
    std::vector<std::pair<double,int>>,
    std::greater<std::pair<double,int>>> queue;

    dist[src] = 0.0;
    queue.push({0.0,src});

    while (!queue.empty())
    {
        std::pair<double,int> u = queue.top();
        queue.pop();

        if (u.first > dist[u.second])
        {
            continue;
        }

        if (u.second == goal)
        {
            break;
        }




        std::vector<Edge> edges = graph.getNeighbors(u.second);

        for (const auto& edge : edges)
        {
            int v = edge.destination;
            double total_dist = u.first + edge.travel_time;

            if (total_dist < dist[v])
            {
                prev[v] = u.second;
                dist[v] = total_dist;

                queue.push({total_dist,v});
            }
        }


    }
    Pathway result(-1.0);
    if (dist[goal] == INF )
    {
        result.path.push_back(-1);
        return result;
    }


    result.travel_time = dist[goal];
    result.path = reconstruct_pathway(prev,src,goal);

    return result;

}

const double PI = 3.141592653589793;
const double MAX_SPEED_MPH = 90.0;
double heuristic(const Graph& graph,double current,double goal)
{
    auto start_c = graph[current].getcoords();
    auto goal_c = graph[goal].getcoords();

    double distance = haversineDistance(start_c.first,start_c.second,
    goal_c.first,goal_c.second);

    return (distance / MAX_SPEED_MPH) * 60.0;

}
double haversineDistance(double lat1,double lon1,double lat2,double lon2)
{
    double R = 3959;

    lat1 = radian_conversion(lat1);
    lon1 = radian_conversion(lon1);
    lat2 = radian_conversion(lat2);
    lon2 = radian_conversion(lon2);

    double phi = lat2 - lat1;
    double lambda = lon2 - lon1;

    double a = intermediate_value(lat1,lat2,phi,lambda);
    double c = central_angle(a);

    return R * c;
}

double radian_conversion(double coord)
{
    return PI * coord / 180.0;
}

double intermediate_value(double lat1,double lat2,double phi, double lambda)
{
    return haversine(phi) + std::cos(lat1) * std::cos(lat2) * haversine(lambda);
}

double haversine(double theta)
{
    return std::pow(std::sin(theta / 2),2);
}

double central_angle(double a)
{
    return 2 * std::atan2(std::sqrt(a),std::sqrt(1-a));
}
double caltraveltime(double distance, int speed_limit)
{
    if (speed_limit <= 0)
    {
        return -1.0;
    }

    return (distance / speed_limit) * 60.0;
}


Pathway a_star(const Graph& graph, int start, int goal)
{
    int size = static_cast<int>(graph.size());

    if (start < 0 || start >= size || goal < 0 || goal >= size)
    {
        Pathway pth(-1.0);
        pth.path.push_back(-1);
        return pth;
    }

    std::priority_queue<std::pair<double,int>,
    std::vector<std::pair<double,int>>,
    std::greater<std::pair<double,int>>> frontier;

    std::vector<double> cost_so_far(size,INF);
    std::vector<int> came_from(size,-1);



    cost_so_far[start] = 0;
    double priority = cost_so_far[start] + heuristic(graph,start,goal);


    frontier.push({priority,start});


    while (!frontier.empty())
    {
        auto current = frontier.top();
        frontier.pop();

        double priority = current.first;
        int vertex = current.second;

        if (vertex == goal)
        {
            break;
        }
        std::vector<Edge> neighbors = graph.getNeighbors(vertex);

        for (const auto& edge : neighbors)
        {
            int next = edge.destination;

            double new_cost = cost_so_far[vertex] + edge.travel_time;

            if (new_cost < cost_so_far[next])
            {
                cost_so_far[next] = new_cost;

                came_from[next] = vertex;

                double priority = new_cost + heuristic(graph,next,goal);

                frontier.push({priority,next});
            }

        }


    }
    Pathway result(-1.0);

    if (cost_so_far[goal] == INF )
    {
        result.path.push_back(-1);
        return result;
    }

    result.travel_time = cost_so_far[goal];
    result.path = reconstruct_pathway(came_from,start,goal);

    return result;

}

Pathway DistancebasedDijkstra(const Graph& graph, int src, int goal)
{
    int size = static_cast<int>(graph.size());

    if (src < 0 || src >= size || goal < 0 || goal >= size)
    {
        Pathway pth(-1.0);
        pth.path.push_back(-1);
        return pth;
    }


    std::vector<double> dist(size,INF);
    std::vector<int> prev(size,-1);

    //{DISTANCE, VERTEX}
    std::priority_queue<std::pair<double,int>,
    std::vector<std::pair<double,int>>,
    std::greater<std::pair<double,int>>> queue;

    dist[src] = 0.0;
    queue.push({0.0,src});

    while (!queue.empty())
    {
        std::pair<double,int> u = queue.top();
        queue.pop();

        if (u.first > dist[u.second])
        {
            continue;
        }

        if (u.second == goal)
        {
            break;
        }




        std::vector<Edge> edges = graph.getNeighbors(u.second);

        for (const auto& edge : edges)
        {
            int v = edge.destination;
            double total_dist = u.first + edge.distance;

            if (total_dist < dist[v])
            {
                prev[v] = u.second;
                dist[v] = total_dist;

                queue.push({total_dist,v});
            }
        }


    }
    Pathway result(-1.0);
    if (dist[goal] == INF )
    {
        result.path.push_back(-1);
        return result;
    }


    result.travel_time = -1;
    result.path = reconstruct_pathway(prev,src,goal);

    return result;

}
