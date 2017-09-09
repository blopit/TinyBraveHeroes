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
std::vector<GridTile *> reachableTiles(DistData mdist, int maxTravel);
DistData dijkstra(GridGraph *graph, GridTile *source, GridTile *target);
DistData dijkstra(GridGraph *graph, GridTile *source);

#endif /* Dijkstra_hpp */
