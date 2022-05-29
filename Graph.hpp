#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <map>
#include <stack>
#include <set>
#include <queue>
#include <limits>
#include <algorithm>
#include <iostream>
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
        void setHeuristic(int a);
        void setParent(Vertex *p);
        void setVisited(bool v);
        int getLabel() const;
        unsigned long getDistance() const;
        int getHeuristic() const;
        Vertex* getParent();
        const int* getPuzzle() const;
        bool getVisited() const;
    private:
        friend class Graph;
        int label; //Used to compare Vertexes
        int numDisplaced;
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
        Vertex* addVertex(int origPuzz[]);
        void addEdge(Vertex *start, Vertex *des, unsigned int long weight);
        void test(int a[]);
        void moveRight(Vertex *p, int blankIndex);
        void moveLeft(Vertex *p, int blankIndex);
        void moveUp(Vertex *p, int blankIndex);
        void moveDown(Vertex *p, int blankIndex);
        void printPuzzle(std::vector<Vertex*> path);
        unsigned long dijkstraAlgo(std::vector<Vertex*> &path);
        unsigned long BFS(std::vector<Vertex*> &path);
        unsigned long pathTrace(std::vector<Vertex*> &q, Vertex *v);
    private:
        std::vector<Vertex*> vertices; //Vertex List
        int numCol;
};

#endif