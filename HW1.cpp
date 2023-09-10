#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <stdio.h>
#include <ctime>
#include <vector>
#include <iomanip>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <climits>
#include <stack>
#include <chrono>
using namespace std;

void typeSearch(int type);
void startD(string fileName, int type);
void startBFS(string fileName, int type);
void startDFS(string fileName, int type);
unordered_map<int, int> dijkstra(const vector<vector<pair<int, int>>> &graph, int source, int target, unordered_map<int, int> &parent);



int main(){
    string input = "";
    cout << "What type of search would you like to perform?\n1: Dijkstra\n2: BFS\n3: DFS\n0:Exit"<< endl;
    cin >> input;
    cout << "Is the choice " << input << endl;

    if(stoi(input) == 1){
        typeSearch(1);
    }else if(stoi(input) == 2){
        typeSearch(2);
    }else if(stoi(input) == 3){
        typeSearch(3);
    }else if(stoi(input) == 0){
        exit(1);
    }else{
        cout << "Invalid Choice! Try Again.\n";
        main();
    }
    
    return 0;
}

void typeSearch(int type){                                                                     
    string input = "";
    string input2 = "";
    cout << "Which file would you like to upload?\n";
    cin >> input;
    cout << "The file you would like to upload is: " << input << "\nIs this correct? yes or no (this is case sensitive)\n";
    cin >> input2;

    if(input2 == "yes"){
        if(type == 1){
            startD(input, type);
        }else if(type == 2){
            startBFS(input,type);
        }else if(type == 3){
            startDFS(input,type);
        }else{
            cout << "This Error should have been caught earlier, sorry for the trouble\n";
            main();
        }
    }else if(input2 == "no"){
        cout << "Please restart the file input process\n";
        typeSearch(type);
    }else{
        cout << "Either the input is in the wrong case or it is an invalid input, regardless try again.\n";
        typeSearch(type);
    }
}

unordered_map<int, int> dijkstra(
    const vector<vector<pair<int, int>>> &graph,
    int source,
    int target,
    unordered_map<int, int> &parent 
) {
    unordered_map<int, int> distances;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    distances[source] = 0;
    pq.push({0, source});
    parent[source] = -1;  

    while (!pq.empty()) {
        int dist = pq.top().first;
        int curNode = pq.top().second;
        pq.pop();

        if (distances.find(curNode) != distances.end() && dist > distances[curNode]) {
            continue;
        }

        if (curNode == target) {
            break;
        }

        for (const auto &neighbor : graph[curNode]) {
            int nextNode = neighbor.first;
            int edgeWeight = neighbor.second;

            
            if (distances.find(nextNode) == distances.end()) {
                distances[nextNode] = INT_MAX;
            }

            if (dist + edgeWeight < distances[nextNode]) {
                distances[nextNode] = dist + edgeWeight;
                pq.push({distances[nextNode], nextNode});
                parent[nextNode] = curNode;  
            }
        }
    }

    return distances;
}


void startD(string fileName, int type){
ifstream ifs(fileName);
if (!ifs.is_open()) {
    cout << "Unable to open file\n";
    return;
}

int size;
ifs >> size;

if (size <= 0) {
    cout << "Invalid graph size\n";
    return;
}


vector<vector<pair<int, int>>> graph(size + 1);

int vertex, neighbor, weight;
while (ifs >> vertex) {
    if (vertex <= 0 || vertex > size) {
        cout << "Invalid vertex index\n";
        return;
    }

    while (ifs.peek() != '\n' && !ifs.eof()) {
        ifs >> neighbor >> weight;

        if (neighbor <= 0 || neighbor > size) {
            cout << "Invalid neighbor index\n";
            return;
        }

        graph[vertex].push_back({neighbor, weight});
    }
}

    int target;
    cout << "What is the target node?\n";
    cin >> target;

    string quest;
    cout << "Is " << target << " the correct target, yes or no?(lowercase)\n";
    cin >> quest;

    if (quest == "no") {
        startD(fileName, type);
        return;
    }

    if (quest != "yes") {
        cout << "Invalid input\n";
        startD(fileName, type);
        return;
    }

    int source = 1;  
    unordered_map<int, int> parent;

    auto start = std::chrono::high_resolution_clock::now();  // Start the timer
    
    auto distances = dijkstra(graph, source, target, parent);

    auto stop = std::chrono::high_resolution_clock::now();  // Stop the timer
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    cout << "Time taken by Dijkstra: " << duration.count() << " microseconds" << endl;

    if (distances.find(target) != distances.end()) {
        cout << "Shortest distance to target is: " << distances[target] << endl;

        vector<int> path;
        for (int v = target; v != -1; v = parent[v]) {
            path.push_back(v);
        }
        reverse(path.begin(), path.end());

        cout << "Path: ";
        for (int v : path) {
            cout << v << " ";
        }
        cout << endl;
        main();
    } else {
        cout << "No path from source to target" << endl;
        main();
    }
}


void startBFS(string fileName, int type){
    ifstream ifs(fileName);
    if (!ifs.is_open()) {
        cout << "Unable to open file\n";
        return;
    }

    int size;
    ifs >> size;
    if (size <= 0) {
        cout << "Invalid graph size\n";
        return;
    }

    vector<vector<pair<int, int>>> graph(size + 1);
    int vertex, neighbor, weight;
    while (ifs >> vertex) {
        while (ifs.peek() != '\n' && !ifs.eof()) {
            ifs >> neighbor >> weight;
            graph[vertex].push_back({neighbor, weight});
        }
    }

    int source = 1;  
    int target;
    cout << "what is the target node?\n ";
    cin >> target;

    unordered_map<int, bool> visited;
    unordered_map<int, int> parent;
    //unordered_map<int, int> distance;
    queue<int> q;

    auto start = std::chrono::high_resolution_clock::now();
    q.push(source);
    visited[source] = true;
    parent[source] = -1;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        if (current == target) {
            break;
        }

        for (const auto &neighbor : graph[current]) {
            if (!visited[neighbor.first]) {
                q.push(neighbor.first);
                visited[neighbor.first] = true;
                parent[neighbor.first] = current;
                
            }
        }
    }
    auto stop = std::chrono::high_resolution_clock::now();  // Stop the timer
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    if (!visited[target]) {
        cout << "No path from source to target.\n";
        return;
    }

   
    cout << "Time taken by BFS: " << duration.count() << " microseconds" << endl;

    
    stack<int> path;
    for (int v = target; v != -1; v = parent[v]) {
        path.push(v);
    }

    cout << "Path: ";
    while (!path.empty()) {
        cout << path.top() << ' ';
        path.pop();
    }
    cout << endl;
    main();
}

void startDFS(string fileName, int type){
        ifstream ifs(fileName);
    if (!ifs.is_open()) {
        cout << "Unable to open file\n";
        return;
    }

    int size;
    ifs >> size;
    if (size <= 0) {
        cout << "Invalid graph size\n";
        return;
    }

    vector<vector<pair<int, int>>> graph(size + 1);
    int vertex, neighbor, weight;
    while (ifs >> vertex) {
        while (ifs.peek() != '\n' && !ifs.eof()) {
            ifs >> neighbor >> weight;
            graph[vertex].push_back({neighbor, weight});
        }
    }

    int source = 1;  
    int target;
    cout << "what is the target node?\n ";
    cin >> target;

    unordered_map<int, bool> visited;
    unordered_map<int, int> parent;

    stack<int> q;

    auto start = std::chrono::high_resolution_clock::now();
    q.push(source);
    visited[source] = true;
    parent[source] = -1;

    while (!q.empty()) {
        int current = q.top();
        q.pop();

        if (current == target) {
            break;
        }

        for (auto neighbor_it = graph[current].rbegin(); neighbor_it != graph[current].rend(); ++neighbor_it) {
            int neighbor = neighbor_it->first;
            if (!visited[neighbor]) {
                q.push(neighbor);
                visited[neighbor] = true;
                parent[neighbor] = current;
                
            }
        }
    }
    auto stop = std::chrono::high_resolution_clock::now();  // Stop the timer
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    if (!visited[target]) {
        cout << "No path from source to target.\n";
        return;
    }

   
    cout << "Time taken by DFS: " << duration.count() << " microseconds" << endl;

    
    stack<int> path;
    for (int v = target; v != -1; v = parent[v]) {
        path.push(v);
    }

    cout << "Path: ";
    while (!path.empty()) {
        cout << path.top() << ' ';
        path.pop();
    }
    cout << endl;
    main();
}



