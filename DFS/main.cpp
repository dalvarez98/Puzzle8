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

    g.addVertex_Dfs(initialS);
    
    
   
    cost = g.Dfs(path);
    std::cout << "Total Cost: " << cost << std::endl;
}
