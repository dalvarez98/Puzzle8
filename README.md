# Puzzle8

Worked in a Team of Two to create an application that could solve the 8-puzzle problem and output the shortest number of moves to the goal state using Dijkstra’s, BFS, and DFS algorithms

To be able to run the program for Dijkstra and BFS use the command 
g++ -std=c++17 -Wall Graph.cpp  main.cpp

You need to go into main.cpp and comment out cost = g.dijkstraAlgo(path) if you wish to run BFS and same for opposite if you wish to dijkstra

To change the puzzle state go into puzzle.txt and change the puzzle to your desired state. Make sure to put the puzzle.txt file into the directory of the program so that the program can run correctly

DFS Folder contains different implementation code for DFS so have to be compiled and run seperately.
g++ -std=c++17 -Wall DFS.cpp  main.cpp
