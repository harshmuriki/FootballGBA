#ifndef MAIN_H
#define MAIN_H

#include "gba.h"

// TODO: Create any necessary structs

// * For example, for a Snake game, one could be:

struct ball
{
    // int height;
    // int width;
    int row;
    int col;
};

//   Example of a struct to hold state machine data:

struct state
{
    // int currentState;
    // int nextState;
    struct ball ball_foot;
};

#endif
