//ID : 208336701
//mail : ofekmarom9@gmail.com


#ifndef GRAPH_HPP
#define GRAPH_HPP
//#include "doctest.h"
#include <iostream>
#include <vector>
using namespace std;
namespace ariel
{
    class Graph
    {
    private:
        vector<vector<int>> adjMatrix; // the adjacency matrix representing the graph
        int vertices; // the number of vertices in the graph
        int edges; // the number of edges in the graph

    public:
        Graph();

        //load the graph
        void loadGraph(vector<vector<int>> graph2);

        //print the graph
        void printGraph();

        //return the adjacency matrix representing the graph
        std::vector<std::vector<int>> getMatrix();

        //return the number of vertices in the graph
        int getVertices();

        //return the number of edges in the graph
        int getEdges();
    };
}
#endif