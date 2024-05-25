//ID : 208336701
//mail : ofekmarom9@gmail.com


#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "Graph.hpp"
#include <string>

namespace ariel {

    class Algorithms {
    private:
        // depth first search(dfs) for checking connectivity (used in the function isConnected)
        static void dfs(Graph& g, int start, std::vector<bool>& visited);
        //function to check if the graph contains a cycle using dfs(used in the function isContainsCycle;
        static bool isContainsCycleDfs(Graph& g, int vertex, int parent, std::vector<bool>& visited);

    public:
        // function to check if the graph is directed
        static bool isDirected(Graph& g);
        // function to check if the graph is connected
        static bool isConnected(Graph& g);
        // fuction to find the shortest path between two vertices
        static std::string shortestPath(Graph& g, int start, int end);
        // function to check if the graph contains a cycle
        static bool isContainsCycle(Graph& g);
        // function to Check if the graph is bipartite
        static std::string isBipartite(Graph& g);
        // function to check if there is a negative cycle in the graph
        static bool negativeCycle(Graph& g);

    };

} // namespace ariel end

#endif // ALGORITHMS_HPP