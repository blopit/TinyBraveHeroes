//
//  Dijkstra.hpp
//  TinyBraveHeroes
//
//  Created by Shrenil Patel on 2017-09-07.
//
//

#ifndef Dijkstra_hpp
#define Dijkstra_hpp

#include "GridGraph.hpp"
using DistData = map<GridTile *, pair<int, GridTile *>>;

std::vector<GridTile *> pathToTile(DistData mdist, GridTile * dest);

DistData dijkstra(GridGraph *graph, GridTile *source, GridTile *target);

#endif /* Dijkstra_hpp */
