//
//  Dijkstra.cpp
//  TinyBraveHeroes
//
//  Created by Shrenil Patel on 2017-09-07.
//
//

#include "Dijkstra.hpp"

std::vector<GridTile *> pathToTile(DistData mdist, GridTile *dest) {
    std::vector<GridTile *> path;
    auto end = dest;
    path.push_back(end);
    while (mdist[end].second != NULL) {
        end = mdist[end].second;
        path.push_back(end);
    }
    return path;
}

std::vector<GridTile *> suitableTiles(DistData mdist, GridTile *source, int maxTravel) {
    std::vector<GridTile *> path;
}

DistData dijkstra(GridGraph *graph, GridTile *source, GridTile *target) {
    DistData min_distance;
    for (auto i = 0; i < COLUMNS; ++i) {
        for (auto j = 0; j < ROWS; ++j) {
            min_distance[graph->getTileAt(Vec(i, j))] = {INT_MAX, NULL};
        }
    }
    
    min_distance[ source ] = {0, NULL};
    set< pair<int, GridTile *> > active_vertices;
    active_vertices.insert( {0,source} );
    
    while (!active_vertices.empty()) {
        GridTile * where = active_vertices.begin()->second;
        if (where == target)
            return min_distance;
        active_vertices.erase( active_vertices.begin() );
        for (auto ed : where->edges)
            if (min_distance[ed.to].first > min_distance[where].first + ed.work) {
                active_vertices.erase( { min_distance[ed.to].first, ed.to } );
                min_distance[ed.to] = {min_distance[where].first + ed.work, where};
                active_vertices.insert( { min_distance[ed.to].first, ed.to } );
            }
    }
    
    return min_distance;
}
