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
        static constexpr double INF = std::numeric_limits<double>::infinity();
        Graph();


        bool findVertex(std::string name);
        bool findVertex(int id);
        bool findEdge(int src_v,int dest_v,double weight);

        Vertex& operator[](int index);


        void addVertex(std::string name);
        void addEdge(int src_v,int dest_v, double weight);
        const std::vector<Edge>& getNeighbors(int id) const;
};


#endif