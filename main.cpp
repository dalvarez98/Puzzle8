#include "Graph.hpp"

int main() {
    Graph g;
    Vertex *v;
    std::vector<Vertex*> path;
    int cost, i = 0, num;
    int initialS[SIZE];
    
    std::ifstream myFile ("puzzle.txt");
    if(myFile.is_open()) {
        while(myFile.good()) {
            myFile >> num;
            initialS[i] = num;
            i++;
        }
    }

    v = g.addVertex(initialS);
    
    cost = g.dijkstraAlgo(path);
    //cost = g.BFS(path);
    g.printPuzzle(path);
    std::cout << "Total Cost: " << cost << std::endl;
}