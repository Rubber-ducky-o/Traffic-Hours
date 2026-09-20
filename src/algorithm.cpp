#include <iostream>
#include "algorithm.h"



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
        std::swap(con_path[start],con_path[end]);
        start++;
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

double PI = 3.141592653589793;

double heuristic(Graph graph,double current,double goal)
{
    double R = 3959;

    auto start_c = graph[current].getcoords();
    auto goal_c = graph[goal].getcoords();

    double lat_c= radian_conversion(start_c.first);
    double long_c = radian_conversion(start_c.second);

    double lat_g = radian_conversion(goal_c.first);
    double long_g = radian_conversion(goal_c.second);


    double phi = lat_g - lat_c;
    double lambda = long_g - long_c;


    double a = intermediate_value(lat_c,lat_g,phi,lambda);
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