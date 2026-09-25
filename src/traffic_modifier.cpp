#include "traffic_modifier.h"
#include <iostream>

void applyClosure(Graph& graph, const std::vector<int>& closure_path, const ClosureData& closure)
{
    if (closure.total_existing_lanes <= 0) return;

    if (closure.lanes_closed.size() == closure.total_existing_lanes)
    {
        for (size_t i =0; i+ 1 < closure_path.size(); ++i)
        {
            int source = closure_path[i];
            int dest = closure_path[i+1];
            Edge* e = graph.getEdge(source,dest);

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

        int start = findNearbyVertex(graph,closure.begin_lat,closure.begin_lon,MAX_SNAP_DISTANCE);
        int end = findNearbyVertex(graph,closure.end_lat,closure.end_lon,MAX_SNAP_DISTANCE);

        if (start == -1 || end == -1) continue;

        auto pathway = DistancebasedDijkstra(graph,start,end);
        if (pathway.path.empty() || pathway.path[0] == -1) continue;

        applyClosure(graph,pathway.path,closure);

    }

}