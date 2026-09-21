#include <gtest/gtest.h>
#include "algorithm.h"

TEST(Pathway, Initialization)
{
    Pathway testing(3.2);
    EXPECT_EQ(testing.travel_time, 3.2);
}

TEST(Dijkstra,single_node)
{
    Graph graph;
    graph.addVertex("A",0.0,0.0);

    Pathway val1 = dijkstra(graph,0,1);

    EXPECT_EQ(val1.travel_time,-1);
    std::vector<int> answer = {-1};

    EXPECT_EQ(val1.path,answer);
}

TEST(Dijkstra,path){
    Graph graph;
    graph.addVertex("A",0.0,0.0);
    graph.addVertex("B",0.0,0.0);
    graph.addVertex("C",0.0,0.0);
    graph.addVertex("D",0.0,0.0);
    graph.addVertex("E",0.0,0.0);

    graph.addEdge(0,1,0.0,10,65);
    graph.addEdge(0,2,0.0,1,65);
    graph.addEdge(0,3,0.0,10,65);
    graph.addEdge(1,0,0.0,9,65);
    graph.addEdge(1,2,0.0,4,65);
    graph.addEdge(1,3,0.0,6,65);
    graph.addEdge(2,0,0.0,0,65);
    graph.addEdge(2,4,0.0,15,65);
    graph.addEdge(3,1,0.0,4,65);
    graph.addEdge(3,4,0.0,11,65);

    Pathway val1 = dijkstra(graph,0,4);

    EXPECT_EQ(val1.travel_time,16);
    std::vector<int> answer = {0,2,4};

    EXPECT_EQ(val1.path,answer);


}

TEST(Dijkstra,shortest_path){
    Graph graph;
    graph.addVertex("A",0.0,0.0);
    graph.addVertex("B",0.0,0.0);
    graph.addVertex("C",0.0,0.0);
    graph.addVertex("D",0.0,0.0);
    graph.addVertex("E",0.0,0.0);

    graph.addEdge(0,1,0.0,10,65);
    graph.addEdge(0,2,0.0,1,65);
    graph.addEdge(0,3,0.0,10,65);
    graph.addEdge(1,0,0.0,9,65);
    graph.addEdge(1,2,0.0,4,65);
    graph.addEdge(1,3,0.0,6,65);
    graph.addEdge(2,0,0.0,0,65);
    graph.addEdge(2,4,0.0,15,65);
    graph.addEdge(3,1,0.0,4,65);
    graph.addEdge(3,4,0.0,11,65);

    Pathway val1 = dijkstra(graph,2,2);

    EXPECT_EQ(val1.travel_time,0);
    std::vector<int> answer = {2};

    EXPECT_EQ(val1.path,answer);


}
TEST(Dijkstra,multipath)
{
    Graph graph;
    graph.addVertex("S",0.0,0.0);
    graph.addVertex("A",0.0,0.0);
    graph.addVertex("B",0.0,0.0);
    graph.addVertex("C",0.0,0.0);
    graph.addVertex("G",0.0,0.0);

    graph.addEdge(0,1,0.0,14,65);
    graph.addEdge(0,2,0.0,12,65);
    graph.addEdge(1,1,0.0,6,65);
    graph.addEdge(1,2,0.0,6,65);
    graph.addEdge(2,2,0.0,2,65);
    graph.addEdge(2,4,0.0,18,65);
    graph.addEdge(3,4,0.0,4,65);

    Pathway ans = dijkstra(graph,0,4);
    std::vector<int>answer = {0,2,4};
    EXPECT_EQ(ans.travel_time,30);
    EXPECT_EQ(ans.path,answer);

}

TEST(Dijkstra, impossible_path){
    Graph graph;
    graph.addVertex("A",0.0,0.0);
    graph.addVertex("B",0.0,0.0);
    graph.addVertex("C",0.0,0.0);
    graph.addVertex("D",0.0,0.0);
    graph.addVertex("E",0.0,0.0);
    graph.addVertex("F",0.0,0.0);

    graph.addEdge(0,1,0.0,10,65);
    graph.addEdge(0,2,0.0,1,65);
    graph.addEdge(0,3,0.0,10,65);
    graph.addEdge(1,0,0.0,9,65);
    graph.addEdge(1,2,0.0,4,65);
    graph.addEdge(1,3,0.0,6,65);
    graph.addEdge(2,0,0.0,0,65);
    graph.addEdge(2,4,0.0,15,65);
    graph.addEdge(3,1,0.0,4,65);
    graph.addEdge(3,4,0.0,11,65);

    Pathway val1 = dijkstra(graph,0,5);

    EXPECT_EQ(val1.travel_time,-1);
    std::vector<int> answer = {-1};

    EXPECT_EQ(val1.path,answer);

}

TEST(A_star,single_node)
{
    Graph graph;
    graph.addVertex("A",10.322,-13.3273);

    Pathway val1 = dijkstra(graph,0,1);

    EXPECT_EQ(val1.travel_time,-1);
    std::vector<int> answer = {-1};

    EXPECT_EQ(val1.path,answer);

}

TEST(TravelTime, Normalcase)
{
    double result = caltraveltime(10.0,50);

    EXPECT_NEAR(result,12.0,0.001);

}
TEST(TravelTime,ErrorCase)
{
    double result = caltraveltime(10,0);
    EXPECT_EQ(result, -1);
}


TEST(Heuristic,heuristic_result)
{
    Graph graph;
    graph.addVertex("S",19.189354,-72.951225);
    graph.addVertex("G",19.186333,-72.966961);

    double result = heuristic(graph,0,1);

    double expected = (1.048 / 90.0) * 60;

    EXPECT_NEAR(result,expected,0.01);



}

TEST(A_star,path){
    Graph graph;
    graph.addVertex("A",33.9400,-118.1200);
    graph.addVertex("B",33.9410,-118.1190);
    graph.addVertex("C",33.9405,-118.1175);
    graph.addVertex("D",33.9390,-118.1185);
    graph.addVertex("E",33.9400,-118.1150);

    graph.addEdge(0,1,1.2,10,65);
    graph.addEdge(0,2,0.8,1,65);
    graph.addEdge(0,3,1.5,10,65);
    graph.addEdge(1,0,1.2,9,65);
    graph.addEdge(1,2,0.7,4,65);
    graph.addEdge(1,3,0.9,6,65);
    graph.addEdge(2,0,0.8,0,65);
    graph.addEdge(2,4,1.6,15,65);
    graph.addEdge(3,1,0.9,4,65);
    graph.addEdge(3,4,1.1,11,65);

    Pathway val1 = a_star(graph,0,4);

    EXPECT_EQ(val1.travel_time,16);
    std::vector<int> answer = {0,2,4};

    EXPECT_EQ(val1.path,answer);


}

TEST(A_star,shortest_path){
    Graph graph;
    graph.addVertex("A",33.9400,-118.1200);
    graph.addVertex("B",33.9410,-118.1190);
    graph.addVertex("C",33.9405,-118.1175);
    graph.addVertex("D",33.9390,-118.1185);
    graph.addVertex("E",33.9400,-118.1150);

    graph.addEdge(0,1,1.2,10,65);
    graph.addEdge(0,2,0.8,1,65);
    graph.addEdge(0,3,1.5,10,65);
    graph.addEdge(1,0,1.2,9,65);
    graph.addEdge(1,2,0.7,4,65);
    graph.addEdge(1,3,0.9,6,65);
    graph.addEdge(2,0,0.8,0,65);
    graph.addEdge(2,4,1.6,15,65);
    graph.addEdge(3,1,0.9,4,65);
    graph.addEdge(3,4,1.1,11,65);

    Pathway val1 = a_star(graph,2,2);

    EXPECT_EQ(val1.travel_time,0);
    std::vector<int> answer = {2};

    EXPECT_EQ(val1.path,answer);


}


TEST(A_star, impossible_path){
    Graph graph;
    graph.addVertex("A",33.9400,-118.1200);
    graph.addVertex("B",33.9410,-118.1190);
    graph.addVertex("C",33.9405,-118.1175);
    graph.addVertex("D",33.9390,-118.1185);
    graph.addVertex("E",33.9400,-118.1150);
    graph.addVertex("F",0.0,0.0);

    graph.addEdge(0,1,1.2,10,65);
    graph.addEdge(0,2,0.8,1,65);
    graph.addEdge(0,3,1.5,10,65);
    graph.addEdge(1,0,1.2,9,65);
    graph.addEdge(1,2,0.7,4,65);
    graph.addEdge(1,3,0.9,6,65);
    graph.addEdge(2,0,0.8,0,65);
    graph.addEdge(2,4,1.6,15,65);
    graph.addEdge(3,1,0.9,4,65);
    graph.addEdge(3,4,1.1,11,65);

    Pathway val1 = a_star(graph,0,5);

    EXPECT_EQ(val1.travel_time,-1);
    std::vector<int> answer = {-1};

    EXPECT_EQ(val1.path,answer);

}
TEST(A_star,multipath)
{
    Graph graph;
    graph.addVertex("S",33.9400,-118.1200);
    graph.addVertex("A",33.9470,-118.1070);
    graph.addVertex("B",33.9400,-118.1030);
    graph.addVertex("C",33.9300,-118.0750);
    graph.addVertex("G",33.9400,-118.0510);

    graph.addEdge(0,1,2.1,14,65);
    graph.addEdge(0,2,1.2,12,65);
    graph.addEdge(1,1,0.8,6,65);
    graph.addEdge(1,2,0.7,6,65);
    graph.addEdge(2,2,0.6,2,65);
    graph.addEdge(2,4,7.6,18,65);
    graph.addEdge(3,4,5.4,4,65);

    Pathway ans = a_star(graph,0,4);

    std::vector<int>answer = {0,2,4};
    EXPECT_EQ(ans.travel_time,30);
    EXPECT_EQ(ans.path,answer);

}