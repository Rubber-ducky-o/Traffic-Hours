#include <gtest/gtest.h>
#include "algorithm.h"

TEST(Pathway, Initialization)
{
    Pathway testing(3.2);
    EXPECT_EQ(testing.distance, 3.2);
}

TEST(Dijkstra,single_node)
{
    Graph graph;
    graph.addVertex("A");

    Pathway val1 = dijkstra(graph,0,1);

    EXPECT_EQ(val1.distance,-1);
    std::vector<int> answer = {-1};

    EXPECT_EQ(val1.path,answer);
}

TEST(Dijkstra,path){
    Graph graph;
    graph.addVertex("A");
    graph.addVertex("B");
    graph.addVertex("C");
    graph.addVertex("D");
    graph.addVertex("E");

    graph.addEdge(0,1,10);
    graph.addEdge(0,2,1);
    graph.addEdge(0,3,10);
    graph.addEdge(1,0,9);
    graph.addEdge(1,2,4);
    graph.addEdge(1,3,6);
    graph.addEdge(2,0,0);
    graph.addEdge(2,4,15);
    graph.addEdge(3,1,4);
    graph.addEdge(3,4,11);

    Pathway val1 = dijkstra(graph,0,4);

    EXPECT_EQ(val1.distance,16);
    std::vector<int> answer = {0,2,4};

    EXPECT_EQ(val1.path,answer);


}

TEST(Dijkstra,shortest_path){
    Graph graph;
    graph.addVertex("A");
    graph.addVertex("B");
    graph.addVertex("C");
    graph.addVertex("D");
    graph.addVertex("E");

    graph.addEdge(0,1,10);
    graph.addEdge(0,2,1);
    graph.addEdge(0,3,10);
    graph.addEdge(1,0,9);
    graph.addEdge(1,2,4);
    graph.addEdge(1,3,6);
    graph.addEdge(2,0,0);
    graph.addEdge(2,4,15);
    graph.addEdge(3,1,4);
    graph.addEdge(3,4,11);

    Pathway val1 = dijkstra(graph,2,2);

    EXPECT_EQ(val1.distance,0);
    std::vector<int> answer = {2};

    EXPECT_EQ(val1.path,answer);


}
TEST(Dijkstra,multipath)
{
    Graph graph;
    graph.addVertex("S");
    graph.addVertex("A");
    graph.addVertex("B");
    graph.addVertex("C");
    graph.addVertex("G");

    graph.addEdge(0,1,14);
    graph.addEdge(0,2,12);
    graph.addEdge(1,1,6);
    graph.addEdge(1,2,6);
    graph.addEdge(2,2,2);
    graph.addEdge(2,4,18);
    graph.addEdge(3,4,4);

    Pathway ans = dijkstra(graph,0,4);
    std::vector<int>answer = {0,2,4};
    EXPECT_EQ(ans.distance,30);
    EXPECT_EQ(ans.path,answer);

}

TEST(Dijkstra, impossible_path){
    Graph graph;
    graph.addVertex("A");
    graph.addVertex("B");
    graph.addVertex("C");
    graph.addVertex("D");
    graph.addVertex("E");
    graph.addVertex("F");

    graph.addEdge(0,1,10);
    graph.addEdge(0,2,1);
    graph.addEdge(0,3,10);
    graph.addEdge(1,0,9);
    graph.addEdge(1,2,4);
    graph.addEdge(1,3,6);
    graph.addEdge(2,0,0);
    graph.addEdge(2,4,15);
    graph.addEdge(3,1,4);
    graph.addEdge(3,4,11);

    Pathway val1 = dijkstra(graph,0,5);

    EXPECT_EQ(val1.distance,-1);
    std::vector<int> answer = {-1};

    EXPECT_EQ(val1.path,answer);

}

TEST(A_star,single_node)
{
    Graph graph;
    graph.addVertex("A");

    Pathway val1 = dijkstra(graph,0,1);

    EXPECT_EQ(val1.distance,-1);
    std::vector<int> answer = {-1};

    EXPECT_EQ(val1.path,answer);
}

TEST(A_star,path){
    Graph graph;
    graph.addVertex("A");
    graph.addVertex("B");
    graph.addVertex("C");
    graph.addVertex("D");
    graph.addVertex("E");

    graph.addEdge(0,1,10);
    graph.addEdge(0,2,1);
    graph.addEdge(0,3,10);
    graph.addEdge(1,0,9);
    graph.addEdge(1,2,4);
    graph.addEdge(1,3,6);
    graph.addEdge(2,0,0);
    graph.addEdge(2,4,15);
    graph.addEdge(3,1,4);
    graph.addEdge(3,4,11);

    Pathway val1 = a_star(graph,0,4);

    EXPECT_EQ(val1.distance,16);
    std::vector<int> answer = {0,2,4};

    EXPECT_EQ(val1.path,answer);


}

TEST(A_star,shortest_path){
    Graph graph;
    graph.addVertex("A");
    graph.addVertex("B");
    graph.addVertex("C");
    graph.addVertex("D");
    graph.addVertex("E");

    graph.addEdge(0,1,10);
    graph.addEdge(0,2,1);
    graph.addEdge(0,3,10);
    graph.addEdge(1,0,9);
    graph.addEdge(1,2,4);
    graph.addEdge(1,3,6);
    graph.addEdge(2,0,0);
    graph.addEdge(2,4,15);
    graph.addEdge(3,1,4);
    graph.addEdge(3,4,11);

    Pathway val1 = a_star(graph,2,2);

    EXPECT_EQ(val1.distance,0);
    std::vector<int> answer = {2};

    EXPECT_EQ(val1.path,answer);


}


TEST(A_star, impossible_path){
    Graph graph;
    graph.addVertex("A");
    graph.addVertex("B");
    graph.addVertex("C");
    graph.addVertex("D");
    graph.addVertex("E");
    graph.addVertex("F");

    graph.addEdge(0,1,10);
    graph.addEdge(0,2,1);
    graph.addEdge(0,3,10);
    graph.addEdge(1,0,9);
    graph.addEdge(1,2,4);
    graph.addEdge(1,3,6);
    graph.addEdge(2,0,0);
    graph.addEdge(2,4,15);
    graph.addEdge(3,1,4);
    graph.addEdge(3,4,11);

    Pathway val1 = a_star(graph,0,5);

    EXPECT_EQ(val1.distance,-1);
    std::vector<int> answer = {-1};

    EXPECT_EQ(val1.path,answer);

}
TEST(A_star,multipath)
{
    Graph graph;
    graph.addVertex("S");
    graph.addVertex("A");
    graph.addVertex("B");
    graph.addVertex("C");
    graph.addVertex("G");

    graph.addEdge(0,1,14);
    graph.addEdge(0,2,12);
    graph.addEdge(1,1,6);
    graph.addEdge(1,2,6);
    graph.addEdge(2,2,2);
    graph.addEdge(2,4,18);
    graph.addEdge(3,4,4);

    Pathway ans = dijkstra(graph,0,4);
    std::vector<int>answer = {0,2,4};
    EXPECT_EQ(ans.distance,30);
    EXPECT_EQ(ans.path,answer);

}