#include "TXLib.h"
#include "Bed.cpp"




int main()
{
    txCreateWindow(1200, 800);
    //txSetFillColor(TX_BLUE);




    int x_Menu_ = 0;
    int y_Menu_ = 0;
    int x_kadr_Menu = 0;
    HDC  Menu_ = txLoadImage("Картинки/Меню/Меню.bmp");

    int x_kadr_Pause = 0;
    int x_Pause = 10;
    int y_Pause = 10;
    HDC  Pause = txLoadImage("Картинки/Меню/Пауза.bmp");

    int x_Settings = 390;
    int y_Settings = 340;
    HDC  Settings = txLoadImage("Картинки/Меню/Шестерёнка.bmp");

    int x_Play = 387;
    int y_Play = 187;
    HDC  Play = txLoadImage("Картинки/Меню/Плей.bmp");

    int x_Leave = 355;
    int y_Leave = 480;
    HDC  Leave = txLoadImage("Картинки/Меню/Дверь.bmp");

    bool Menu = true;


    Picture Bed[4];
    Bed[0] = {0, 0, 131, 135, txLoadImage("Картинки/кровать_1.bmp")};
    Bed[1] = {0, 200, 189, 131, txLoadImage("Картинки/кровать_2.bmp")};
    Bed[2] = {0, 400, 192, 212, txLoadImage("Картинки/кровать_3.bmp")};
    Bed[3] = {0, 800, 164, 199, txLoadImage("Картинки/кровать_4.bmp")};

    while (!GetAsyncKeyState(VK_ESCAPE))
    {
        txBegin();
        txClear();
        if (Menu)
        {
            //txPlaySound("?.wav", SND_ASYNC);

            txTransparentBlt (txDC(), x_Menu_, y_Menu_, 1200, 824, Menu_, 1200 * x_kadr_Menu,  0, RGB(255, 127, 39));





        if (txMouseX() >=430   &&
        txMouseY() >=200  &&
        txMouseX() <=816 &&
        txMouseY() <=304&&
        Menu == true)
        {
        txTransparentBlt (txDC(), x_Play , y_Play , 448, 132, Play, 0,  0, RGB(255, 127, 39));
        }

        if (txMouseX() >=430   &&
        txMouseY() >=350  &&
        txMouseX() <=816 &&
        txMouseY() <=450&&
        Menu == true)
        {
        txTransparentBlt (txDC(), x_Settings , y_Settings , 457, 122, Settings, 0,  0, RGB(255, 127, 39));
        }

        if (txMouseX() >=418   &&
        txMouseY() >=490 &&
        txMouseX() <=816 &&
        txMouseY() <=590&&
        Menu == true)
        {
        txTransparentBlt (txDC(), x_Leave , y_Leave , 468, 140, Leave, 0,  0, RGB(255, 127, 39));
        }

        if (txMouseX() >=430   &&
        txMouseY() >=200  &&
        txMouseX() <=816 &&
        txMouseY() <=304&&
        txMouseButtons () ==1&&
        Menu == true)
        {
        txPlaySound("2.wav", SND_ASYNC);
        Menu=false;
        //txSleep(350);
        }

        if (txMouseX() >=430   &&
        txMouseY() >=350  &&
        txMouseX() <=816 &&
        txMouseY() <=450&&
        txMouseButtons () ==1&&
        Menu == true)
        {
        txPlaySound("2.wav", SND_ASYNC);
        //txSleep(350);
        }


    }
        else
        {
            //Меню
            txSetFillColour(TX_WHITE);




            if(GetAsyncKeyState('P') && Menu == false)  {

            Menu = true; }

            if (txMouseX() >=10   &&
            txMouseY() >=10  &&
            txMouseX() <=83 &&
            txMouseY() <=77&&
            Menu == false){
            x_kadr_Pause = 1;}
            else{x_kadr_Pause = 0;}

            if (txMouseX() >=10   &&
            txMouseY() >=10  &&
            txMouseX() <=83 &&
            txMouseY() <=77&&
            txMouseButtons () ==1&&
            Menu == false){txPlaySound("2.wav", SND_ASYNC);
            Menu = true;}


            /*
            txTransparentBlt (txDC(), x_Bed_1, y_Bed_1, 131, 135, Bed_1, 0, 0, RGB(255, 127, 39));
            txTransparentBlt (txDC(), x_Bed_2, y_Bed_2 + 200, 189, 131,  Bed_2, 0, 0, RGB(255, 127, 39));
            txTransparentBlt (txDC(), x_Bed_3, y_Bed_3 + 400, 192, 212,  Bed_3, 0, 0, RGB(255, 127, 39));
            txTransparentBlt (txDC(), x_Bed_4, y_Bed_4 + 600, 164, 199,  Bed_4, 0, 0, RGB(255, 127, 39));


            txTransparentBlt (txDC(), Bed_1.x, Bed_1.y,       131, 135,  Bed_1.picture, 0, 0, RGB(255, 127, 39));
            txTransparentBlt (txDC(), Bed_2.x, Bed_2.y + 200, 189, 131,  Bed_2.picture, 0, 0, RGB(255, 127, 39));
            txTransparentBlt (txDC(), Bed_3.x, Bed_3.y + 400, 192, 212,  Bed_3.picture, 0, 0, RGB(255, 127, 39));
            txTransparentBlt (txDC(), Bed_4.x, Bed_4.y + 600, 164, 199,  Bed_4.picture, 0, 0, RGB(255, 127, 39));
            */

            for (int nomer = 0; nomer < 4; nomer = nomer + 1)
                txTransparentBlt (txDC(), Bed[nomer].x,   Bed[nomer].y, Bed[nomer].width, Bed[nomer].height, Bed[nomer].picture);





            txTransparentBlt (txDC(), x_Pause , y_Pause , 74, 67, Pause, 73 * x_kadr_Pause,  0, RGB(255, 127, 39));
        }










        txSleep(20);
        txEnd();
    }


    return 0;
}
