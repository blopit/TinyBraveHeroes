//
//  Dijkstra.cpp
//  TinyBraveHeroes
//
//  Created by Shrenil Patel on 2017-09-07.
//
//

#include "Dijkstra.hpp"
#include <iostream>

const weight_t max_weight = std::numeric_limits<double>::infinity();


std::vector<GridTile *> dijkstra(GridGraph *graph, GridTile *source, GridTile *target) {
    map<GridTile *, pair<int, GridTile *>> min_distance;
    for (auto i = 0; i < COLUMNS; ++i) {
        for (auto j = 0; j < ROWS; ++j) {
            min_distance[graph->getTileAt(Vec(i, j))] = {INT_MAX, NULL};
        }
    }
    
    min_distance[ source ] = {0, NULL};
    set< pair<int, GridTile *> > active_vertices;
    active_vertices.insert( {0,source} );
    std::vector<GridTile *> path;
    
    while (!active_vertices.empty()) {
        GridTile * where = active_vertices.begin()->second;
        if (where == target) {
            
            auto it = min_distance.begin();
            /*while (it != min_distance.end())
            {
                GridTile *tile = it->first;
                GridTile *prev = it->second.second;
                int work = it->second.first;
                
                std::cout << "(" << tile->location.x
                <<  "," << tile->location.y << ") " << work
                << " : ";
                
                if (prev != NULL) {
                    std::cout << "(" << prev->location.x
                    <<  "," << prev->location.y << ") ";
                }
                
                std::cout << std::endl;
                it++;
            }*/
            auto end = target;
            path.push_back(end);
            while (min_distance[end].second != NULL) {
                end = min_distance[end].second;
                path.push_back(end);
            }
            
            return path;
        }
        active_vertices.erase( active_vertices.begin() );
        for (auto ed : where->edges)
            if (min_distance[ed.to].first > min_distance[where].first + ed.work) {
                active_vertices.erase( { min_distance[ed.to].first, ed.to } );
                min_distance[ed.to] = {min_distance[where].first + ed.work, where};
                active_vertices.insert( { min_distance[ed.to].first, ed.to } );
            }
    }
    
    return path;
}
