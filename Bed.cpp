#include "TXLib.h"

struct Picture
{
    int x;
    int y;
    const char* address;
    bool visible;
    string category;
    HDC picture;
    int width;
    int height;

    //Рисование
    void draw()
    {
        txTransparentBlt (txDC(), x, y, width, height, picture);
    }

    //Рисование иконки плана
    void draw2()
    {
        Win32::TransparentBlt (txDC(), x, y, 150, 120, picture, 0, 0, width, height, TX_YELLOW);
    }
};


//Рисование всех вариантов в цикле
void drawAllVariants(string category, Picture* variants, int count_variants)
{
    for (int nomer = 0; nomer < count_variants; nomer = nomer + 1)
    {
        if (category == variants[nomer].category)
        {
            variants[nomer].draw();
        }
    }
}
void drawAllPlans(string category, Picture* variants, int count_variants)
{
    for (int nomer = 0; nomer < count_variants; nomer = nomer + 1)
    {
        if (category == variants[nomer].category)
        {
            variants[nomer].draw2();
        }
    }
}

//Рисование Bed2
void drawAllBED2(Picture* Bed2, int n_pics)
{
    for (int nomer = 0; nomer <  n_pics; nomer = nomer + 1)
    {
        if(Bed2[nomer].visible == true)
            Bed2[nomer].draw();
    }
}

//Движение картинок
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


     bool monolit = true;
     int x1 = 0, y1 = 0;
    if(txMouseButtons() == 0)
    {
        for (int x = Bed2[Active_Pic].x;
                 x < Bed2[Active_Pic].x + Bed2[Active_Pic].width;
                 x = x + 5)
        {
            for (int y = Bed2[Active_Pic].y;
                     y < Bed2[Active_Pic].y + Bed2[Active_Pic].height;
                     y = y + 5)

            {
                if (txGetPixel(x, y) == TX_BLACK)
                {
                    monolit = false;
                    x1 = x;
                    y1 = y;
                }
            }
        }

        //Если столкнулись с черным, кидаем влево
        if (!monolit)
        {
            Bed2[Active_Pic].x = x1 + 5;
            Bed2[Active_Pic].y = y1 + 5;
        }



        Active_Pic = -1;
    }

    return Active_Pic;
}


//Удаление всех картинок
void deletePicBed(Picture* variants, int count_variants, Picture* Plans)
{
    for(int i = 0; i < count_variants; i = i +1)
    {
        txDeleteDC(variants[i].picture);
        txDeleteDC(Plans[i].picture);
    }
}
