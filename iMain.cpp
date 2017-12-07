//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "iGraphics.h"
#include "Global.h"
#include "Engine.h"
#include "Animation.h"
#include "GameStates.h"
#include "HexColors.h"
#include "Dimensions.h"

int frame_no=0;

void iDraw()
{
	++frame_no;
	iClear();
    //printf("%d\t%d\n",frame_no,current_game_state);
    iShowBMP(0,0,"back.bmp");
	switch (current_game_state)
	{
	    case BEGIN:     Start_screen(); return;
	    case HELP :     Help_screen(); return;
	    case EXIT:      exit(0); return;
	    case FINISHED:  Finish_screen(); return;
	    case CONTINUE:
            if (game_on)    current_game_state=1;
            else            current_game_state=0;
            return;
        case NEW_GAME:
            Newgame_Screen();
            return;
	    default:
            Draw_board();
    }

    if (current_game_state==TURN_START)
    {
        if (!type[current_player])
            current_player=(current_player+1)%4;
    }

    if (current_game_state==DICE_ROLLING)
    {
        if (rolls_left==0)
        {
            rolls_left=50;
            current_game_state=PIECE_MOVE;
        }
        else
        {
            rolls_left--;
            current_dice_val=1+rand()%6;
        }
    }

    else if (current_game_state==PIECE_MOVE)
    {
        moves_size=0;
        for (int i=0; i<No_of_pieces; i++)
        {
            Piece cur=pieces[current_player][i];
            Piece nw=move_piece(cur, current_dice_val);
            if (nw.color==cur.color && nw.position==cur.position)    continue;
                moves[moves_size++]=i;
        }

        if (moves_size==0)
        {
            current_game_state=4;
        }
    }
    else if (current_game_state==END_TURN)
    {
        int won=1;
        for (int i=0; i<No_of_pieces; i++)
            if (pieces[current_player][i].position/100!=5)
                won=0;

        if (won)
        {
            winner=current_player;
            current_game_state=10;
        }
    }
}
/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouse(int button, int state, int mx, int my) {
    if (current_game_state>0 && current_game_state<=4)
    {
       if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            if (62>=mx && my<=22)
            {
                current_game_state=0;
                return;
            }
        }
    }
    if (current_game_state==BEGIN)
    {
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            if (OPTIONS_POSX<=mx && mx <=OPTIONS_POSX+OPTIONS_LEN)
            {
                int k=OPTIONS_DIF+OPTIONS_POSY-my;
                if (k/OPTIONS_DIF<4 && my%OPTIONS_DIF<=OPTIONS_WID)
                    current_game_state=-1-k/OPTIONS_DIF;
                if (current_game_state==CONTINUE && !game_on)
                    current_game_state=BEGIN;
            }
        }
    }

    else if (current_game_state==HELP)
    {
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            if (CANCEL_POSX<=mx && mx <=CANCEL_POSX+CANCEL_LEN && CANCEL_POSY<=my && my <=CANCEL_POSY+CANCEL_LEN)
                current_game_state=BEGIN;
        }
    }

    else if (current_game_state==NEW_GAME)
    {
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            if (mx>142 && mx <158)
            {
                if (my>462 && my<478)   number_of_players=2;
                else if (my>432 && my<448)   number_of_players=3;
                else if (my>402 && my<418)   number_of_players=4;
            }

            if (CANCEL_POSX<=mx && mx <=CANCEL_POSX+CANCEL_LEN && CANCEL_POSY<=my && my <=CANCEL_POSY+CANCEL_LEN)
                current_game_state=BEGIN;

            if (100<=mx && mx <=100+CANCEL_LEN && CANCEL_POSY<=my && my <=CANCEL_POSY+CANCEL_LEN)
            {
                current_game_state=TURN_START;
                current_player=0;
                rolls_left=50;
                game_on=1;
                type[0]=1;
                type[2]=1;
                type[3]=0;
                type[1]=0;
                if (number_of_players>2)    type[1]=1;
                if (number_of_players>3)    type[3]=1;
                initialize(type);
            }
        }
    }
	else if (current_game_state==TURN_START)
    {
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            if (ROLLBUTTON_POSX<=mx && mx <=ROLLBUTTON_POSX+ROLLBUTTON_LEN && ROLLBUTTON_POSY<=my && my <=ROLLBUTTON_POSY+ROLLBUTTON_LEN)
                current_game_state=DICE_ROLLING;
        }
    }

    else if (current_game_state==PIECE_MOVE)
    {
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            int px=(mx-LEFTX)/CELLSIZE+1;
            int py=(my-LEFTY)/CELLSIZE+1;
            int crd=100*px+py;

            int rgb[3], color;
            iGetPixelColor(mx, my, rgb);

            switch (hex(rgb))
            {
                case PIECE_COLOR_0: color=0; break;
                case PIECE_COLOR_1: color=1; break;
                case PIECE_COLOR_2: color=2; break;
                case PIECE_COLOR_3: color=3; break;
                default:
                    color=-1;
            }
            printf("%d ", crd);
            for (int i=0; i<moves_size; i++)
            {
                printf("%d ", toCartesian(pieces[current_player][moves[i]].position, moves[i]));
                if (toCartesian(pieces[current_player][moves[i]].position, moves[i])==crd)
                {
                    pieces[current_player][moves[i]]=move_piece(pieces[current_player][moves[i]], current_dice_val);
                    int extra=(capture(current_player, moves[i])) || (current_dice_val==6);
                    if (extra)
                        current_game_state=1;
                    else
                        current_game_state=4;
                    break;
                }
                printf("\n");
            }
        }
    }
    else if (current_game_state==END_TURN)
    {
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            if (ROLLBUTTON_POSX<=mx && mx <=ROLLBUTTON_POSX+ROLLBUTTON_LEN && ROLLBUTTON_POSY<=my && my <=ROLLBUTTON_POSY+ROLLBUTTON_LEN)
            {
                current_game_state=TURN_START,
                current_player=(1+current_player)%4;
                moves_size=0;
            }
        }
    }
    else if (current_game_state==FINISHED)
    {
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            if (CANCEL_POSX<=mx && mx <=CANCEL_POSX+CANCEL_LEN && CANCEL_POSY<=my && my <=CANCEL_POSY+CANCEL_LEN)
            {
                current_game_state=0;
                current_player=0;
                game_on=0;
                rolls_left=50;
            }
        }
    }
}

void iMouseMove(int button, int state)
{

}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
	*/
void iKeyboard(unsigned char key) {
	if (key == 'q') ;

    return;
    ///The following are for debugging. comment out the return to access these.
    if (key>'0' && key<='6')
	{

        current_dice_val=key-'0';
        current_game_state=3;
	}

	if (key=='`')
        current_game_state=10;

        //printf("%c\n",key);
	//place your codes for other keys here
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
	*/
void iSpecialKeyboard(unsigned char key) {

	if (key == GLUT_KEY_END) {
		exit(0);
	}

    if (current_game_state>0 && key == GLUT_KEY_HOME)
    {
        if (current_game_state==4)
            current_player=(current_player+1)%4;
        current_game_state=0;
    }
}

int main()
{
    srand(time(0));
        printf("%f %f", LEFTX+15*CELLSIZE+OPTIONS_WIDTH+2*BORDER,LEFTY+15*CELLSIZE+2*BORDER);

    iInitialize(LEFTX+15*CELLSIZE+OPTIONS_WIDTH+2*BORDER,LEFTY+15*CELLSIZE+2*BORDER,"Ludo");
}
