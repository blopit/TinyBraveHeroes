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

typedef int weight_t;

std::vector<GridTile *> dijkstra(GridGraph *graph, GridTile *source, GridTile *target);

#endif /* Dijkstra_hpp */
