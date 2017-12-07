#ifndef LUDO_ANIMATION_H
#define LUDO_ANIMATION_H

#include <stdio.h>
#include <stdlib.h>

#include "iGraphics.h"
#include "Dimensions.h"
#include "HexColors.h"

int toCartesian(int pos);

void Draw_board();
void Draw_design();
void Show_info();
void Draw_pieces(struct Piece pieces[4][MAX_PIECES]);
void Draw_dice(int dice_val);
void Start_screen();

void Help_screen();
void About_screen();
void Settings_screen();

void Help_screen()
{
    int i;
    iShowBMP(0,0,"Help.bmp");

    iSetColor(BLACK);
    iFilledRectangle(CANCEL_POSX-BORDER, CANCEL_POSY-BORDER, CANCEL_LEN+2*BORDER, CANCEL_WID+2*BORDER);

    iSetColor(RED);
    iFilledRectangle(CANCEL_POSX, CANCEL_POSY, CANCEL_LEN, CANCEL_WID);

    iSetColor(BLACK);
    iText(CANCEL_POSX, CANCEL_POSY+CANCEL_WID/3, "BACK", GLUT_BITMAP_TIMES_ROMAN_24);
}

void About_screen()
{
    int i;
    iText(300,300,"Help Screen will show here");

    iSetColor(BLACK);
    iFilledRectangle(CANCEL_POSX-BORDER, CANCEL_POSY-BORDER, CANCEL_LEN+2*BORDER, CANCEL_WID+2*BORDER);

    iSetColor(RED);
    iFilledRectangle(CANCEL_POSX, CANCEL_POSY, CANCEL_LEN, CANCEL_WID);

    iSetColor(BLACK);
    iText(CANCEL_POSX, CANCEL_POSY+CANCEL_WID/3, "BACK", GLUT_BITMAP_TIMES_ROMAN_24);

}

void Settings_screen()
{
    int i;
    iText(300,300,"Help Screen will show here");

    iSetColor(BLACK);
    iFilledRectangle(CANCEL_POSX-BORDER, CANCEL_POSY-BORDER, CANCEL_LEN+2*BORDER, CANCEL_WID+2*BORDER);

    iSetColor(RED);
    iFilledRectangle(CANCEL_POSX, CANCEL_POSY, CANCEL_LEN, CANCEL_WID);

    iSetColor(BLACK);
    iText(CANCEL_POSX, CANCEL_POSY+CANCEL_WID/3, "BACK", GLUT_BITMAP_TIMES_ROMAN_24);
}

void Finish_screen()
{
    int i;
    char buf[100];
    sprintf(buf, "Congratulations! Player %d Won!!!", winner);
    iText(100,300,buf, GLUT_BITMAP_TIMES_ROMAN_24);

    iSetColor(BLACK);
    iFilledRectangle(CANCEL_POSX-BORDER, CANCEL_POSY-BORDER, CANCEL_LEN+2*BORDER, CANCEL_WID+2*BORDER);

    iSetColor(RED);
    iFilledRectangle(CANCEL_POSX, CANCEL_POSY, CANCEL_LEN, CANCEL_WID);

    iSetColor(BLACK);
    iText(CANCEL_POSX, CANCEL_POSY+CANCEL_WID/3, "MENU", GLUT_BITMAP_TIMES_ROMAN_24);
}

void Newgame_Screen()
{
    iSetColor(BLACK);
    iText(100, 500, "Number of Players:", GLUT_BITMAP_TIMES_ROMAN_24);
    for (int i=1; i<4; i++)
    {
        iCircle(150, 500-30*i, 8);
        char buf[10];
        sprintf(buf, "%d", i+1);
        iText(170, 500-30*i-5, buf, GLUT_BITMAP_HELVETICA_18);
    }
    iSetColor(RED);
    iFilledCircle(150, 500-30*number_of_players+30, 10);

    iSetColor(BLACK);
    iFilledRectangle(100-BORDER, CANCEL_POSY-BORDER, CANCEL_LEN+2*BORDER, CANCEL_WID+2*BORDER);

    iSetColor(RED);
    iFilledRectangle(100, CANCEL_POSY, CANCEL_LEN, CANCEL_WID);

    iSetColor(BLACK);
    iText(100, CANCEL_POSY+CANCEL_WID/3, "PLAY", GLUT_BITMAP_TIMES_ROMAN_24);

    iSetColor(BLACK);
    iFilledRectangle(CANCEL_POSX-BORDER, CANCEL_POSY-BORDER, CANCEL_LEN+2*BORDER, CANCEL_WID+2*BORDER);

    iSetColor(RED);
    iFilledRectangle(CANCEL_POSX, CANCEL_POSY, CANCEL_LEN, CANCEL_WID);

    iSetColor(BLACK);
    iText(CANCEL_POSX, CANCEL_POSY+CANCEL_WID/3, "BACK", GLUT_BITMAP_TIMES_ROMAN_24);
}


void Start_screen()
{
#ifdef __GNUC__
    iShowBMP2(0, 500, "Ludo.bmp", WHITE);
#else
    iSetColor(BLACK);    iShowBMP(0, 0, "Ludo2.bmp");

#endif

    int i;
    iSetColor(BLACK);
    for (i=0; i<4; i++)
        if (i || game_on)
        iFilledRectangle(OPTIONS_POSX-BORDER, OPTIONS_POSY-OPTIONS_DIF*i-BORDER, OPTIONS_LEN+2*BORDER, OPTIONS_WID+2*BORDER);

    iSetColor(RED);
    for (i=0; i<4; i++)
        if (i || game_on)
        iFilledRectangle(OPTIONS_POSX, OPTIONS_POSY-OPTIONS_DIF*i, OPTIONS_LEN, OPTIONS_WID);

    iSetColor(BLACK);
    for (i=0; i<4; i++)
        if (i || game_on)
        iText(OPTIONS_POSX, OPTIONS_POSY-OPTIONS_DIF*i+OPTIONS_WID/3, options[i], GLUT_BITMAP_TIMES_ROMAN_24);
}

int toCartesian(int pos, int id)
{
    switch (pos)
    {
        case -1:    return 1014-id;
        case -2:    return 1406-id*100;
        case -3:    return  602+id;
        case -4:    return  210+id*100;
        case 500:   return  809;
        case 501:   return  908;
        case 502:   return  807;
        case 503:   return  708;
        case 6:     return  815;
        case 19:    return 1508;
        case 32:    return  801;
        case 45:    return  108;
    }

    if (pos>=100)
    {
        switch (pos/100)
        {
            case 1:     return 800+(15-pos%100);
            case 2:     return (15-pos%100)*100+8;
            case 3:     return 800+(1+pos%100);
            case 4:     return (1+pos%100)*100+8;
        }
    }

    if (pos>=0  && pos<=5)      return  700+(10+pos);
    if (pos>=7  && pos<=12)     return  900+(22-pos);
    if (pos>=13 && pos<=18)     return  (pos-3)*100+9;
    if (pos>=20 && pos<=25)     return  (35-pos)*100+7;
    if (pos>=26 && pos<=31)     return  900+(32-pos);
    if (pos>=33 && pos<=38)     return  700+(pos-32);
    if (pos>=39 && pos<=44)     return  (45-pos)*100+7;
    if (pos>=46 && pos<=51)     return  (pos-45)*100+9;
	return 0;
}

void Draw_pieces(struct Piece pieces[4][MAX_PIECES])
{
    int i,j,k;
    for (k=0, i=(current_player+1)%4; k<4; k++, i=(i+1)%4)
        if (player_type[i])
            for (j=0; j<No_of_pieces; j++)
            {
                int pos=toCartesian(pieces[i][j].position, j);
                int posx=pos/100;
                int posy=pos%100;
                int piece_color;

                switch(i)
                {
                    case 0: piece_color=PIECE_COLOR_0; break;
                    case 1: piece_color=PIECE_COLOR_1; break;
                    case 2: piece_color=PIECE_COLOR_2; break;
                    case 3: piece_color=PIECE_COLOR_3; break;
                }
                iSetColor(BORDER_COLOR);
                iFilledCircle(LEFTX+(posx-0.5)*CELLSIZE, LEFTY+(posy-0.5)*CELLSIZE, PIECE_RADIUS);
                iSetColor(piece_color);
                iFilledCircle(LEFTX+(posx-0.5)*CELLSIZE, LEFTY+(posy-0.5)*CELLSIZE, PIECE_RADIUS-BORDER);
            }
}

void Draw_board()
{
    int i, j, ii, jj;
	iSetColor(BORDER_COLOR);
    iFilledRectangle(LEFTX-BORDER,LEFTY-BORDER,15*CELLSIZE+2*BORDER,15*CELLSIZE+2*BORDER);
    iSetColor(COLOR_0);
    iFilledRectangle(LEFTX+9*CELLSIZE,LEFTY+9*CELLSIZE,6*CELLSIZE,6*CELLSIZE);
    iSetColor(COLOR_1);
    iFilledRectangle(LEFTX+9*CELLSIZE,LEFTY,6*CELLSIZE,6*CELLSIZE);
    iSetColor(COLOR_2);
    iFilledRectangle(LEFTX,LEFTY,6*CELLSIZE,6*CELLSIZE);
    iSetColor(COLOR_3);
    iFilledRectangle(LEFTX,LEFTY+9*CELLSIZE,6*CELLSIZE,6*CELLSIZE);
    iSetColor(CELL_COLOR);
    iFilledRectangle(LEFTX+6*CELLSIZE,LEFTY+6*CELLSIZE,3*CELLSIZE,3*CELLSIZE);

    iSetColor(CELL_COLOR);
    for (i=LEFTX+6*CELLSIZE+BORDER/2, ii=0; ii<3; ii++, i+=CELLSIZE)
        for (j=LEFTY+9*CELLSIZE+BORDER/2, jj=0; jj<6; j+=CELLSIZE, jj++)
            iFilledRectangle(i,j,CELLSIZE-BORDER,CELLSIZE-BORDER);

    for (i=LEFTX+6*CELLSIZE+BORDER/2, ii=0; ii<3; ii++, i+=CELLSIZE)
        for (j=LEFTY+BORDER/2, jj=0; jj<6; j+=CELLSIZE, jj++)
            iFilledRectangle(i,j,CELLSIZE-BORDER,CELLSIZE-BORDER);

    for (i=LEFTX+BORDER/2, ii=0; ii<6; ii++, i+=CELLSIZE)
        for (j=LEFTY+6*CELLSIZE+BORDER/2, jj=0; jj<3; j+=CELLSIZE, jj++)
            iFilledRectangle(i,j,CELLSIZE-BORDER,CELLSIZE-BORDER);

    for (i=LEFTX+9*CELLSIZE+BORDER/2, ii=0; ii<6; ii++, i+=CELLSIZE)
        for (j=LEFTY+6*CELLSIZE+BORDER/2, jj=0; jj<3; j+=CELLSIZE, jj++)
            iFilledRectangle(i,j,CELLSIZE-BORDER,CELLSIZE-BORDER);

    iSetColor(COLOR_0);
    iFilledRectangle(LEFTX+8*CELLSIZE+BORDER/2,LEFTY+13*CELLSIZE+BORDER/2,CELLSIZE-BORDER,CELLSIZE-BORDER);
    for (i=0; i<5; i++)
        iFilledRectangle(LEFTX+7*CELLSIZE+BORDER/2,LEFTY+(13-i)*CELLSIZE+BORDER/2,CELLSIZE-BORDER,CELLSIZE-BORDER);

    iSetColor(COLOR_1);
    iFilledRectangle(LEFTX+13*CELLSIZE+BORDER/2,LEFTY+6*CELLSIZE+BORDER/2,CELLSIZE-BORDER,CELLSIZE-BORDER);
    for (i=0; i<5; i++)
        iFilledRectangle(LEFTX+(13-i)*CELLSIZE+BORDER/2,LEFTY+7*CELLSIZE+BORDER/2,CELLSIZE-BORDER,CELLSIZE-BORDER);

    iSetColor(COLOR_2);
    iFilledRectangle(LEFTX+6*CELLSIZE+BORDER/2,LEFTY+1*CELLSIZE+BORDER/2,CELLSIZE-BORDER,CELLSIZE-BORDER);
    for (i=0; i<5; i++)
        iFilledRectangle(LEFTX+7*CELLSIZE+BORDER/2,LEFTY+(1+i)*CELLSIZE+BORDER/2,CELLSIZE-BORDER,CELLSIZE-BORDER);

    iSetColor(COLOR_3);
    iFilledRectangle(LEFTX+1*CELLSIZE+BORDER/2,LEFTY+8*CELLSIZE+BORDER/2,CELLSIZE-BORDER,CELLSIZE-BORDER);
    for (i=0; i<5; i++)
        iFilledRectangle(LEFTX+(1+i)*CELLSIZE+BORDER/2,LEFTY+7*CELLSIZE+BORDER/2,CELLSIZE-BORDER,CELLSIZE-BORDER);

    Draw_design();
    Show_info();
	Draw_pieces(pieces);
	Draw_dice(current_dice_val);
	//show_debug_info();
}

void Draw_design()
{
    //return ;
    iSetColor(BORDER_COLOR);
    iFilledRectangle(LEFTX+   1*CELLSIZE, LEFTY+ 1*CELLSIZE, RELATIVE_WINDOW_WIDTH*CELLSIZE, (3+RELATIVE_WINDOW_WIDTH)*CELLSIZE);
    iFilledRectangle(LEFTX+ 2.5*CELLSIZE, LEFTY+ 1*CELLSIZE, RELATIVE_WINDOW_WIDTH*CELLSIZE, (3+RELATIVE_WINDOW_WIDTH)*CELLSIZE);
    iFilledRectangle(LEFTX+   4*CELLSIZE, LEFTY+ 1*CELLSIZE, RELATIVE_WINDOW_WIDTH*CELLSIZE, (3+RELATIVE_WINDOW_WIDTH)*CELLSIZE);
    iFilledRectangle(LEFTX+  10*CELLSIZE, LEFTY+ 1*CELLSIZE, RELATIVE_WINDOW_WIDTH*CELLSIZE, (3+RELATIVE_WINDOW_WIDTH)*CELLSIZE);
    iFilledRectangle(LEFTX+11.5*CELLSIZE, LEFTY+ 1*CELLSIZE, RELATIVE_WINDOW_WIDTH*CELLSIZE, (3+RELATIVE_WINDOW_WIDTH)*CELLSIZE);
    iFilledRectangle(LEFTX+  13*CELLSIZE, LEFTY+ 1*CELLSIZE, RELATIVE_WINDOW_WIDTH*CELLSIZE, (3+RELATIVE_WINDOW_WIDTH)*CELLSIZE);
    iFilledRectangle(LEFTX+   1*CELLSIZE, LEFTY+10*CELLSIZE, RELATIVE_WINDOW_WIDTH*CELLSIZE, (3+RELATIVE_WINDOW_WIDTH)*CELLSIZE);
    iFilledRectangle(LEFTX+ 2.5*CELLSIZE, LEFTY+10*CELLSIZE, RELATIVE_WINDOW_WIDTH*CELLSIZE, (3+RELATIVE_WINDOW_WIDTH)*CELLSIZE);
    iFilledRectangle(LEFTX+   4*CELLSIZE, LEFTY+10*CELLSIZE, RELATIVE_WINDOW_WIDTH*CELLSIZE, (3+RELATIVE_WINDOW_WIDTH)*CELLSIZE);
    iFilledRectangle(LEFTX+  10*CELLSIZE, LEFTY+10*CELLSIZE, RELATIVE_WINDOW_WIDTH*CELLSIZE, (3+RELATIVE_WINDOW_WIDTH)*CELLSIZE);
    iFilledRectangle(LEFTX+11.5*CELLSIZE, LEFTY+10*CELLSIZE, RELATIVE_WINDOW_WIDTH*CELLSIZE, (3+RELATIVE_WINDOW_WIDTH)*CELLSIZE);
    iFilledRectangle(LEFTX+  13*CELLSIZE, LEFTY+10*CELLSIZE, RELATIVE_WINDOW_WIDTH*CELLSIZE, (3+RELATIVE_WINDOW_WIDTH)*CELLSIZE);

    iFilledRectangle( LEFTX+ 1*CELLSIZE,LEFTY+   1*CELLSIZE, (3+RELATIVE_WINDOW_WIDTH)*CELLSIZE, RELATIVE_WINDOW_WIDTH*CELLSIZE);
    iFilledRectangle( LEFTX+ 1*CELLSIZE,LEFTY+ 2.5*CELLSIZE, (3+RELATIVE_WINDOW_WIDTH)*CELLSIZE, RELATIVE_WINDOW_WIDTH*CELLSIZE);
    iFilledRectangle( LEFTX+ 1*CELLSIZE,LEFTY+   4*CELLSIZE, (3+RELATIVE_WINDOW_WIDTH)*CELLSIZE, RELATIVE_WINDOW_WIDTH*CELLSIZE);
    iFilledRectangle( LEFTX+ 1*CELLSIZE,LEFTY+  10*CELLSIZE, (3+RELATIVE_WINDOW_WIDTH)*CELLSIZE, RELATIVE_WINDOW_WIDTH*CELLSIZE);
    iFilledRectangle( LEFTX+ 1*CELLSIZE,LEFTY+11.5*CELLSIZE, (3+RELATIVE_WINDOW_WIDTH)*CELLSIZE, RELATIVE_WINDOW_WIDTH*CELLSIZE);
    iFilledRectangle( LEFTX+ 1*CELLSIZE,LEFTY+  13*CELLSIZE, (3+RELATIVE_WINDOW_WIDTH)*CELLSIZE, RELATIVE_WINDOW_WIDTH*CELLSIZE);
    iFilledRectangle( LEFTX+10*CELLSIZE,LEFTY+   1*CELLSIZE, (3+RELATIVE_WINDOW_WIDTH)*CELLSIZE, RELATIVE_WINDOW_WIDTH*CELLSIZE);
    iFilledRectangle( LEFTX+10*CELLSIZE,LEFTY+ 2.5*CELLSIZE, (3+RELATIVE_WINDOW_WIDTH)*CELLSIZE, RELATIVE_WINDOW_WIDTH*CELLSIZE);
    iFilledRectangle( LEFTX+10*CELLSIZE,LEFTY+   4*CELLSIZE, (3+RELATIVE_WINDOW_WIDTH)*CELLSIZE, RELATIVE_WINDOW_WIDTH*CELLSIZE);
    iFilledRectangle( LEFTX+10*CELLSIZE,LEFTY+  10*CELLSIZE, (3+RELATIVE_WINDOW_WIDTH)*CELLSIZE, RELATIVE_WINDOW_WIDTH*CELLSIZE);
    iFilledRectangle( LEFTX+10*CELLSIZE,LEFTY+11.5*CELLSIZE, (3+RELATIVE_WINDOW_WIDTH)*CELLSIZE, RELATIVE_WINDOW_WIDTH*CELLSIZE);
    iFilledRectangle( LEFTX+10*CELLSIZE,LEFTY+  13*CELLSIZE, (3+RELATIVE_WINDOW_WIDTH)*CELLSIZE, RELATIVE_WINDOW_WIDTH*CELLSIZE);

    iSetColor(CELL_COLOR);
    iFilledRectangle(LEFTX+   1*CELLSIZE+BORDER_WINDOW/2, LEFTY+ 1*CELLSIZE+BORDER_WINDOW/2, RELATIVE_WINDOW_WIDTH*CELLSIZE-BORDER_WINDOW, (3+RELATIVE_WINDOW_WIDTH)*CELLSIZE-BORDER_WINDOW);
    iFilledRectangle(LEFTX+ 2.5*CELLSIZE+BORDER_WINDOW/2, LEFTY+ 1*CELLSIZE+BORDER_WINDOW/2, RELATIVE_WINDOW_WIDTH*CELLSIZE-BORDER_WINDOW, (3+RELATIVE_WINDOW_WIDTH)*CELLSIZE-BORDER_WINDOW);
    iFilledRectangle(LEFTX+   4*CELLSIZE+BORDER_WINDOW/2, LEFTY+ 1*CELLSIZE+BORDER_WINDOW/2, RELATIVE_WINDOW_WIDTH*CELLSIZE-BORDER_WINDOW, (3+RELATIVE_WINDOW_WIDTH)*CELLSIZE-BORDER_WINDOW);
    iFilledRectangle(LEFTX+  10*CELLSIZE+BORDER_WINDOW/2, LEFTY+ 1*CELLSIZE+BORDER_WINDOW/2, RELATIVE_WINDOW_WIDTH*CELLSIZE-BORDER_WINDOW, (3+RELATIVE_WINDOW_WIDTH)*CELLSIZE-BORDER_WINDOW);
    iFilledRectangle(LEFTX+11.5*CELLSIZE+BORDER_WINDOW/2, LEFTY+ 1*CELLSIZE+BORDER_WINDOW/2, RELATIVE_WINDOW_WIDTH*CELLSIZE-BORDER_WINDOW, (3+RELATIVE_WINDOW_WIDTH)*CELLSIZE-BORDER_WINDOW);
    iFilledRectangle(LEFTX+  13*CELLSIZE+BORDER_WINDOW/2, LEFTY+ 1*CELLSIZE+BORDER_WINDOW/2, RELATIVE_WINDOW_WIDTH*CELLSIZE-BORDER_WINDOW, (3+RELATIVE_WINDOW_WIDTH)*CELLSIZE-BORDER_WINDOW);
    iFilledRectangle(LEFTX+   1*CELLSIZE+BORDER_WINDOW/2, LEFTY+10*CELLSIZE+BORDER_WINDOW/2, RELATIVE_WINDOW_WIDTH*CELLSIZE-BORDER_WINDOW, (3+RELATIVE_WINDOW_WIDTH)*CELLSIZE-BORDER_WINDOW);
    iFilledRectangle(LEFTX+ 2.5*CELLSIZE+BORDER_WINDOW/2, LEFTY+10*CELLSIZE+BORDER_WINDOW/2, RELATIVE_WINDOW_WIDTH*CELLSIZE-BORDER_WINDOW, (3+RELATIVE_WINDOW_WIDTH)*CELLSIZE-BORDER_WINDOW);
    iFilledRectangle(LEFTX+   4*CELLSIZE+BORDER_WINDOW/2, LEFTY+10*CELLSIZE+BORDER_WINDOW/2, RELATIVE_WINDOW_WIDTH*CELLSIZE-BORDER_WINDOW, (3+RELATIVE_WINDOW_WIDTH)*CELLSIZE-BORDER_WINDOW);
    iFilledRectangle(LEFTX+  10*CELLSIZE+BORDER_WINDOW/2, LEFTY+10*CELLSIZE+BORDER_WINDOW/2, RELATIVE_WINDOW_WIDTH*CELLSIZE-BORDER_WINDOW, (3+RELATIVE_WINDOW_WIDTH)*CELLSIZE-BORDER_WINDOW);
    iFilledRectangle(LEFTX+11.5*CELLSIZE+BORDER_WINDOW/2, LEFTY+10*CELLSIZE+BORDER_WINDOW/2, RELATIVE_WINDOW_WIDTH*CELLSIZE-BORDER_WINDOW, (3+RELATIVE_WINDOW_WIDTH)*CELLSIZE-BORDER_WINDOW);
    iFilledRectangle(LEFTX+  13*CELLSIZE+BORDER_WINDOW/2, LEFTY+10*CELLSIZE+BORDER_WINDOW/2, RELATIVE_WINDOW_WIDTH*CELLSIZE-BORDER_WINDOW, (3+RELATIVE_WINDOW_WIDTH)*CELLSIZE-BORDER_WINDOW);

    iFilledRectangle( LEFTX+ 1*CELLSIZE+BORDER_WINDOW/2,LEFTY+BORDER_WINDOW/2+   1*CELLSIZE, (3+RELATIVE_WINDOW_WIDTH)*CELLSIZE-BORDER_WINDOW, RELATIVE_WINDOW_WIDTH*CELLSIZE-BORDER_WINDOW);
    iFilledRectangle( LEFTX+ 1*CELLSIZE+BORDER_WINDOW/2,LEFTY+BORDER_WINDOW/2+ 2.5*CELLSIZE, (3+RELATIVE_WINDOW_WIDTH)*CELLSIZE-BORDER_WINDOW, RELATIVE_WINDOW_WIDTH*CELLSIZE-BORDER_WINDOW);
    iFilledRectangle( LEFTX+ 1*CELLSIZE+BORDER_WINDOW/2,LEFTY+BORDER_WINDOW/2+   4*CELLSIZE, (3+RELATIVE_WINDOW_WIDTH)*CELLSIZE-BORDER_WINDOW, RELATIVE_WINDOW_WIDTH*CELLSIZE-BORDER_WINDOW);
    iFilledRectangle( LEFTX+ 1*CELLSIZE+BORDER_WINDOW/2,LEFTY+BORDER_WINDOW/2+  10*CELLSIZE, (3+RELATIVE_WINDOW_WIDTH)*CELLSIZE-BORDER_WINDOW, RELATIVE_WINDOW_WIDTH*CELLSIZE-BORDER_WINDOW);
    iFilledRectangle( LEFTX+ 1*CELLSIZE+BORDER_WINDOW/2,LEFTY+BORDER_WINDOW/2+11.5*CELLSIZE, (3+RELATIVE_WINDOW_WIDTH)*CELLSIZE-BORDER_WINDOW, RELATIVE_WINDOW_WIDTH*CELLSIZE-BORDER_WINDOW);
    iFilledRectangle( LEFTX+ 1*CELLSIZE+BORDER_WINDOW/2,LEFTY+BORDER_WINDOW/2+  13*CELLSIZE, (3+RELATIVE_WINDOW_WIDTH)*CELLSIZE-BORDER_WINDOW, RELATIVE_WINDOW_WIDTH*CELLSIZE-BORDER_WINDOW);
    iFilledRectangle( LEFTX+10*CELLSIZE+BORDER_WINDOW/2,LEFTY+BORDER_WINDOW/2+   1*CELLSIZE, (3+RELATIVE_WINDOW_WIDTH)*CELLSIZE-BORDER_WINDOW, RELATIVE_WINDOW_WIDTH*CELLSIZE-BORDER_WINDOW);
    iFilledRectangle( LEFTX+10*CELLSIZE+BORDER_WINDOW/2,LEFTY+BORDER_WINDOW/2+ 2.5*CELLSIZE, (3+RELATIVE_WINDOW_WIDTH)*CELLSIZE-BORDER_WINDOW, RELATIVE_WINDOW_WIDTH*CELLSIZE-BORDER_WINDOW);
    iFilledRectangle( LEFTX+10*CELLSIZE+BORDER_WINDOW/2,LEFTY+BORDER_WINDOW/2+   4*CELLSIZE, (3+RELATIVE_WINDOW_WIDTH)*CELLSIZE-BORDER_WINDOW, RELATIVE_WINDOW_WIDTH*CELLSIZE-BORDER_WINDOW);
    iFilledRectangle( LEFTX+10*CELLSIZE+BORDER_WINDOW/2,LEFTY+BORDER_WINDOW/2+  10*CELLSIZE, (3+RELATIVE_WINDOW_WIDTH)*CELLSIZE-BORDER_WINDOW, RELATIVE_WINDOW_WIDTH*CELLSIZE-BORDER_WINDOW);
    iFilledRectangle( LEFTX+10*CELLSIZE+BORDER_WINDOW/2,LEFTY+BORDER_WINDOW/2+11.5*CELLSIZE, (3+RELATIVE_WINDOW_WIDTH)*CELLSIZE-BORDER_WINDOW, RELATIVE_WINDOW_WIDTH*CELLSIZE-BORDER_WINDOW);
    iFilledRectangle( LEFTX+10*CELLSIZE+BORDER_WINDOW/2,LEFTY+BORDER_WINDOW/2+  13*CELLSIZE, (3+RELATIVE_WINDOW_WIDTH)*CELLSIZE-BORDER_WINDOW, RELATIVE_WINDOW_WIDTH*CELLSIZE-BORDER_WINDOW);

    iSetColor(BORDER_COLOR);
    iFilledRectangle(LEFTX+6*CELLSIZE, LEFTY+6*CELLSIZE, 3*CELLSIZE, 3*CELLSIZE);

    iSetColor(CELL_COLOR);
    iFilledRectangle(LEFTX+6*CELLSIZE+BORDER/2, LEFTY+6*CELLSIZE+BORDER/2, 3*CELLSIZE-BORDER, 3*CELLSIZE-BORDER);

    iSetColor(COLOR_0);
    double x0[3]={LEFTX+6*CELLSIZE+BORDER,LEFTX+9*CELLSIZE-BORDER,LEFTX+7.5*CELLSIZE};
    double y0[3]={LEFTY+9*CELLSIZE-BORDER,LEFTY+9*CELLSIZE-BORDER,LEFTY+7.5*CELLSIZE};
    iFilledPolygon(x0,y0,3);

    iSetColor(COLOR_1);
    double x1[3]={LEFTX+9*CELLSIZE-BORDER,LEFTX+9*CELLSIZE-BORDER,LEFTX+7.5*CELLSIZE};
    double y1[3]={LEFTY+6*CELLSIZE+BORDER,LEFTY+9*CELLSIZE-BORDER,LEFTY+7.5*CELLSIZE};
    iFilledPolygon(x1,y1,3);

    iSetColor(COLOR_2);
    double x2[3]={LEFTX+6*CELLSIZE+BORDER,LEFTX+9*CELLSIZE-BORDER,LEFTX+7.5*CELLSIZE};
    double y2[3]={LEFTY+6*CELLSIZE+BORDER,LEFTY+6*CELLSIZE+BORDER,LEFTY+7.5*CELLSIZE};
    iFilledPolygon(x2,y2,3);

    iSetColor(COLOR_3);
    double x3[3]={LEFTX+6*CELLSIZE+BORDER,LEFTX+6*CELLSIZE+BORDER,LEFTX+7.5*CELLSIZE};
    double y3[3]={LEFTY+6*CELLSIZE+BORDER,LEFTY+9*CELLSIZE-BORDER,LEFTY+7.5*CELLSIZE};
    iFilledPolygon(x3,y3,3);

    iSetColor(BORDER_COLOR);
    iFilledCircle(LEFTX+7.5*CELLSIZE,LEFTY+7.5*CELLSIZE, CELLSIZE);

    iSetColor(CELL_COLOR);
    iFilledCircle(LEFTX+7.5*CELLSIZE,LEFTY+7.5*CELLSIZE, CELLSIZE-BORDER);

    iSetColor(BLACK);
    iText(LEFTX+7.5*CELLSIZE-27,LEFTY+7.5*CELLSIZE-6, "HOME",GLUT_BITMAP_HELVETICA_18);
}

int dec (char * bin)
{
    int res=0;
    int i;
    for (i=0; i<7; i++)
        res=res*2+bin[i]-'0';
    return res;
}

void Draw_dice(int dice_val)
{
    int bitmask=0;
    switch (dice_val)
    {
        case 1:     bitmask=dec("0000001");    break;          // +---------+
        case 2:     bitmask=dec("1000010");    break;          // | 1     4 |
        case 3:     bitmask=dec("1000011");    break;          // |         |
        case 4:     bitmask=dec("1011010");    break;          // | 2  0  5 |
        case 5:     bitmask=dec("1011011");    break;          // |         |
        case 6:     bitmask=dec("1111110");    break;          // | 3     6 |
                                                               // +---------+
    }
    iSetColor(BORDER_COLOR);
    iFilledRectangle(DICE_POSX-BORDER,DICE_POSY-BORDER, DICE_SIZE+2*BORDER, DICE_SIZE+2*BORDER);
    iSetColor(DICE_COLOR);
    iFilledRectangle(DICE_POSX, DICE_POSY, DICE_SIZE, DICE_SIZE);

    iSetColor(DICE_DOT_COLOR);
    int i;
    for (i=0; i<7; i++)
        if (bitmask & 1<<i)
        {
            if (i==0)   iFilledCircle(DICE_POSX+  DICE_SIZE/2, DICE_POSY+  DICE_SIZE/2, DICE_DOT_RADIUS);
            if (i==1)   iFilledCircle(DICE_POSX+  DICE_SIZE/4, DICE_POSY+3*DICE_SIZE/4, DICE_DOT_RADIUS);
            if (i==2)   iFilledCircle(DICE_POSX+  DICE_SIZE/4, DICE_POSY+  DICE_SIZE/2, DICE_DOT_RADIUS);
            if (i==3)   iFilledCircle(DICE_POSX+  DICE_SIZE/4, DICE_POSY+  DICE_SIZE/4, DICE_DOT_RADIUS);
            if (i==4)   iFilledCircle(DICE_POSX+3*DICE_SIZE/4, DICE_POSY+3*DICE_SIZE/4, DICE_DOT_RADIUS);
            if (i==5)   iFilledCircle(DICE_POSX+3*DICE_SIZE/4, DICE_POSY+  DICE_SIZE/2, DICE_DOT_RADIUS);
            if (i==6)   iFilledCircle(DICE_POSX+3*DICE_SIZE/4, DICE_POSY+  DICE_SIZE/4, DICE_DOT_RADIUS);
        }
}

void Show_info()
{
    char plstr[20]="Player 1's Turn";
    plstr[7]=current_player+'1';

    int color;
    switch(current_player)
    {
        case 0: color=COLOR_0; break;
        case 1: color=COLOR_1; break;
        case 2: color=PIECE_COLOR_2; break;
        case 3: color=COLOR_3; break;
    }
    iSetColor(color);
    iText(CELLSIZE,LEFTY/2,plstr, GLUT_BITMAP_TIMES_ROMAN_24);

    if (current_game_state==1 || current_game_state==4)
    {
        iSetColor(BLACK);
        iFilledRectangle(ROLLBUTTON_POSX-BORDER, ROLLBUTTON_POSY-BORDER, ROLLBUTTON_LEN+2*BORDER, ROLLBUTTON_WID+2*BORDER);

        iSetColor(RED);
        iFilledRectangle(ROLLBUTTON_POSX, ROLLBUTTON_POSY, ROLLBUTTON_LEN, ROLLBUTTON_WID);

        iSetColor(BLACK);
        char str[20];
        if (current_game_state==1)      strcpy(str,"ROLL DICE");
        else                            strcpy(str,"END TURN");
        iText(ROLLBUTTON_POSX, ROLLBUTTON_POSY+ROLLBUTTON_WID/3, str, GLUT_BITMAP_TIMES_ROMAN_24);
    }

        iSetColor(BLACK);
        iFilledRectangle(0, 0, 60+BORDER*2, 20+BORDER*2);

        iSetColor(RED);
        iFilledRectangle(BORDER, BORDER, 60, 20);

        iSetColor(BLACK);
        iText(3, 3, "MENU", GLUT_BITMAP_HELVETICA_18);
}

#endif // LUDO_ANIMATION_H
