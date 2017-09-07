//
//  GridTile.cpp
//  TinyBraveHeroes
//
//  Created by Shrenil Patel on 2017-09-06.
//
//

#include "GridGraph.hpp"
#include "GameManager.hpp"

using namespace std;


cocos2d::Vec2 GridTile::getCoordinate() {
    return GridGraph::getCoordinate(location);
}

void GridGraph::addTile(Vec location, int weight) {
    graph[location.x][location.y] = new GridTile(location, weight);
}

void GridGraph::addEdge(const Vec from, const Vec to, int work){
    if (from.x < 0 or from.y < 0 or from.x > COLUMNS-1 or from.y > ROWS-1 or
        to.x < 0 or to.y < 0 or to.x > COLUMNS-1 or to.y > ROWS-1) {
        return;
    }
    
    auto *g1 = graph[from.x][from.y];
    auto *g2 = graph[to.x][to.y];
    GridEdge e = *new GridEdge(g2, work);
    g1->edges.push_back(e);
}

GridGraph::GridGraph() {
    
    // Create 2D array of Vecers:
    graph = new GridTile**[COLUMNS];
    for (auto i = 0; i < COLUMNS; ++i) {
        graph[i] = new GridTile*[ROWS];
    }
    
    // Set the Vecers contained in the array:
    for (auto i = 0; i < COLUMNS; ++i) {
        for (auto j = 0; j < ROWS; ++j) {
            GridGraph::addTile(Vec(i, j), 0);
        }
    }
    
    for (auto i = 0; i < COLUMNS; ++i) {
        for (auto j = 0; j < ROWS; ++j) {
            addEdge(Vec(i,j), Vec(i,j+1), 10);      // N
            addEdge(Vec(i,j), Vec(i+1,j+1), 15);    // NE
            addEdge(Vec(i,j), Vec(i+1,j), 10);      // E
            addEdge(Vec(i,j), Vec(i+1,j-1), 15);    // SE
            addEdge(Vec(i,j), Vec(i,j-1), 10);      // S
            addEdge(Vec(i,j), Vec(i-1,j-1), 15);    // SW
            addEdge(Vec(i,j), Vec(i-1,j), 10);      // W
            addEdge(Vec(i,j), Vec(i-1,j+1), 15);    // NW
        }
    }
}

GridTile* GridGraph::getTileAt(Vec at) {
    auto x = at.x;
    auto y = at.y;
    
    boundToRange(0, x, COLUMNS-1);
    boundToRange(0, y, ROWS-1);
    
    return graph[x][y];
}

 cocos2d::Vec2 GridGraph::getCoordinate(Vec location) {
    auto tileSize = GameManager::getInstance()->getTileSize();
    auto winWidth = cocos2d::Director::getInstance()->getWinSize().width;
    auto winHeight = cocos2d::Director::getInstance()->getWinSize().height;
    auto offsetx = (tileSize + winWidth) / 2;
    auto offsety = (tileSize + winHeight) / 2;
    
    auto x = offsetx + (location.x - 3) * tileSize;
    auto y = offsety + (location.y - 4) * tileSize;
     
    return cocos2d::Vec2(x, y);
}


unordered_map<GridTile*, GridTile*> breadthFirstSearch(const GridGraph& graph, GridTile* start, GridTile* goal) {

    queue<GridTile*> frontier;
    frontier.push(start);
    
    unordered_map<GridTile*, GridTile*> came_from;
    came_from[start] = start;
    
    while (!frontier.empty()) {
        auto current = frontier.front();
        frontier.pop();
        
        if (current == goal) {
            break;
        }
        
        for (auto& nextEdge : current->edges) {
            GridTile* nextTile = nextEdge.to;
            if (!came_from.count(nextTile)) {
                frontier.push(nextTile);
                came_from[nextTile] = current;
            }
        }
    }
    return came_from;
}

