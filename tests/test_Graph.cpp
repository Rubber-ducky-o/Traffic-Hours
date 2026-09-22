#include <gtest/gtest.h>
#include "Graph.h"


TEST(EdgeTest,Initialize)
{
    Edge a_edge(4,200,3.2,65);

    EXPECT_EQ(a_edge.distance, 200);
    EXPECT_EQ(a_edge.travel_time,3.2);
    EXPECT_EQ(a_edge.destination,4);
    EXPECT_EQ(a_edge.speed_limit,65);

    Edge fallback(5,10.0,-1.0,50);

    EXPECT_NEAR(fallback.travel_time,12.0,0.001);

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
    Edge edge(10,2.3,10,65);
    vert.adj.push_back(edge);

    EXPECT_TRUE(Vertex::findEdge(vert,10));
    EXPECT_FALSE(Vertex::findEdge(vert,5));

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

    graph.addEdge(0,1,2.3,5,65);
    EXPECT_TRUE(graph.findEdge(0,1));
}

TEST(Graphing,getNeighbors)
{
    Graph graph;
    graph.addVertex("A",0.2802232,82.2907);
    graph.addVertex("B",0.2802232,82.2907);
    graph.addVertex("C",0.2802232,82.2907);
    graph.addVertex("D",0.2802232,82.2907);

    graph.addEdge(0,1,0.0,2,65);
    graph.addEdge(0,2,0.0,10,65);
    graph.addEdge(0,3,0.0,100,65);

    const std::vector<Edge> edges = graph.getNeighbors(0);
    size_t si = 3;

    EXPECT_EQ(edges.size(),3);
}

TEST(Graphing,FreeFlowEdge)
{
    Graph graph;
    graph.addVertex("A",0.0,0.0);
    graph.addVertex("B",0.0,0.0);

    graph.addEdge(0,1,10.0,-1.0,50);

    auto edges = graph.getNeighbors(0);

    EXPECT_EQ(edges.size(),1);
    EXPECT_NEAR(edges[0].travel_time,12.0,0.001);
    EXPECT_EQ(edges[0].speed_limit,50);


}