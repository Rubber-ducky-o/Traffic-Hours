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
            double total_dist = u.first + edge.cost;

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


    result.distance = dist[goal];
    result.path = reconstruct_pathway(prev,src,goal);

    return result;

}

double heuristic(double longitude,double latitude)
{
    return 0.0;
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
    double priority = cost_so_far[start] + heuristic(start,goal);


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

            double new_cost = cost_so_far[vertex] + edge.cost;

            if (new_cost < cost_so_far[next])
            {
                cost_so_far[next] = new_cost;

                came_from[next] = vertex;

                double priority = new_cost + heuristic(next,goal);

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

    result.distance = cost_so_far[goal];
    result.path = reconstruct_pathway(came_from,start,goal);

    return result;

}