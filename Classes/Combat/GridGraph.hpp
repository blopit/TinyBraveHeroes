//
//  GridTile.hpp
//  TinyBraveHeroes
//
//  Created by Shrenil Patel on 2017-09-06.
//
//

#ifndef GridTile_hpp
#define GridTile_hpp

#include "cocos2d.h"

#define ROWS 8
#define COLUMNS 6

using namespace std;

struct Vec {
    int x, y;
    Vec(int x, int y) : x(x), y(y) {};
    operator cocos2d::Vec2() const {
        return cocos2d::Vec2(x, y);
    }
};

bool operator==(const Vec& lhs, const Vec& rhs) {
    return lhs.x == rhs.x and lhs.y == rhs.y;
}

class GridTile;

class GridGraph {
public:
    GridGraph();
    GridTile ***graph;
    void addTile(Vec location, int weight);
    void addEdge(const Vec from, const Vec to, int work);
    GridTile* getTileAt(Vec at);
    static cocos2d::Vec2 getCoordinate(Vec location);
};

//int GridGraph::gridTileSize = 0;

struct GridEdge {
    GridTile *to;
    int work;
    bool infinite;
    
    //add edge sythesis
    GridEdge(GridTile *to, int work): to(to), work(work){}
};

class GridTile {
public:
    Vec location;
    int work;
    bool infinite;
    bool occupied = false;
    
    GridTile(Vec location, int work) : location(location), work(work), infinite(false){}
    GridTile(Vec location) : location(location), work(0), infinite(true){}
    cocos2d::Vec2 getCoordinate();
    
    // N, NE, E, SE, S, SW, W, NW
    /*
     *
     *            0
     *         '     '
     *      7     |     1
     *     .  \       /  .
     *
     *    6  --   o   --  2
     *
     *     '  /   |   \  '
     *      5           3
     *         .  4  .        
     *
     */
    vector<GridEdge> edges;
    
};

#endif /* GridTile_hpp */
