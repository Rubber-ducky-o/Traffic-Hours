#include <gtest/gtest.h>
#include "Graph.h"


TEST(EdgeTest,Initialize)
{
    Edge a_edge(4,200,3.2);

    EXPECT_EQ(a_edge.distance, 200);
    EXPECT_EQ(a_edge.travel_time,3.2);
    EXPECT_EQ(a_edge.destination,4);
}

TEST(Vertex, Initialize){
    Vertex a_vertex(0,"test_vertex",0.2802232,82.2907);

    std::pair<double,double> answer = {0.2802232,82.2907};
    EXPECT_EQ(a_vertex.id,0);
    EXPECT_EQ(a_vertex.name,"test_vertex");
    EXPECT_EQ(a_vertex.coordinates,answer);

}

TEST(Vertex, findEdge){
    Vertex vert(0,"test_vertex",0.2802232,82.2907);
    Edge edge(10,2.3,10);
    vert.adj.push_back(edge);

    EXPECT_TRUE(Vertex::findEdge(vert,10,2.3,10));

}

TEST(Graphing,AddVertex)
{
    Graph graph;

    graph.addVertex("A",0.2802232,82.2907);
    graph.addVertex("B",0.2802232,82.2907);
    graph.addVertex("C",0.2802232,82.2907);

    EXPECT_EQ(graph[0].name,"A");
    EXPECT_EQ(graph[1].name,"B");
    EXPECT_EQ(graph[2].name,"C");
}

TEST(Graphing,findVertexbyname)
{
    Graph graph;
    graph.addVertex("A",0.2802232,82.2907);
    graph.addVertex("B",0.2802232,82.2907);
    graph.addVertex("C",0.2802232,82.2907);

    EXPECT_TRUE(graph.findVertex("A"));
    EXPECT_FALSE(graph.findVertex("D"));
}
TEST(Graphing,findVertexbyid)
{
    Graph graph;
    graph.addVertex("A",0.2802232,82.2907);
    graph.addVertex("B",0.2802232,82.2907);
    graph.addVertex("C",0.2802232,82.2907);

    EXPECT_TRUE(graph.findVertex(1));
    EXPECT_FALSE(graph.findVertex(4));
}
TEST(Graphing,addEdge)
{
    Graph graph;
    graph.addVertex("A",0.2802232,82.2907);
    graph.addVertex("B",0.2802232,82.2907);

    graph.addEdge(0,1,2.3,5);
    EXPECT_TRUE(graph.findEdge(0,1,2.3,5));
}

TEST(Graphing,getNeighbors)
{
    Graph graph;
    graph.addVertex("A",0.2802232,82.2907);
    graph.addVertex("B",0.2802232,82.2907);
    graph.addVertex("C",0.2802232,82.2907);
    graph.addVertex("D",0.2802232,82.2907);

    graph.addEdge(0,1,0.0,2);
    graph.addEdge(0,2,0.0,10);
    graph.addEdge(0,3,0.0,100);

    const std::vector<Edge> edges = graph.getNeighbors(0);
    size_t si = 3;

    EXPECT_EQ(edges.size(),3);


}