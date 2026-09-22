#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <limits>


struct Edge;

struct Vertex{
    int id;
    std::string name;
    std::vector<Edge> adj;
    // (LATITUDE, LONGITUDE)
    std::pair<double,double> coordinates;


    Vertex(int id, std::string name,double lat,double longi);

    static bool findEdge(const Vertex& vertex,int destination);

    bool operator==(const Vertex& other)const;

    bool operator!=(const Vertex& other) const;

    std::pair<double,double> getcoords() const;

};

struct Edge {
    double travel_time;//time
    double distance;//miles
    int destination;//other vertex
    int speed_limit;



    Edge(int destination,double distance, double travel_time,int speed_limit);

    bool operator==(const Edge& other)const;

    bool operator!=(const Edge& other)const;
};



class Graph{
    private:
        std::vector<Vertex> vertices;



    public:
        Graph();

        const std::vector<Vertex>& getData() const;

        int size() const;

        bool findVertex(std::string name);
        bool findVertex(int id);
        bool findEdge(int source,int destination);
        const Vertex& operator[](int index) const;
        Vertex& operator[](int index);


        void addVertex(std::string name,double lat,double longi);
        void addEdge(int source,int destination,double distance, double travel_time,int speed);
        const std::vector<Edge>& getNeighbors(int id) const;
};


#endif