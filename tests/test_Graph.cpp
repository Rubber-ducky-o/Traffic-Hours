#include <gtest/gtest.h>
#include "Graph.h"


TEST(EdgeTest,Initialize)
{
    Edge a_edge(200,4);

    EXPECT_EQ(a_edge.cost, 200);
    EXPECT_EQ(a_edge.destination,4);
}

TEST(Vertex, Initialize){
    Vertex a_vertex(0,"test_vertex");

    EXPECT_EQ(a_vertex.id,0);
    EXPECT_EQ(a_vertex.name,"test_vertex");

}

TEST(Vertex, findEdge){
    Vertex vert(0,"test_vertex");
    Edge edge(10,1);
    vert.adj.push_back(edge);

    EXPECT_TRUE(Vertex::findEdge(vert,1,10));

}

TEST(Graphing,AddVertex)
{
    Graph graph;

    graph.addVertex("A");
    graph.addVertex("B");
    graph.addVertex("C");

    EXPECT_EQ(graph[0].name,"A");
    EXPECT_EQ(graph[1].name,"B");
    EXPECT_EQ(graph[2].name,"C");
}

TEST(Graphing,findVertexbyname)
{
    Graph graph;
    graph.addVertex("A");
    graph.addVertex("B");
    graph.addVertex("C");

    EXPECT_TRUE(graph.findVertex("A"));
    EXPECT_FALSE(graph.findVertex("D"));
}
TEST(Graphing,findVertexbyid)
{
    Graph graph;
    graph.addVertex("A");
    graph.addVertex("B");
    graph.addVertex("C");

    EXPECT_TRUE(graph.findVertex(1));
    EXPECT_FALSE(graph.findVertex(4));
}
TEST(Graphing,addEdge)
{
    Graph graph;
    graph.addVertex("A");
    graph.addVertex("B");

    graph.addEdge(0,1,10);
    EXPECT_TRUE(graph.findEdge(0,1,10));
}
