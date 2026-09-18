#include <iostream>
#include "Graph.h"


Vertex::Vertex(int id, std::string name ) : name(name), id(id) {}

Edge::Edge(double cost, int dest) : cost(cost), destination(dest) {}

Graph::Graph() {}

const std::vector<Vertex>& Graph::getData() const
{
    return vertices;
}
int Graph::size()
{
    return vertices.size();
}

Vertex& Graph::operator[](int index)
{
    return vertices[index];
}

void Graph::addVertex(std::string name)
{
    if (Graph::findVertex(name)) return;

    Vertex new_point(vertices.size(),name);
    vertices.push_back(new_point);
}


void Graph::addEdge(int src_v,int dest_v,double weight)
{
    if (!findVertex(src_v) ||!findVertex(dest_v) ) return;

    if (Vertex::findEdge(vertices[src_v],dest_v,weight)) return;


    Edge new_edge(weight, dest_v);
    vertices[src_v].adj.push_back(new_edge);


}

const std::vector<Edge>& Graph::getNeighbors(int id) const
{
    return vertices[id].adj;
    }


//HELPER FUNCTIONS
bool Graph::findVertex(std::string name){


    for(const auto& vertex : vertices)
    {
        if (vertex.name == name) return true;
    }
    return false;

}
bool Graph::findVertex(int id){

    if ((id >= 0) && id < static_cast<int>(vertices.size())) return true;

    return false;
}

bool Vertex::findEdge(const Vertex& vertex, int dest,int weight){

    for (const auto& Edge : vertex.adj)
    {
        if (Edge.destination == dest && Edge.cost == weight) return true;

    }
    return false;

}

bool Graph::findEdge(int src_v,int dest_v,double weight)
{
    return Vertex::findEdge(vertices[src_v], dest_v,weight);
}

