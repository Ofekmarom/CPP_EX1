//ID : 208336701
//mail : ofekmarom9@gmail.com

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"

using namespace std;
using namespace ariel;

TEST_CASE("test invalid graph loadGraph with different cases")
{
    ariel::Graph g;

    SUBCASE("test empty graph")
    {
        vector<vector<int>> graph = {};
        CHECK_THROWS_AS(g.loadGraph(graph), std::invalid_argument);
    }

    SUBCASE("invalid matrix (not square)") {
        vector<vector<int>> graph = {
                {0, 1, 2},
                {1, 0}};
        CHECK_THROWS(g.loadGraph(graph));
    }

    SUBCASE("valid matrix") {
        vector<vector<int>> graph = {
                {0, 1, 0},
                {1, 0, 1},
                {0, 1, 0}};
        CHECK_NOTHROW(g.loadGraph(graph));
    }
}

TEST_CASE("test isConnected with different cases")
{
    ariel::Graph g;

    SUBCASE("single vertex graph") {
        vector<vector<int>> graph = {{0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isConnected(g) == true);
    }

    SUBCASE("fully connected graph") {
        vector<vector<int>> graph = {
                {0, 1, 1},
                {1, 0, 1},
                {1, 1, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isConnected(g) == true);
    }

    SUBCASE("graph with disconnected vertex") {
        vector<vector<int>> graph = {
                {0, 1, 0},
                {1, 0, 0},
                {0, 0, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isConnected(g) == false);
    }

    SUBCASE("graph with two disconnected components") {
        vector<vector<int>> graph = {
                {0, 1, 0, 0},
                {1, 0, 0, 0},
                {0, 0, 0, 1},
                {0, 0, 1, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isConnected(g) == false);
    }

    SUBCASE("check isconnected") {
        vector<vector<int>> graph2 = {
                {0, 1, 1, 0, 0},
                {1, 0, 1, 0, 0},
                {1, 1, 0, 1, 0},
                {0, 0, 1, 0, 0},
                {0, 0, 0, 0, 0}};
        g.loadGraph(graph2);
        CHECK(ariel::Algorithms::isConnected(g) == false);
    }

}

TEST_CASE("test shortestPath with different cases")
{
    ariel::Graph g;

    SUBCASE("path to not existing vertex") {
        vector<vector<int>> graph = {
                {0, 1, 0},
                {1, 0, 1},
                {0, 1, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "-1");
    }


    SUBCASE("single vertex graph") {
        vector<vector<int>> graph = {{0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::shortestPath(g, 0, 0) == "0");
    }

    SUBCASE("no path between vertices") {
        vector<vector<int>> graph = {
                {0, 0, 0},
                {0, 0, 0},
                {0, 0, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "-1");
    }

    SUBCASE("path exists") {
        vector<vector<int>> graph = {
                {0, 1, 0},
                {1, 0, 1},
                {0, 1, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->1->2");
    }

    SUBCASE("path to itself") {
        vector<vector<int>> graph = {
                {0, 1, 0},
                {1, 0, 1},
                {0, 1, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::shortestPath(g, 1, 1) == "1");
    }

    // graph with negative edge weights but no negative cycles
    SUBCASE("shortest path with negative edge weights") {
        vector<vector<int>> graph = {
                {0, 1, 1, 0},
                {1, 0, 4, 0},
                {-1, 4, 0, 2},
                {0, 0, 2, 0}
        };
        g.loadGraph(graph);

        // testing many paths
        CHECK(ariel::Algorithms::shortestPath(g, 0, 1) == "0->1");
        CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->2");
        CHECK(ariel::Algorithms::shortestPath(g, 0, 3) == "0->2->3");
        CHECK(ariel::Algorithms::shortestPath(g, 1, 3) == "1->0->2->3");
    }

// graph with zero weight edges
    SUBCASE("shortest path with zero weight edges") {
        vector<vector<int>> graph = {
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0}
        };
        g.loadGraph(graph);

        // Since all edges are zero, any vertex should be reachable in one step
        CHECK(ariel::Algorithms::shortestPath(g, 0, 1) == "-1");
        CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "-1");
        CHECK(ariel::Algorithms::shortestPath(g, 0, 3) == "-1");
    }


    SUBCASE("test shoertest path with negative edge in the path") {
        vector<vector<int>> graph = {
                {0, 7, 5},
                {0, 0, -3},
                {0, 0, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->1->2");
    }

}

TEST_CASE("test isContainsCycle with different cases")
{
    ariel::Graph g;



    SUBCASE("single vertex graph") {
        vector<vector<int>> graph = {{0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isContainsCycle(g) == false);
    }

    SUBCASE("graph with no cycles") {
        vector<vector<int>> graph = {
                {0, 0, 0},
                {0, 0, 50},
                {0, 0, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isContainsCycle(g) == false);
    }

    SUBCASE("graph with a cycle") {
        vector<vector<int>> graph = {
                {0, 1, 1},
                {1, 0, 1},
                {1, 1, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isContainsCycle(g) == true);
    }

    SUBCASE("graph with a cycle") {
        vector<vector<int>> graph2 = {
                {0, 1, 1, 0, 0},
                {1, 0, 1, 0, 0},
                {1, 1, 0, -21, 0},
                {0, 0, 1, 0, 0},
                {0, 0, 0, 0, 0}};
        g.loadGraph(graph2);
        CHECK(ariel::Algorithms::isContainsCycle(g) == true);
    }
}

TEST_CASE("test isBipartite with different cases")
{
    ariel::Graph g;

    SUBCASE("single vertex graph") {
        vector<vector<int>> graph = {{0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0}, B={}");
    }

    SUBCASE("a bipartite graph") {
        vector<vector<int>> graph = {
                {0, 1, 0},
                {1, 0, 1},
                {0, 1, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0,2}, B={1}");
    }

    SUBCASE("non bipartite graph") {
        vector<vector<int>> graph = {
                {0, 1, 1},
                {1, 0, 1},
                {1, 1, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isBipartite(g) == "0");
    }

    SUBCASE("non bipartite graph") {
        vector<vector<int>> graph3 = {
                {0, 1, 2, 0, 0},
                {1, 0, 3, 0, 0},
                {2, 3, 0, 4, 0},
                {0, 0, 4, 0, 5},
                {0, 0, 0, 5, 0}};
        g.loadGraph(graph3);
        CHECK(ariel::Algorithms::isBipartite(g) == "0");
    }

    SUBCASE("non bipartite graph") {
        vector<vector<int>> graph2 = {
                {0, 1, 1, 0, 0},
                {1, 0, 1, 0, 0},
                {1, 1, 0, 1, 0},
                {0, 0, 1, 0, 0},
                {0, 0, 0, 0, 0}};
        g.loadGraph(graph2);
        CHECK(ariel::Algorithms::isBipartite(g) == "0");
    }

    SUBCASE("disconnected bipartite graph") {
        vector<vector<int>> graph = {
                {0, 1, 0, 0},
                {1, 0, 0, 0},
                {0, 0, 0, 1},
                {0, 0, 1, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0,2}, B={1,3}");
    }
}


TEST_CASE("test isDirected with different cases")
{
    ariel::Graph g;

    SUBCASE("Undirected graph") {
        vector<vector<int>> graph = {
                {0, 1, 0},
                {1, 0, 1},
                {0, 1, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isDirected(g) == false);
    }

    SUBCASE("directed graph") {
        vector<vector<int>> graph = {
                {0, 1, 0},
                {0, 0, 1},
                {1, 0, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isDirected(g) == true);
    }
    SUBCASE("directed graph with negative edges") {
        vector<vector<int>> graph = {
                {0, -7, 1},
                {0, 0, -15},
                {1, 0, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isDirected(g) == true);
    }
}

TEST_CASE("test negativeCycle with different cases")
{
    ariel::Graph g;

    SUBCASE("graph with no negative cycles") {
        vector<vector<int>> graph = {
                {0, 1, 0},
                {1, 0, 1},
                {0, 1, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::negativeCycle(g) == false);
    }

    SUBCASE("graph with negative cycle") {
        vector<vector<int>> graph = {
                {0, 1, 2},
                {-1, 0, 3},
                {-2, -3, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::negativeCycle(g) == true);
    }
}

TEST_CASE("test invalid graph")
{
    ariel::Graph g;
    vector <vector<int>> graph = {
            {0, 1, 2, 0},
            {1, 0, 3, 0},
            {2, 3, 0, 4},
            {0, 0, 4, 0},
            {0, 0, 0, 5}};
    CHECK_THROWS(g.loadGraph(graph));
}
