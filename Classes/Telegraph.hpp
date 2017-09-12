//
//  Telegraph.hpp
//  TinyBraveHeroes
//
//  Created by Shrenil Patel on 2017-09-08.
//
//

#ifndef Telegraph_hpp
#define Telegraph_hpp

#include "GridGraph.hpp"

#define TELE_SIZE 15
#define TELE_CENT 7

typedef std::vector< std::vector< char > > telegraph;

enum Direction {
    N, NE, E, SE, S, SW, W, NW, NONE
};

telegraph none();
telegraph circfill_0();
telegraph circfill_20();
telegraph line_50();

telegraph tele_rotate(telegraph from, Direction direction);
telegraph tele_direction(telegraph from, Direction direction);
telegraph tele_union(telegraph lhs, telegraph rhs);
telegraph tele_subtract(telegraph lhs, telegraph rhs);

#endif /* Telegraph_hpp */
