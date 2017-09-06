//
//  GridTile.hpp
//  TinyBraveHeroes
//
//  Created by Shrenil Patel on 2017-09-06.
//
//

#ifndef GridTile_hpp
#define GridTile_hpp

#include <stdio.h>
#include <vector>
#include <map>
#include <string>
#include "Pawn.hpp"

#define ROWS 8
#define COLUMNS 6

using namespace std;

struct Point {
    int x, y;
    Point(int x, int y) : x(x), y(y) {};
};

class GridTile;

struct GridEdge {
    GridTile *to;
    int work;
    bool infinite;
    
    //add edge sythesis
    GridEdge(GridTile *to, int work): to(to), work(work){}
};

class GridTile {
public:
    Point id;
    Pawn *pawn;
    int work;
    bool infinite;
    
    GridTile(Point id, int work):id(id), work(work), infinite(false){}
    GridTile(Point id):id(id), work(0), infinite(true){}
    
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

class GridGraph {
public:
    GridGraph();
    GridTile ***graph;
    void addTile(Point id, int weight);
    void addEdge(const Point from, const Point to, int work);
};



#endif /* GridTile_hpp */
