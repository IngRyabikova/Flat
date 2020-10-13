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



void drawPicture(Picture variants)
{
    txTransparentBlt (txDC(), variants.x,   variants.y, variants.width, variants.height, variants.picture);
}

void drawAllVariants(string category, Picture* variants)
{
    for (int nomer = 0; nomer < 12; nomer = nomer + 1)
    {
         if (category == variants[nomer].category)
         {
                drawPicture(variants[nomer]);
         }
    }
}








void drawAllBED2(Picture* Bed2, int n_pics)
{
    for (int nomer = 0; nomer <  n_pics; nomer = nomer + 1)
            {
                if(Bed2[nomer].visible == true)
                    drawPicture(Bed2[nomer]);



            }


}









int movePic(Picture* Bed2, int Active_Pic, int n_pics)
{
    //Движение мышкой
    for (int n = 0; n < n_pics; n = n + 1)
    {
        if(txMouseX() >= Bed2[n].x &&      //!!!!!!!!!!!!!
            txMouseY() >= Bed2[n].y &&
            txMouseX() <= Bed2[n].x +  Bed2[n].width &&
            txMouseY() <= Bed2[n].y +  Bed2[n].height  &&
            txMouseButtons() == 1 )
        {
            //Bed2[n].x = txMouseX();
            //Bed2[n].y = txMouseY();
            Active_Pic = n;

        }
    }



    if(Active_Pic >= 0 && txMouseButtons() == 1)
    {
        Bed2[Active_Pic].x = txMouseX();
        Bed2[Active_Pic].y = txMouseY();

    }
    if(txMouseButtons() == 0)
        Active_Pic = -1;

    return Active_Pic;

}










/*

bool()

{

                    for (int nomer = 0; nomer <  25; nomer = nomer + 1)
                    {
                        if (txMouseX() >= variants[nomer].x    &&
                        txMouseY() >= variants[nomer].y  &&
                        txMouseX() <= variants[nomer].x +  variants[nomer].width &&
                        txMouseY() <= variants[nomer].y +  variants[nomer].height &&
                        txMouseButtons () ==1 && category == variants[nomer].category &&  klik == true)
                        {
                            Bed2[n_pics] = {random(100, 800), random(100, 600),  variants[nomer].width,  variants[nomer].height, variants[nomer].picture};
                            n_pics++;
                            klik = false;
                        }
                    }







}


*/
