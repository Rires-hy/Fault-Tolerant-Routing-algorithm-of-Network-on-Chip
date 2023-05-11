#ifndef __NOXIMUPDOWN_H__
#define __NOXIMUPDOWN_H__
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <stack>
#include <queue>
#include <map>
#include <vector>
#define NO_INCOMING_INDEX   999999

class Node {
public:
    int id;
    int x;
    int y;
    bool visited;
    std::map<int,Node*> neighbors;
    std::vector<Node*> up;
    std::vector<Node*> down;

    Node(int x,int y,int length) :x(x),y(y), visited(false) {id = x*length+y;}
};

enum DOWNUP {
    DOWN, UP
};

class Graph {
public:
    std::map<int,Node*> nodes;
    std::vector<int> tempPath;
    int size=0;
    
    Graph();

    std::vector<std::vector<int>> readFileMap();
    bool downContain(int currentIndex,int findIndex);
    DOWNUP findPath(int currentIndex,int findIndex,int comingIndex);

    void addEdge(int u, int v, int DIREC);
    void dfsSpanningTree(int startNodeId);
    void bfsSpanningTree(int startNodeId);
    void build(int choice);
};



#endif