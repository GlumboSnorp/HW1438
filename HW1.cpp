#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <stdio.h>
#include <ctime>
#include <vector>
#include <iomanip>
using namespace std;

void typeSearch(int type);
void startD(string fileName, int type);
void startBFS(string fileName, int type);
void startDFS(string fileName, int type);

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

void startD(string fileName, int type){
    char car[] = "";
    string sizeI;
    int size = 0;
    int siz2 = 0;
    vector<string> arr;
    string line;
    string input;
    string quest;
    string rand;
    int count = 0;
    clock_t start, stop;  
    double createTime;
    ofstream ofs("dijkstra.txt");

    cout << "What is the target node?\n";
    cin >> input;
    cout << "Is " << input << " the correct target, yes or no?(lowercase)\n";
    cin >> quest;

    if(quest == "no"){
        startD(fileName, type);
    }else if(quest == "yes"){
        ifstream ifs;
        ifs.open(fileName);
    if (ifs.is_open()) {
        getline(ifs,sizeI);
        size = stoi(sizeI);
        cout << size << endl;
        while(getline(ifs, line)){
           cout << line << endl;
        }
        
    } else {
        cout << "Unable to open File\n";
        ofs.close();
        ifs.close();
        typeSearch(type);
    }
    cout <<"\n\n start of output \n";
    cout << line << endl;
    //createTime = (double)(stop - start) / CLOCKS_PER_SEC;
    cout << "Dijkstra's Algorith Created in " << createTime << " seconds\n";
    //dij.inorder(ofs);
    ofs.close();
    ifs.close();
    }else{
        cout << "Invalid input\n";
        startD(fileName, type);
    }
}

void startBFS(string fileName, int type){
    exit(1);
}

void startDFS(string fileName, int type){
    exit(1);
}










if (distances.find(neighbor.vertex) == distances.end()) {
                distances[neighbor.vertex] = numeric_limits<int>::max();
            }

            // Check if the current vertex exists in the graph
        if (graph.find(current.vertex) == graph.end()) {
            continue; // Skip if not found
        }