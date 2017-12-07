#ifndef HEX_COLORS_H
#define HEX_COLORS_H

enum COLOR
{
    COLOR_0=0xFF0000,   //RED
    COLOR_1=0x009900,   //GREEN
    COLOR_2=0xFFFF00,   //YELLOW
    COLOR_3=0x0000FF,   //BLUE

    PIECE_COLOR_0=0x990000,   //DARK RED
    PIECE_COLOR_1=0x00FF00,   //LIGHT GREEN
    PIECE_COLOR_2=0x999900,   //DARK YELLOW
    PIECE_COLOR_3=0x000099,   //DARK BLUE

    BACKGROUND_COLOR=0x999999,
    BORDER_COLOR=0x000000,
    CELL_COLOR=0xFFFFFF,

    DICE_COLOR=0xFFFFFF,
    DICE_DOT_COLOR=0x000000,

    BLACK=0x000000,
    WHITE=0xFFFFFF,
    GREY=0xAAAAAA,
    YELLOW=0xFFFF00,
    RED=0xFF0000
};

void iSetColor(int HEX)
{
    iSetColor(HEX/(256*256), (HEX/256)%256, HEX%256);
}

int hex(int rgb[])
{
    return rgb[0]*256*256+rgb[1]*256+rgb[2];
}

#endif
