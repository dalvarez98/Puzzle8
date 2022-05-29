# Puzzle8

To be able to run the program for Dijkstra and BFS use the command 
g++ -std=c++17 -Wall Graph.cpp  main.cpp

Need to go into main.cpp and comment out cost = g.dijkstraAlgo(path) if you wish to run BFS and same for opposite if you wish to dijkstra

To change the puzzle state go into puzzle.txt and change the puzzle to desired state. Make sure to put puzzle.txt into directory of program so that program can run correctly

DFS Folder contains different implementation code for DFS so have to be compiled and run seperately.
g++ -std=c++17 -Wall DFS.cpp  main.cpp
