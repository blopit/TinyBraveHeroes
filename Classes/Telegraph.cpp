//
//  Telegraph.cpp
//  TinyBraveHeroes
//
//  Created by Shrenil Patel on 2017-09-08.
//
//

#include "Telegraph.hpp"

telegraph _trot(telegraph from) {
    telegraph to = none();
    for (auto i = 0; i < TELE_SIZE; i++) {
        for (auto j = 0; j < TELE_SIZE; j++) {
            to[i][j] = from[TELE_SIZE-1-j][i];
        }
    }
    return to;
}

telegraph tele_direction(telegraph from, Direction direction) {
    telegraph to = none();
    telegraph a, b;
    switch (direction) {
        case N:
            to = from;
            break;
        case NE:
            a = tele_rotate(from, Direction::E);
            b = from;
            to = tele_union(a, b);
            break;
        case E:
            to = tele_rotate(from, Direction::E);
            break;
        case SE:
            a = tele_rotate(from, Direction::E);
            b = tele_rotate(from, Direction::S);
            to = tele_union(a, b);
            break;
        case S:
            to = tele_rotate(from, Direction::S);
            break;
        case SW:
            a = tele_rotate(from, Direction::W);
            b = tele_rotate(from, Direction::S);
            to = tele_union(a, b);
            break;
        case W:
            to = tele_rotate(from, Direction::W);
            break;
        case NW:
            a = tele_rotate(from, Direction::W);
            b = from;
            to = tele_union(a, b);
            break;
        default:
            break;
    }
    return to;
}

telegraph tele_rotate(telegraph from, Direction direction) {
    auto repeat = 0;
    telegraph to = none();
    to = from;
    
    switch (direction) {
        case N:
            repeat = 0;
            break;
        case NE:
            repeat = 0;
            break;
        case E:
            repeat = 3;
            break;
        case SE:
            repeat = 2;
            break;
        case S:
            repeat = 2;
            break;
        case SW:
            repeat = 2;
            break;
        case W:
            repeat = 1;
            break;
        case NW:
            repeat = 0;
            break;
        default:
            break;
    }
    
    for (auto i = 0; i < repeat; i++) {
        to = _trot(to);
    }
    return to;
}

telegraph tele_union(telegraph lhs, telegraph rhs) {
    telegraph to = none();
    for (auto i = 0; i < TELE_SIZE; i++) {
        for (auto j = 0; j < TELE_SIZE; j++) {
            if (lhs[i][j] != 0) {
                to[i][j] = lhs[i][j];
            } else if (rhs[i][j] != 0) {
                to[i][j] = rhs[i][j];
            }
        }
    }
    return to;
}

telegraph tele_subtract(telegraph lhs, telegraph rhs) {
    telegraph to = lhs;
    for (auto i = 0; i < TELE_SIZE; i++) {
        for (auto j = 0; j < TELE_SIZE; j++) {
            if (lhs[i][j] != 0 and rhs[i][j] != 0) {
                to[i][j] = 0;
            }
        }
    }
    return to;
}

telegraph none() {
    return {
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    };
}

telegraph circfill_0() {
    return {
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    };
}

telegraph circfill_20() {
    return {
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
        {0,0,0,0,0,1,1,1,1,1,0,0,0,0,0},
        {0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    };
}

telegraph line_50() {
    return {
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,1,1,1,1,1,1,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    };
}

