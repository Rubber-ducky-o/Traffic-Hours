#include <iostream>
#include "Graph.h"
#include "algorithm.h"


Vertex::Vertex(int id, std::string name,double lat,double longi ) : name(name), id(id), coordinates({lat,longi}) {}


bool Vertex::operator==(const Vertex& other)const{
   return id == other.id && name == other.name && adj == other.adj && coordinates == other.coordinates;
}


bool Vertex::operator!=(const Vertex& other) const{
   return !(*this == other);
}

std::pair<double,double> Vertex::getcoords() const{
    return coordinates;
}

Edge::Edge(int destination, double distance,double travel_time,int speed_limit) : distance(distance),destination(destination), speed_limit(speed_limit) {
    if (travel_time < 0)
    {
      this->travel_time =caltraveltime(distance, speed_limit);

    }
    else
    {
       this->travel_time = travel_time;
    }
}


bool Edge::operator==(const Edge& other)const{
    return travel_time == other.travel_time && destination == other.destination && distance == other.distance && speed_limit == other.speed_limit;
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

const Vertex& Graph::operator[](int index) const
{
    return vertices[index];
}

void Graph::addVertex(std::string name,double lat,double longi)
{
    if (Graph::findVertex(name)) return;

    Vertex new_point(vertices.size(),name,lat,longi);
    vertices.push_back(new_point);
}


void Graph::addEdge(int source,int destination, double distance,double travel_time,int speed)
{
    if (!findVertex(source) ||!findVertex(destination) ) return;

    if (Vertex::findEdge(vertices[source], destination, distance,travel_time,speed)) return;


    Edge new_edge(destination,distance, travel_time, speed);
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


bool Vertex::findEdge(const Vertex& vertex,int destination, double distance,double travel_time,int speed){


    for (const auto& Edge : vertex.adj)
    {
        if (Edge.destination == destination && Edge.travel_time == travel_time && Edge.distance == distance && Edge.speed_limit == speed) return true;

    }
    return false;

}


bool Graph::findEdge(int source,int destination,double distance,double travel_time,int speed)
{
    return Vertex::findEdge(vertices[source],destination, distance,travel_time,speed);
}

