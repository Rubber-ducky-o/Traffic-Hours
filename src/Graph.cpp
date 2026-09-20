#include <iostream>
#include "Graph.h"


Vertex::Vertex(int id, std::string name,double lat,double longi ) : name(name), id(id), coordinates({lat,longi}) {}


bool Vertex::operator==(const Vertex& other)const{
   return id == other.id && name == other.name && adj == other.adj && coordinates == other.coordinates;
}


bool Vertex::operator!=(const Vertex& other) const{
   return !(*this == other);
}

std::pair<double,double> Vertex::getcoords() {
    return coordinates;
}

Edge::Edge(int destination, double distance,double travel_time) : travel_time(travel_time), distance(distance),destination(destination) {}


bool Edge::operator==(const Edge& other)const{
    return travel_time == other.travel_time && destination == other.destination && distance == other.distance;
}


bool Edge::operator!=(const Edge& other)const {
    return !(*this == other);
}


Graph::Graph() {}


const std::vector<Vertex>& Graph::getData() const
{
    return vertices;
}


int Graph::size() const
{
    return vertices.size();
}


Vertex& Graph::operator[](int index)
{
    return vertices[index];
}


void Graph::addVertex(std::string name,double lat,double longi)
{
    if (Graph::findVertex(name)) return;

    Vertex new_point(vertices.size(),name,lat,longi);
    vertices.push_back(new_point);
}


void Graph::addEdge(int source,int destination, double distance,double travel_time)
{
    if (!findVertex(source) ||!findVertex(destination) ) return;

    if (Vertex::findEdge(vertices[source], destination, distance,travel_time)) return;


    Edge new_edge(destination,distance, travel_time);
    vertices[source].adj.push_back(new_edge);


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


bool Vertex::findEdge(const Vertex& vertex,int destination, double distance,double travel_time){


    for (const auto& Edge : vertex.adj)
    {
        if (Edge.destination == destination && Edge.travel_time == travel_time && Edge.distance == distance) return true;

    }
    return false;

}


bool Graph::findEdge(int source,int destination,double distance,double travel_time)
{
    return Vertex::findEdge(vertices[source],destination, distance,travel_time);
}

