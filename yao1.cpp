#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include <climits>
#include <fstream>

using namespace std;

struct Node {
    int vertex;
    int weight;

    Node(int v, int w) : vertex(v), weight(w) {}

    bool operator<(const Node& n) const {
        return weight > n.weight;  // For priority_queue to act as min-heap
    }
};

using Graph = unordered_map<int, vector<Node>>;

Graph loadGraph(const string& filename) {
    ifstream in(filename);
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

// Dijkstra's Algorithm
void uniformCostBestFirstSearch(const Graph& graph) {
    unordered_map<int, int> distances;
    for (const auto& pair : graph) {
        distances[pair.first] = INT_MAX;
    }
    distances[1] = 0;

    priority_queue<Node> pq;
    pq.push(Node(1, 0));

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        for (const Node& neighbor : graph.at(current.vertex)) {
            int newDist = distances[current.vertex] + neighbor.weight;
            if (newDist < distances[neighbor.vertex]) {
                distances[neighbor.vertex] = newDist;
                pq.push(Node(neighbor.vertex, newDist));
            }
        }
    }

    for (const auto& pair : distances) {
        cout << "Distance to " << pair.first << " = " << pair.second << endl;
    }
}

// BFS
void breadthFirstSearch(const Graph& graph, unordered_map<int, int>& distances) {
    unordered_map<int, bool> visited;
    for (const auto& pair : graph) {
        visited[pair.first] = false;
        distances[pair.first] = INT_MAX; // Set initial distances to a very high value
    }

    queue<int> q;
    q.push(1);
    distances[1] = 0;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        if (!visited[current]) {
            cout << "Visiting " << current << " with distance " << distances[current] << endl;
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
void depthFirstSearch(const Graph& graph, unordered_map<int, int>& distances) {
    unordered_map<int, bool> visited;
    for (const auto& pair : graph) {
        visited[pair.first] = false;
        distances[pair.first] = INT_MAX; // Set initial distances to a very high value
    }

    stack<int> s;
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
    Graph graph = loadGraph("test.txt");  // Example for 10-node graph
    cout << "Dijkstra's Algorithm Results:" << endl;
    uniformCostBestFirstSearch(graph);

    cout << "\nBFS Results:" << endl;
    unordered_map<int, int> bfsDistances;
    breadthFirstSearch(graph, bfsDistances);
    cout << "\nDFS Results:" << endl;
    unordered_map<int, int> dfsDistances;
    depthFirstSearch(graph, dfsDistances);


    return 0;
}