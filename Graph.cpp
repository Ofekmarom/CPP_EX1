//ID : 208336701
//mail : ofekmarom9@gmail.com


#include "Graph.hpp"
using namespace std;
namespace ariel
{


    Graph::Graph()
    {
        adjMatrix = {};
        vertices = 0;
        edges = 0;
    }

    void Graph::loadGraph(vector<vector<int>> graph2) //function to load the graph to an object
    {
        // Check if the graph is a square matrix.
        if (graph2.empty() || graph2.size() != graph2[0].size())
        {
            throw invalid_argument("Invalid graph: The graph is not a square matrix.");
        }

        adjMatrix = graph2;// Load the matrix to the graph
        // Count the number of vertices and edges in the graph.
        vertices = graph2.size();
        int allEdges = 0;
        for (size_t i = 0; i < vertices; i++) {
            for (size_t j = 0 ; j < vertices; j++) {
                if (adjMatrix[i][j] != 0) {
                    allEdges++;
                }
            }

        }
        edges = allEdges;
    }
    std::vector<std::vector<int>> Graph::getMatrix()//return the adjacency matrix representing the graph
    {
        return adjMatrix;
    }
    void Graph::printGraph()//funtion to print the graph
    {
        cout << "Graph with " << vertices << " vertices and " << edges << " edges." << endl;
    }
    int Graph::getVertices()//return the number of vertices in the graph
    {
        return this->vertices;
    }
    int Graph::getEdges()//return the number of edges in the graph
    {
        return this->edges;
    }
}