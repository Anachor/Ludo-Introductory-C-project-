#ifndef LUDO_GAME_STATES_H
#define LUDO_GAME_STATES_H

enum GAME_STATES
{
    BEGIN=0,
    CONTINUE=-1,
    NEW_GAME=-2,
    HELP=-3,
    EXIT=-4,

    TURN_START=1,
    DICE_ROLLING=2,
    PIECE_MOVE=3,
    END_TURN=4,
    FINISHED=10
};


#endif // LUDO_GAME_STATES_H
