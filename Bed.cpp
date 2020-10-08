#include "TXLib.h"

struct Picture
{
    int x;
    int y;
    int width;
    int height;
    HDC picture;
    bool visible;
    string category;
};




void drawVariant(Picture variants)
{
    txTransparentBlt (txDC(), variants.x,   variants.y, variants.width, variants.height, variants.picture);
}



void drawBED2(Picture Bed2)
{
    txTransparentBlt (txDC(), Bed2.x,   Bed2.y, Bed2.width, Bed2.height, Bed2.picture);


}
