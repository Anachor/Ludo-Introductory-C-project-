#ifndef LUDO_GLOBAL_H
#define LUDO_GLOBAL_H
#define MAX_PIECES 10

struct Piece
{
    int color;
    int position;
};

int No_of_pieces=4;
int type[4]={0,0,0,0};
struct Piece pieces[4][MAX_PIECES];
int player_type[4];                     //1 for human player, 0 for not playing, 2 for AL
int current_game_state=0;
int current_dice_val=1;
int current_player=0;
int rolls_left=50;
int game_on=0;
int number_of_players=2;
int winner=-1;
int count=0;

char options[5][20]={"CONTINUE", "NEW GAME", "HELP", "EXIT"};
int moves[100];
int moves_size=0;

#endif
