//ID : 208336701
//mail : ofekmarom9@gmail.com


#include "Algorithms.hpp"
#include <queue>
#include <algorithm>
#include <climits> // include for INT_MAX

namespace ariel {

    // function to check if the graph is directed
    bool Algorithms::isDirected(Graph& g) {
        std::vector<std::vector<int>> matrix = g.getMatrix();//the adj matrix of g
        //check that the graph not empty
        if (matrix.empty()){
            return false; // assume undirected for an empty graph
        }
        for (size_t i = 0; i < g.getVertices(); i++) {
            for (size_t j = i + 1; j < g.getVertices(); j++) {
                if (matrix[i][j] != matrix[j][i]) {//if not symetric its directed
                    return true; // the graph is directed
                }
            }
        }
        return false; // the graph is undirected
    }


    // function to check if the graph is connected
    bool Algorithms::isConnected(Graph& g) {
        std::vector<std::vector<int>> matrix = g.getMatrix();//the adj matrix of g
        //check that the graph not empty
        if (matrix.empty()){
            return false; // assume not connected for an empty graph
        }
        std::vector<bool> visited(static_cast<size_t>(g.getVertices()), false); // vector for visited vertices in size of the vertices in the graph and the value for each element is false
        dfs(g, 0, visited); //dfs from vertex 0
        return std::find(visited.begin(), visited.end(), false) == visited.end();// check if all vertices were visited in the dfs (check where is the first false in the visited vector)
    }

    // depth first search(dfs) for checking connectivity
    void Algorithms::dfs(Graph& g, int start, std::vector<bool>& visited) {
        visited[static_cast<size_t>(start)] = true; // mark the current vertex as visited
        for (size_t i = 0; i < g.getVertices(); i++) {
            if (g.getMatrix()[static_cast<size_t>(start)][i] && !visited[i]) {// check if we have an edge between vertex i to the current vertex and if is not visited yet
                dfs(g, i, visited); //do the same for vertex i
            }
        }
    }


    std::string Algorithms::shortestPath(Graph& g, int start, int end) {
        // check that the graph is not empty
        std::vector<std::vector<int>> matrix = g.getMatrix();
        if (matrix.empty()){
            return "-1";
        }
        if (negativeCycle(g)){ //check if there is negative cycle in the graph
            return "-1";
        }

        // number of vertices in the graph
        size_t vertices = static_cast<size_t>(g.getVertices());

        // check that the requested path is valid
        if (start < 0 || start >= vertices || end < 0 || end >= vertices){
            return "-1";
        }

        // Check if the path is from a vertex to itself
        if (start == end){
            return std::to_string(start);
        }

        // initialize distances and parents
        std::vector<int> dist(vertices, INT_MAX);
        std::vector<int> parent(vertices, -1);
        dist[static_cast<size_t>(start)] = 0;//dist from start is 0

        // Bellman-Ford algorithm
        for (size_t i = 0; i < vertices - 1; ++i) {
            for (size_t u = 0; u < vertices; ++u) {
                for (size_t v = 0; v < vertices; ++v) {
                    // check if there is an edge from u to v and if the distance to v can be reduced if we go through u
                    if (matrix[u][v] != 0 && dist[u] != INT_MAX && dist[u] + matrix[u][v] < dist[v]) {
                        // update the distance to v and its parent if a shorter path is found
                        dist[v] = dist[u] + matrix[u][v];
                        parent[v] = static_cast<int>(u);
                    }
                }
            }
        }


        // if the end vertex is not reachable, return "-1"
        if (dist[static_cast<size_t>(end)] == INT_MAX) {
            return "-1";
        }

        // make the shortest path as a string
        std::string path = std::to_string(end); // Start with the end vertex
        // go from the end vertex to the start vertex using the parent
        for (int at = end; at != start; at = parent[static_cast<size_t>(at)]) {
            // add the current vertex to the path string
            path = std::to_string(parent[static_cast<size_t>(at)]) + "->" + path;
        }

        return path;
    }






    // function to check if the graph contains a cycle
    bool Algorithms::isContainsCycle(Graph& g) {
        //check that the graph not empty
        std::vector<std::vector<int>> matrix = g.getMatrix();
        if (matrix.empty()){
            return false;//empty graph no cycle
        }
        size_t vertices = static_cast<size_t>(g.getVertices());
      //  int vertices = g.getVertices();// number of vertices in the graph
        std::vector<bool> visited(vertices, false);// vector for visited vertices in size of the vertices in the graph and the value for each element is false

        // loop through each vertex and check for cycles
        for (size_t i = 0; i < vertices; i++) {
            // check if the vertex has not been visited and if it is part of a cycle
            if (!visited[i] && isContainsCycleDfs(g, i, -1, visited)) {
                return true;// if we found a cycle return true
            }
        }
        // if no cycle is found after checking all vertices, return false
        return false;
    }


    // function to check if the graph contains a cycle using dfs
    bool Algorithms::isContainsCycleDfs(Graph& g, int vertex, int parent, std::vector<bool>& visited) {
        visited[static_cast<size_t>(vertex)] = true;// mark the current vertex as visited
        // loop through adjacent vertices
        for (size_t i = 0; i < g.getVertices(); i++) {
            // check if there is an edge to vertex i from the current vertex
            if (g.getMatrix()[static_cast<size_t>(vertex)][i]) {
                // If vertex i is not visited, recursively check for cycle for it
                if (!visited[i]) {
                    if (isContainsCycleDfs(g, i, vertex, visited)) {
                        return true;// cycle was found
                    }
                }
                    // If vertex i is visited and not the parent of current vertex it means that a cycle exists
                else if (i != parent) {
                    return true;// cycle was found
                }
            }
        }

        return false;// no cycle found after checking all vertices

    }



    std::string Algorithms::isBipartite(Graph& g) {
        // Check that the graph is not empty
        std::vector<std::vector<int>> matrix = g.getMatrix();
        if (matrix.empty()){
            return "0"; // Empty graph is not bipartite
        }
        size_t vertices = static_cast<size_t>(g.getVertices()); // Number of vertices in the graph
        std::vector<int> colors(vertices, -1); // Vector of colors for vertices, start all with -1 that indicates uncolored

        for (size_t start = 0; start < vertices; ++start) {
            if (colors[start] != -1) {
                continue; // Skip already colored vertices
            }

            colors[start] = 0; // Set the color of the starting vertex with 0
            std::queue<int> q; // Queue for BFS
            q.push(static_cast<int>(start)); // Push the starting vertex to the queue for BFS with the color of the first vertex

            // Perform BFS traversal
            while (!q.empty()) {
                size_t u = static_cast<size_t>(q.front()); // Get the front vertex from the queue (was added earliest to the queue)
                q.pop(); // Remove the vertex from the queue

                // Pass over all adjacent vertices of u
                for (size_t v = 0; v < vertices; ++v) {
                    // If there is an edge from u to v and v is uncolored, color it with the opposite color of u
                    if (matrix[u][v] && colors[v] == -1) {
                        colors[v] = 1 - colors[u]; // Color v with the opposite color of u
                        q.push(static_cast<int>(v)); // Push v to the queue to continue doing this on the graph
                    }
                        // If there is an edge from u to v and v is the same color as u, the graph is not bipartite
                    else if (matrix[u][v] && colors[v] == colors[u]) {
                        return "0"; // Not bipartite
                    }
                }
            }
        }

        // This part is to make the string of the bipartite graph
        std::string result = "The graph is bipartite: "; // The full string
        std::string groupA = "A={"; // String for 1 color
        std::string groupB = "B={"; // String for 2 color
        // Loop through all the vertices in the graph
        for (size_t i = 0; i < vertices; ++i) {
            if (colors[i] == 0) { // Vertices with color 0 belong to group A
                if (groupA.size() > 3) {
                    groupA += ",";
                }
                groupA += std::to_string(i); // Update group A
            } else if (colors[i] == 1) { // Vertices with color 1 belong to group B
                if (groupB.size() > 3) {
                    groupB += ",";
                }
                groupB += std::to_string(i); // Update group B
            }
        } // End of for
        groupA += "}";
        groupB += "}";
        result += groupA + ", " + groupB; // Sum the full string and then return it

        return result; // Return the full string
    }



    // function to check if there is a negative cycle in the graph
    bool Algorithms::negativeCycle(Graph& g) {
        //check that the graph not empty
        std::vector<std::vector<int>> matrix = g.getMatrix();
        if (matrix.empty()){
            std::cout << "No negative cycle found!" << std::endl; // no graph no negative cycle
            return false;//exit the function in this case
        }
        size_t vertices = static_cast<size_t>(g.getVertices());;// number of vertices in the graph
        // vectors for distances and parents
        std::vector<int> dist(vertices, INT_MAX); // vector for distances from the start vertex
        std::vector<int> parent(vertices, -1);    // vector for parent vertices in the shortest path

        size_t start = 0; // start vertex for bellman ford algorithm
        dist[start] = 0; // the distance from the start vertex to itself is 0

        // perform bellman ford algorithm to find shortest paths
        // loop v-1 times (v is the number of vertices in the graph)
        for (size_t i = 1; i < vertices; i++) {
            //goes through all the vertices in the graph and performs relaxation on each of them by the value of the edges.
            for (size_t u = 0; u < vertices; u++) {
                for (size_t v = 0; v < vertices; v++) {
                    // check if there is an edge from vertex u to vertex v and if a shorter path exists
                    if (g.getMatrix()[u][v] != 0 && dist[u] != INT_MAX && dist[u] + g.getMatrix()[u][v] < dist[v]) {
                        // update if shorter path found
                        dist[v] = dist[u] + g.getMatrix()[u][v]; // update distance
                        parent[v] = u; // update parent vertex
                    }
                }
            }
        }

        // check for negative cycles by performing relaxation 1 more time
        for (size_t u = 0; u < vertices; u++) {
            for (size_t v = 0; v < vertices; v++) {
                // if there is an edge from vertex u to vertex v and a shorter path exists, it means that a negative cycle is found
                if (g.getMatrix()[u][v] != 0 && dist[u] != INT_MAX && dist[u] + g.getMatrix()[u][v] < dist[v]) {
                    std::cout << "Negative cycle found!" << std::endl; // print that we found a negative cycle in the graph
                    return true; // exit the function when a negative cycle is found
                }
            }
        }

        std::cout << "No negative cycle found!" << std::endl; // print message that the graph dont have a negative cycle
   return false;
    }



} // end of namespace ariel
