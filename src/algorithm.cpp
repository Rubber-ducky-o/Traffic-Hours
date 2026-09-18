#include <iostream>
#include "algorithm.h"

struct Pathway{
    double distance;
    std::vector<int>path;

    Pathway(double dist) : distance(dist) {}
};

static constexpr double INF = std::numeric_limits<double>::infinity();
Pathway dijkstra(Graph& graph, int src, int goal)
{
    int size = static_cast<int>(graph.size());

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
            double total_dist = u.first + edge.cost;

            if (total_dist < dist[v])
            {
                prev[v] = u.second;
                dist[v] = total_dist;

                queue.push({total_dist,v});
            }
        }


    }
    Pathway result(0.0);

    for (double num : dist)
    {
        result.distance +=num;
    }
    result.path = prev;

    return result;

}

double heuristic(double g_n,double h_n)
{
    return g_n + h_n;
}

