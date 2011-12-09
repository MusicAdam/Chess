#ifndef STATE_H
#define STATE_H

#include <string>

struct State{
    enum type{
        Uninitialized,
        Loading,
        Ready,
        Turn,
        Exit,

        Sleep,
        Wake,
        Idle,
        Dead
    };

    type            current;


};

#endif
