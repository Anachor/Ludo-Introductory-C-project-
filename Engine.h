#ifndef LUDO_ENGINE_H
#define LUDO_ENGINE_H

struct Piece move_piece(struct Piece p, int k);

void initialize(int type_info[4], int no_of_pieces=4)
{
    No_of_pieces=no_of_pieces;
    int i,j;

    for (i=0; i<no_of_pieces; i++)
        for (j=0; j<4; j++)
            pieces[j][i].color=j,
            pieces[j][i].position=-1-j;

    for (i=0; i<4; i++)
        player_type[i]=type_info[i];
}


struct Piece move_piece(struct Piece q, int k)
{
    struct Piece p=q;
    int i,j;

    int home=13*p.color+6;

    int start=13*p.color+8;
    int home_st=(home-start+4*13)%(4*13);

    int distance=(p.position-start+4*13)%(4*13);

    if (p.position<0)
    {
        if (k==6)   p.position=start;
        else        return p;
    }

    else if (p.position>=500)
        return p;

    else if (p.position>=100)
    {
        if (p.position%100+k>6)
            return p;
        else
            p.position+=k;

        if (p.position%100==6)
            p.position=500+p.color;
    }

    else if (distance+k>home_st)
    {
        int r=distance+k-home_st;
        p.position=100+p.color*100+r;

        if (p.position%100==6)
            p.position=500+p.color;
    }

    else
        p.position=(p.position+k)%(4*13);

    return p;
}

int capture(int player, int id)
{
    int i, j;
    int pos=pieces[player][id].position;
    if (pos==8 || pos==21 || pos==34 || pos==47 || pos<0 || pos>=100)   return 0;

    int good=0;
    for ( i=0; i<4; i++)
        if (player!=i)
        {
            for (j=0; j<No_of_pieces; j++)
            {
                if (pieces[i][j].position==pos)
                {
                    good=1;
                    pieces[i][j].position=-1-i;
                }
            }
        }
    return good;
}
#endif
