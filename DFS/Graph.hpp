#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <limits>
#include <algorithm>
#include <stack>
#include <fstream>

#define SIZE 9

class Vertex;

class Edge {

    public:
        Edge(Vertex *des, unsigned int long w);
        unsigned int long getWeight() const;
        Vertex* getDestination();
    private:
        friend class Graph;
        Vertex *destination;
        unsigned int long weight;
};

class Vertex {
    
    public:
        Vertex();
        bool isGoalState();
        bool operator==(const Vertex& rhs) const;
        void setLabel(int a);
        void setDistance(unsigned long d);
        void setParent(Vertex *p);
        void setVisited(bool v);
        int getLabel() const;
        unsigned long getDistance() const;
        Vertex* getParent();
        const int* getPuzzle() const;
        bool getVisited() const;
    private:
        friend class Graph;
        int label; //Used to compare Vertexes
        bool visited;
        std::vector<Edge*> adjaList;
        int puzzle8 [SIZE]; //Puzzle state of each Vertex
        Vertex *parent; //Used to Get Shortest Path
        unsigned long distance;
};

class Graph {
    
    public:
        Graph();
        ~Graph(); //Deconstructor
        int getNumCol() const;
        Vertex* addVertex_Dfs(int origPuzz[]);
        void addEdge(Vertex *start, Vertex *des, unsigned int long weight);
        void test(int a[]);
       void moveRight(Vertex *p, int blankInde);
        void moveLeft(Vertex *p, int blankIndex);
       void moveUp(Vertex *p, int blankIndex);
        void moveDown(Vertex *p, int blankIndex);
        unsigned long shortestPath(std::vector<Vertex*> &path);
        unsigned long BFS(std::vector<Vertex*> &path);
        unsigned long pathTrace(std::vector<Vertex*> &q, Vertex *v);
        unsigned long Dfs(std::vector<Vertex*>&path);
        unsigned long printPath(std::vector<Vertex*> &path, Vertex* v);
        void printPuzzle(std::vector<Vertex*> path);
      
    private:
        std::vector<Vertex*> vertices; //Vertex List
        std::map<int, Vertex*> currVert; //Creating a map of the vertices for easier access
        int numCol;
};

#endif
