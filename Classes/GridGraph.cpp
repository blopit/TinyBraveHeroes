//
//  GridTile.cpp
//  TinyBraveHeroes
//
//  Created by Shrenil Patel on 2017-09-06.
//
//

#include "GridGraph.hpp"

using namespace std;

void GridGraph::addTile(Point id, int weight) {
    graph[id.x][id.y] = new GridTile(id, weight);
}

void GridGraph::addEdge(const Point from, const Point to, int work){
    if (from.x < 0 or from.y < 0 or from.x > COLUMNS-1 or from.y > ROWS-1 or
        to.x < 0 or to.y < 0 or to.x > COLUMNS-1 or to.y > ROWS-1) {
        return;
    }
    
    GridTile *g1 = graph[from.x][from.y];
    GridTile *g2 = graph[to.x][to.y];
    GridEdge e = *new GridEdge(g2, work);
    g1->edges.push_back(e);
    
    
}

GridGraph::GridGraph() {
    // Create 2D array of pointers:
    graph = new GridTile**[ROWS];
    for (int i = 0; i < ROWS; ++i) {
        graph[i] = new GridTile*[COLUMNS];
    }
    
    // Set the pointers contained in the array:
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLUMNS; ++j) {
            GridGraph::addTile(Point(i, j), 0);
        }
    }
    
    //NORTH
    
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLUMNS; ++j) {
            addEdge(Point(i,j), Point(i,j+1), 10);      // N
            addEdge(Point(i,j), Point(i+1,j+1), 15);    // NE
            addEdge(Point(i,j), Point(i+1,j), 10);      // E
            addEdge(Point(i,j), Point(i+1,j-1), 15);    // SE
            addEdge(Point(i,j), Point(i,j-1), 10);      // S
            addEdge(Point(i,j), Point(i-1,j-1), 15);    // SW
            addEdge(Point(i,j), Point(i-1,j), 10);      // W
            addEdge(Point(i,j), Point(i-1,j+1), 15);    // NW
        }
    }
    
    
    
}
