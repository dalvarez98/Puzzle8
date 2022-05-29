#include "Graph.hpp"

Edge::Edge(Vertex *des, unsigned int long w) {
    destination = des;
    weight = w;
}

Vertex::Vertex() {
    label = 0;
    distance = -1;
    visited = false;
}

Graph::Graph() {
    numCol = 3;
}

Graph::~Graph() {
    unsigned int i;

    for(i = 0; i < vertices.size(); i++) {
        delete vertices.at(i);
    }

    vertices.clear();
}

//Checks if the Vertexes puzzle is the goal state
bool Vertex::isGoalState() {
    unsigned int i;
    bool goal = true;
    int goalS[SIZE] = {1, 2, 3, 8, 0, 4, 7, 6, 5};

    for(i = 0; i < SIZE; i++) {
        if(puzzle8[i] != goalS[i])
            goal = false;
    }

    return goal;
}

bool Vertex::operator==(const Vertex& rhs) const {

    return (getLabel() == rhs.getLabel());
}

unsigned int long Edge::getWeight() const {
    return weight;
}

Vertex* Edge::getDestination() {
    return destination;
}

void Vertex::setLabel(int a) {
    label = a;
}

void Vertex::setDistance(unsigned long d) {
    distance = d;
}

void Vertex::setHeuristic(int a) {
    numDisplaced = a;
}

void Vertex::setParent(Vertex *p) {
    parent = p;
}

void Vertex::setVisited(bool v) {
    visited = v;
}

int Vertex::getLabel() const {
    return label;
}

unsigned long Vertex::getDistance() const {
    return distance;
}

int Vertex::getHeuristic() const {
    return numDisplaced;
}

Vertex* Vertex::getParent() {
    return parent;
}

const int* Vertex::getPuzzle() const {
    return puzzle8;
}

bool Vertex::getVisited() const {
    return visited;
}

int Graph::getNumCol() const {
    return numCol;
}

//Adds a Vertex Object to vertices, sets the label of the Vertex, and returns the created Vertex
Vertex* Graph::addVertex(int origPuzz[]) {
    unsigned int i, temp = 0;
    int goalS[SIZE] = {1, 2, 3, 8, 0, 4, 7, 6, 5};
    Vertex *newV = new Vertex();
    newV->setLabel(vertices.size());
    newV->setDistance(std::numeric_limits<unsigned long>::max()); //Basically Infinity
    
    //Copys origPuzz into newV puzzle either being left, right, up, or down state
    for(i = 0; i < SIZE; i++) {
        newV->puzzle8[i] = origPuzz[i];
        if(newV->puzzle8[i] != goalS[i])
            temp++;
    }

    newV->setHeuristic(temp);
    vertices.push_back(newV);

    return newV;
}

//Adds an Edge to the Adjacency List based on the given Vertexes
void Graph::addEdge(Vertex *start, Vertex *des, unsigned int long weight) {
    unsigned int i;
    Edge *e1 = new Edge(des, weight);
    Edge *e2 = new Edge(start, weight);

    des->setParent(start);

    //Compares two Vertexes by label and creates the edges for them
    for(i = 0; i < vertices.size(); i++) {
        if(vertices.at(i) == start)
            start->adjaList.push_back(e1);
        if(vertices.at(i) == des)
            des->adjaList.push_back(e2);
    }
}


//Finds the shortestPath of the graph for an 8 puzzle solution using Dijkstra's Algorithm
//Returns the total distance weight of the path and stores the path taken in the vector path
unsigned long Graph::dijkstraAlgo(std::vector<Vertex*> &path) {
    //PQ used to sort each Vertex based on lowest weight using Dijkstra's Algorithm
    std::priority_queue<std::pair<unsigned long, Vertex*>, std::vector<std::pair<unsigned long, Vertex*> >, 
                        std::greater<std::pair<unsigned long, Vertex*> > > pathS;
    Vertex *temp, *goalState, *currEdge;
    int x, moves = 0;
    unsigned int i;
    unsigned long distanceTotal, weight;
    bool goalFound = false;

    pathS.push(std::make_pair(0, vertices.front())); //Pushing first Vertex into PQ
    vertices.front()->setDistance(0);
    moves++;

    //Goes through Graph finding the shortest distance from the initialS to 
    //every other Vertex and stores the distance of each finding the best path to goalS
    while(!pathS.empty() && !goalFound) {
        temp = pathS.top().second;
        pathS.pop();
        moves++;
        //Finds blank space in puzzle to be used to generate possible moves
        for(i = 0; i < SIZE; i++) {
            if(temp->getPuzzle()[i] == 0) {
                x = i;
            }
        }

        //Creates vertices based on possible movements using blank space in puzzle
        moveLeft(temp, x);
        moveUp(temp, x);
        moveRight(temp, x);
        moveDown(temp, x);

        //Loops through the edges associated with the Vertex
        for(i = 0; i < temp->adjaList.size(); i++) {
            currEdge = temp->adjaList.at(i)->getDestination();
            //Finds out if adj vertex is the goalState of 8 puzzle
            if(currEdge->isGoalState()) {
                std::cout << "Number of moves: " << moves << std::endl;
                std::cout << "\nPath to Goal State Found:\n" << std::endl;
                goalFound = true;
                goalState = currEdge;
            }

            weight = temp->adjaList.at(i)->getWeight();
            
            //Checking if curr neighbor has a greater distance than curr Vertex
            if(currEdge->getDistance() > (temp->getDistance() + weight + currEdge->getHeuristic())) {
                currEdge->setDistance(temp->getDistance() + weight);
                pathS.push(std::make_pair(currEdge->getDistance() + currEdge->getHeuristic(), currEdge));
            }
        }
    }
    
    distanceTotal = goalState->getDistance();
    
    //creates the path to goalState of 8 puzzle by backtracking using parent
    Vertex *v = goalState;
    while(v->getLabel() != vertices.at(0)->getLabel()) {
        path.push_back(v);
        
        v = v->getParent();
    }
    path.push_back(vertices.at(0));

    std::reverse(path.begin(), path.end());

    return distanceTotal;
}

//Finds path to 8 puzzle solution using BFS Algorithm
unsigned long Graph::BFS(std::vector<Vertex*> &path) {
    Vertex *currVertex, *currEdge;
    std::deque<Vertex*> discovered;
    int x, moves = 0;
    unsigned long distance = 0;
    
    //Pushing initialState into queue
    vertices.front()->setVisited(true);
    discovered.push_back(vertices.front());
    moves++;
    bool goalFound = false;

    //Goes from initial Puzzle state and finds the goalState using BFS
    while(!discovered.empty() && !goalFound) {
        currVertex = discovered.front();
        discovered.pop_front();
        moves++;
        //Finds blank space in puzzle to be used to generate possible moves
        for(int i = 0; i < SIZE; i++) {
            if(currVertex->getPuzzle()[i] == 0) {
                x = i;
            }
        }

        //Creates vertices based on possible movements using blank space in puzzle
        moveLeft(currVertex, x);
        moveUp(currVertex, x);
        moveRight(currVertex, x);
        moveDown(currVertex, x);

        //For every adj vertex checks if it is goalState and if it was visited or not pushing to queue if not
        for(int i = 0; i < currVertex->adjaList.size(); i++) {
            currEdge = currVertex->adjaList.at(i)->getDestination();
            if(currEdge->isGoalState()) {
                std::cout << "Number of moves: " << moves << std::endl;
                std::cout << "\nPath to Goal State Found:\n" << std::endl;
                goalFound = true;
                distance = pathTrace(path, currEdge);
                std::reverse(path.begin(), path.end());
            }

            //checks if adj vertex is not visited
            if(!currEdge->getVisited()) {
                currEdge->setVisited(true);
                discovered.push_back(currEdge);
            }
        }
    }
    return distance;
}

//Retraces the path from the goalState to the initial state
unsigned long Graph::pathTrace(std::vector<Vertex*> &q, Vertex *v) {
    unsigned long count = 0;
    while (v != NULL) {
        q.push_back(v);
        v = v->getParent();
        count++;
    }
    return --count;
}

//Prints the path of puzzles to the goalState
void Graph::printPuzzle(std::vector<Vertex*> path) {
    unsigned int i, j;

    for(i = 0; i < path.size(); i++) {
        for(j = 0; j < SIZE; j++) {
            std::cout << path.at(i)->getPuzzle()[j] << " ";
            if(j == 2 || j == 5 || j == 8)
                std::cout << "" << std::endl;
        }
        std::cout << "\n";
    }
}

//Creates a possible Right state movement of current vertex 8 puzzle
void Graph::moveRight(Vertex *p, int blankIndex) {
    unsigned int i;
    int temp;

    //Checks if Right move is possible then creates puzzle state if true
    if(blankIndex % getNumCol() < getNumCol() - 1) {
        int newPuzz[SIZE];

        for(i = 0; i < SIZE; i++) {
            newPuzz[i] = p->getPuzzle()[i];
        }
        
        temp = newPuzz[blankIndex + 1];
        newPuzz[blankIndex + 1] = newPuzz[blankIndex];
        newPuzz[blankIndex] = temp;

        Vertex *v = addVertex(newPuzz);
        addEdge(p, v, temp);
    }
}

//Creates a possible Left state movement of current vertex 8 puzzle
void Graph::moveLeft(Vertex *p, int blankIndex) {
    unsigned int i;
    int temp;
    Vertex *v;

    //Checks if Left move is possible then creates puzzle state if true
    if(blankIndex % getNumCol() > 0) {
        int newPuzz[SIZE];
        for(i = 0; i < SIZE; i++) {
            newPuzz[i] = p->getPuzzle()[i];
        }
        
        temp = newPuzz[blankIndex - 1];
        newPuzz[blankIndex - 1] = newPuzz[blankIndex];
        newPuzz[blankIndex] = temp;
        
        v = addVertex(newPuzz);
        addEdge(p, v, temp);
    }
}

//Creates a possible Up state movement of current vertex 8 puzzle
void Graph::moveUp(Vertex *p, int blankIndex) {
    unsigned int i;
    int temp;

    //Checks if Up move is possible then creates puzzle state if true
    if(blankIndex - getNumCol() >= 0) {
        int newPuzz[SIZE];

        for(i = 0; i < SIZE; i++) {
            newPuzz[i] = p->getPuzzle()[i];
        }
        
        temp = newPuzz[blankIndex - getNumCol()];
        newPuzz[blankIndex - getNumCol()] = newPuzz[blankIndex];
        newPuzz[blankIndex] = temp;

        Vertex *v = addVertex(newPuzz);
        addEdge(p, v, temp);
    }
}

//Creates a possible Down state movement of current vertex 8 puzzle
void Graph::moveDown(Vertex *p, int blankIndex) {
    unsigned int i;
    int temp;

    //Checks if Down move is possible then creates puzzle state if true
    if(blankIndex + getNumCol() < 9) {
        int newPuzz[SIZE];

        for(i = 0; i < SIZE; i++) {
            newPuzz[i] = p->getPuzzle()[i];
        }
        
        temp = newPuzz[blankIndex + getNumCol()];
        newPuzz[blankIndex + getNumCol()] = newPuzz[blankIndex];
        newPuzz[blankIndex] = temp;

        Vertex *v = addVertex(newPuzz);
        addEdge(p, v, temp);
    }
}