#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <limits>


struct Edge;

struct Vertex{
    int id;
    std::string name;
    std::vector<Edge> adj;

    Vertex(int id, std::string name);

    static bool findEdge(const Vertex& vertex, int dest,int weight);

    bool operator==(const Vertex& other)const{
        return id == other.id && name == other.name && adj == other.adj;
    }

    bool operator!=(const Vertex& other) const{
        return !(*this == other);
    }
};

struct Edge {
    double cost;
    int destination;

    Edge(double cost, int dest);
};



class Graph{
    private:
        std::vector<Vertex> vertices;



    public:
        Graph();

        const std::vector<Vertex>& getData() const;

        int size();

        bool findVertex(std::string name);
        bool findVertex(int id);
        bool findEdge(int src_v,int dest_v,double weight);

        Vertex& operator[](int index);


        void addVertex(std::string name);
        void addEdge(int src_v,int dest_v, double weight);
        const std::vector<Edge>& getNeighbors(int id) const;
};


#endif