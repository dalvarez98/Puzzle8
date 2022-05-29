#include "Graph.hpp"
#define MAX_DEPTH 20

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
Vertex* Graph::addVertex_Dfs(int origPuzz[]) {
    unsigned int i, j;
    bool exists = false;
    Vertex *newV = new Vertex();
    Vertex *oldV = new Vertex();
    newV->setLabel(vertices.size());
    newV->setDistance(std::numeric_limits<unsigned long>::max()); //Basically Infinity
    currVert[newV->getLabel()] = newV;
    
    for(i = 0; i < SIZE; i++) {
        newV->puzzle8[i] = origPuzz[i];
    }
    
    // Detect if such puzzle is already in vertices
   if(!vertices.empty()){
    	for(i = 0; i < vertices.size(); i++) {
    		exists = true;
        	oldV = vertices.at(i);
        	for (j = 0; j < SIZE; j++){
        		if(oldV->getPuzzle()[j]!=newV->getPuzzle()[j]){
        			exists = false;
				}
			}
			if(exists){
				return oldV;
			}
        }
    }
    
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




unsigned long Graph::Dfs(std::vector<Vertex*>&path)
{

     std::stack<Vertex*>newV;
    Vertex *temp, *goalState, *curr;
    int a, x, depth=0;
    unsigned int i;
    unsigned long distanceTotal=0, moves;
    bool goalFound = false;

    newV.push(vertices.front());
    vertices.front()->setVisited(true);
    moves++;
    while(!newV.empty() && !goalFound) {
        temp = newV.top();
        newV.pop();
          moves++;
        //Finds blank space in puzzle to be used to generate possible moves
        for(i = 0; i < SIZE; i++) {
            if(temp->getPuzzle()[i] == 0) {
                x = i;
            }
        }

        //Creates vertices based on possible movements using blank space in puzzle
        moveDown(temp, x);
        moveLeft(temp, x);
        moveRight(temp, x);
        moveUp(temp, x);
      
			
			for(i = 0; i < temp->adjaList.size(); i++) {
				
			    curr = temp->adjaList.at(i)->getDestination();
            	
				if(curr->isGoalState()) {
	                std::cout << "Goal State Found:\n" << std::endl;
	                goalFound = true;
	                goalState = curr;
                    distanceTotal =  printPath(path, goalState);
                    std::reverse(path.begin(), path.end());
                   break;
                
            	}
            	if (!curr->getVisited()){//check if the vertex is already visited, if not push into the stack
                    curr->setVisited(true);
                 
            		newV.push(curr);
				}
            	 
			}
             
		
	}
     
    
    return distanceTotal;//return totat distance
    
}
//print the path to the goal state
unsigned long Graph::printPath(std::vector<Vertex*>&path, Vertex* v)
{
    unsigned long count=0;

   while (v != NULL) {
        path.push_back(v);
        v=v->getParent();
     
      
       count++;
       
       if(count>MAX_DEPTH)// this is set to avoid stack overflow
      {
            break;
       }
      
    }
   
  printPuzzle(path);
    return --count;
    
}
//function to print puzzle
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


//Creates a possible right state movement of current vertex 8 puzzle
void Graph::moveRight(Vertex *p, int blankIndex) {
    unsigned int i;
    int temp;
    int moves;
    if(blankIndex % getNumCol() < getNumCol() - 1) {
        int newPuzz[SIZE];

        for(i = 0; i < SIZE; i++) {
            newPuzz[i] = p->getPuzzle()[i];
        }
        
        temp = newPuzz[blankIndex + 1];
        newPuzz[blankIndex + 1] = newPuzz[blankIndex];
        newPuzz[blankIndex] = temp;

        Vertex *v = addVertex_Dfs(newPuzz);
        addEdge(p, v, temp);
        
    }
   
}

//Creates a possible left state movement of current vertex 8 puzzle
void Graph::moveLeft(Vertex *p, int blankIndex) {
    unsigned int i;
    int temp;
    Vertex *v;
    int moves=0;;
    if(blankIndex % getNumCol() > 0) {
        int newPuzz[SIZE];
        for(i = 0; i < SIZE; i++) {
            newPuzz[i] = p->getPuzzle()[i];
        }
        
        temp = newPuzz[blankIndex - 1];
        newPuzz[blankIndex - 1] = newPuzz[blankIndex];
        newPuzz[blankIndex] = temp;
        
        v = addVertex_Dfs(newPuzz);
        addEdge(p, v, temp);
        
    }
}

//Creates a possible Up state movement of current vertex 8 puzzle
void Graph::moveUp(Vertex *p, int blankIndex) {
    unsigned int i;
    int temp;
    int moves;
    if(blankIndex - getNumCol() >= 0) {
        int newPuzz[SIZE];

        for(i = 0; i < SIZE; i++) {
            newPuzz[i] = p->getPuzzle()[i];
        }
        
        temp = newPuzz[blankIndex - getNumCol()];
        newPuzz[blankIndex - getNumCol()] = newPuzz[blankIndex];
        newPuzz[blankIndex] = temp;

        Vertex *v = addVertex_Dfs(newPuzz);
        addEdge(p, v, temp);
        
    }
    
}

//Creates a possible Down state movement of current vertex 8 puzzle
void Graph::moveDown(Vertex *p, int blankIndex) {
    unsigned int i;
    int temp;
    int moves;
    if(blankIndex + getNumCol() < 9) {
        int newPuzz[SIZE];

        for(i = 0; i < SIZE; i++) {
            newPuzz[i] = p->getPuzzle()[i];
        }
        
        temp = newPuzz[blankIndex + getNumCol()];
        newPuzz[blankIndex + getNumCol()] = newPuzz[blankIndex];
        newPuzz[blankIndex] = temp;

        Vertex *v = addVertex_Dfs(newPuzz);
        addEdge(p, v, temp);
       
    }
   
}


