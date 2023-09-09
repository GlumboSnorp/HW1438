#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include <climits>
#include <fstream>

struct Node {
    int vertex;
    int weight;

    Node(int v, int w) : vertex(v), weight(w) {}

    bool operator<(const Node& n) const {
        return weight > n.weight;  // For priority_queue to act as min-heap
    }
};

using Graph = std::unordered_map<int, std::vector<Node>>;

Graph loadGraph(const std::string& filename) {
    std::ifstream in(filename);
    Graph graph;

    int numVertices;
    in >> numVertices;

    int vertex, neighbor, weight;
    for (int i = 0; i < numVertices; ++i) {
        in >> vertex;
        while (in.peek() != '\n' && !in.eof()) {
            in >> neighbor >> weight;
            graph[vertex].push_back(Node(neighbor, weight));
        }
    }
    return graph;
}
// Function to display the path from start node to target node
void displayPath(const std::unordered_map<int, int>& prev, int target) {
    std::stack<int> path;
    int node = target;

    while (node != -1) {
        path.push(node);
        node = prev.at(node);
    }

    std::cout << "Path: ";
    while (!path.empty()) {
        std::cout << path.top();
        path.pop();
        if (!path.empty()) {
            std::cout << " -> ";
        }
    }
    std::cout << std::endl;
}

// Dijkstra's Algorithm
std::unordered_map<int, int> uniformCostBestFirstSearch(const Graph& graph, int start, int goal) {
    std::unordered_map<int, int> prev;
    std::unordered_map<int, int> distances;

    for (const auto& pair : graph) {
        distances[pair.first] = INT_MAX;
        prev[pair.first] = -1;  // Initialize with -1 to represent no predecessor
    }
    distances[start] = 0;

    std::priority_queue<Node> pq;
    pq.push(Node(start, 0));

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        for (const Node& neighbor : graph.at(current.vertex)) {
            int newDist = distances[current.vertex] + neighbor.weight;
            if (newDist < distances[neighbor.vertex]) {
                distances[neighbor.vertex] = newDist;
                prev[neighbor.vertex] = current.vertex;  // Set the predecessor
                pq.push(Node(neighbor.vertex, newDist));
            }
        }
    }

    for (const auto& pair : distances) {
        std::cout << "Distance to " << pair.first << " = " << pair.second << std::endl;
    }
    return prev; // Return the predecessor map
}


// BFS
void breadthFirstSearch(const Graph& graph, std::unordered_map<int, int>& distances) {
    std::unordered_map<int, bool> visited;
    for (const auto& pair : graph) {
        visited[pair.first] = false;
        distances[pair.first] = INT_MAX; // Set initial distances to a very high value
    }

    std::queue<int> q;
    q.push(1);
    distances[1] = 0;
    
    while (!q.empty()) {
        int current = q.front();
        q.pop();

        if (!visited[current]) {
            std::cout << "Visiting " << current << " with distance " << distances[current] << std::endl;
            visited[current] = true;

            for (const Node& neighbor : graph.at(current)) {
                if (!visited[neighbor.vertex] && distances[neighbor.vertex] == INT_MAX) { // This check ensures we don't update distances for already explored paths
                    q.push(neighbor.vertex);
                    distances[neighbor.vertex] = distances[current] + neighbor.weight;
                }
            }
        }
    }
}

// DFS
void depthFirstSearch(const Graph& graph, std::unordered_map<int, int>& distances) {
    std::unordered_map<int, bool> visited;
    for (const auto& pair : graph) {
        visited[pair.first] = false;
        distances[pair.first] = INT_MAX; // Set initial distances to a very high value
    }

    std::stack<int> s;
    s.push(1);
    distances[1] = 0;

    while (!s.empty()) {
        int current = s.top();
        s.pop();

        if (!visited[current]) {
            std::cout << "Visiting " << current << " with distance " << distances[current] << std::endl;
            visited[current] = true;

            for (const Node& neighbor : graph.at(current)) {
                if (!visited[neighbor.vertex]) {
                    s.push(neighbor.vertex);
                    if (distances[neighbor.vertex] == INT_MAX) { // This check ensures we don't update distances for already explored paths
                        distances[neighbor.vertex] = distances[current] + neighbor.weight;
                    }
                }
            }
        }
    }
}

int main() {
    int target = 0;
    Graph graph = loadGraph("graphPosMes.txt");  // Example for 10-node graph
    std::cout << "What is target: ";
    std::cin >> target;

    std::cout << "Dijkstra's Algorithm Results:" << std::endl;
    std::unordered_map<int, int> prev = uniformCostBestFirstSearch(graph, 1, target); // Assuming 1 as the start node
    displayPath(prev, target); // Now this should work

    std::cout << "\nBFS Results:" << std::endl;
    std::unordered_map<int, int> bfsDistances;
    breadthFirstSearch(graph, bfsDistances);
    std::cout << "\nDFS Results:" << std::endl;
    std::unordered_map<int, int> dfsDistances;
    depthFirstSearch(graph, dfsDistances);

    return 0;
}
//I added tracking the specified node and displaying the path on the best search algorithm. I successfully run this code on the siue server
