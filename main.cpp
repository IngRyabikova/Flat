#include "TXLib.h"
#include "Bed.cpp"

struct button
{
    HDC picture;
    int x;
    int y;
    const char* text;
};

void drawButton(button Button1)
{
    txTransparentBlt(txDC(), Button1.x, Button1.y, 200, 60, Button1.picture, 0, 0, TX_WHITE);

    if (Button1.text != "")
    {
        txSelectFont ("Comic Sans MS", 30);
        txSetColor(TX_BLACK);
        txTextOut(Button1.x + 15, Button1.y + 10, Button1.text);
    }

};

int main()
{
    txCreateWindow (1300, 750);


    HDC Fon = txLoadImage("Êàðòèíêè/Êîîðäèíàòíàÿ ñåòêà.bmp");
    int x_Fon = 0;
    int y_Fon = 0;

    int count_button = 5;
    button Button[count_button];

    Button[0] = {txLoadImage("Êàðòèíêè/Êíîïêà.bmp"), 0, 0, "Êðîâàòè"};
    Button[1] = {txLoadImage("Êàðòèíêè/Êíîïêà.bmp"), 250,0, "Äèâàíû"};
    Button[2] = {txLoadImage("Êàðòèíêè/Êíîïêà.bmp"), 500,0, "Ñòîëû"};
    Button[3] = {txLoadImage("Êàðòèíêè/Êíîïêà.bmp"), 750,0, ""};
    Button[4] = {txLoadImage("Êàðòèíêè/Êíîïêà.bmp"), 1000,0, ""};
        int x_Menu_ = 0;
    int y_Menu_ = 0;
    int x_kadr_Menu = 0;
    HDC  Menu_ = txLoadImage("Êàðòèíêè/Ìåíþ/Ìåíþ.bmp");

    int x_kadr_Pause = 0;
    int x_Pause = 1220;
    int y_Pause = 10;
    HDC  Pause = txLoadImage("Êàðòèíêè/Ìåíþ/Ïàóçà.bmp");

    int x_Settings = 390;
    int y_Settings = 340;
    HDC  Settings = txLoadImage("Êàðòèíêè/Ìåíþ/Øåñòåð¸íêà.bmp");

    int x_Play = 387;
    int y_Play = 187;
    HDC  Play = txLoadImage("Êàðòèíêè/Ìåíþ/Ïëåé.bmp");

    int x_Leave = 355;
    int y_Leave = 480;
    HDC  Leave = txLoadImage("Êàðòèíêè/Ìåíþ/Äâåðü.bmp");

    bool Menu = true;


    Picture Bed[8];
    Bed[0] = {0, 0, 131, 135, txLoadImage("Êàðòèíêè/êðîâàòü_1.bmp")};
    Bed[1] = {0, 200, 189, 131, txLoadImage("Êàðòèíêè/êðîâàòü_2.bmp")};
    Bed[0] = {0, 100, 131, 135, txLoadImage("Êàðòèíêè/êðîâàòü_1.bmp")};
    Bed[1] = {0, 250, 189, 131, txLoadImage("Êàðòèíêè/êðîâàòü_2.bmp")};
    Bed[2] = {0, 400, 192, 212, txLoadImage("Êàðòèíêè/êðîâàòü_3.bmp")};
    Bed[3] = {0, 600, 164, 199, txLoadImage("Êàðòèíêè/êðîâàòü_4.bmp")};
    Bed[4] = {200, 0, 191, 90, txLoadImage("Êàðòèíêè/Äèâàí_1.bmp")};
    Bed[5] = {200, 150, 192, 133, txLoadImage("Êàðòèíêè/Äèâàí_2.bmp")};
    Bed[6] = {200, 300, 202, 92, txLoadImage("Êàðòèíêè/Äèâàí_3.bmp")};
    Bed[7] = {200, 450, 268, 142, txLoadImage("Êàðòèíêè/Äèâàí_4.bmp")};

    Picture Table[4];
    Table[0] = {450, 0, 164, 148, txLoadImage("Êàðòèíêè/ñòîë_1.bmp"), false};
    Table[1] = {450, 200, 131, 130, txLoadImage("Êàðòèíêè/ñòîë_2.bmp"), false};
    Table[2] = {450, 350, 169, 86, txLoadImage("Êàðòèíêè/ñòîë_3.bmp"), false};
    Table[3] = {500, 500, 227, 137, txLoadImage("Êàðòèíêè/ñòîë_4.bmp"), false};





    while(!GetAsyncKeyState(VK_ESCAPE))
    {
        txBegin();
        txClear();

        //Ñòàðòîâàÿ ñòðàíèöà
        if (Menu)
        {


            //txPlaySound("?.wav", SND_ASYNC);

            txTransparentBlt (txDC(), x_Menu_, y_Menu_, 1200, 824, Menu_, 1200 * x_kadr_Menu,  0, RGB(255, 127, 39));


            //Íàäïèñü â ìåíþ / íàçâàíèå
            txSelectFont ("Comic Sans MS", 80);
            txSetColor(TX_RED);
            txDrawText(0, 0, txGetExtentX(), txGetExtentY() / 3, "Ñîçäàé ñâîé äèçàéí êâàðòèðû" );




            //Êíîïêè â ìåíþ


            //Êíîïêà èãðàòü
            if (txMouseX() >=430   && txMouseY() >=200  &&  txMouseX() <=816 &&   txMouseY() <=304)
            {
                txTransparentBlt (txDC(), x_Play , y_Play , 448, 132, Play, 0,  0, RGB(255, 127, 39));
            }


            //Êíîïêà íàñòðîéêè
            if (txMouseX() >=430 && txMouseY() >=350  && txMouseX() <=816 && txMouseY() <=450 && Menu == true)

            {
                txTransparentBlt (txDC(), x_Settings , y_Settings , 457, 122, Settings, 0,  0, RGB(255, 127, 39));
            }


            //Êíîïêà âûõîä
            if (txMouseX() >=418 && txMouseY() >=490 && txMouseX() <=816 && txMouseY() <=590 && Menu == true)
            {
                txTransparentBlt (txDC(), x_Leave , y_Leave , 468, 140, Leave, 0,  0, RGB(255, 127, 39));
            }
            //Êëèê íà âûõîä
            if (txMouseX() >=418 && txMouseY() >=490 && txMouseX() <=816 && txMouseY() <=590 && txMouseButtons () ==1 )
            {
                txDisableAutoPause();
                return 0;
            }



            if (txMouseX() >=430 && txMouseY() >=200 && txMouseX() <=816 && txMouseY() <=304 &&
                txMouseButtons () ==1 && Menu == true)

            {
                txPlaySound("2.wav", SND_ASYNC);
                Menu=false;
                //txSleep(350);
            }



            if (txMouseX() >=430   && txMouseY() >=350  && txMouseX() <=816 &&  txMouseY() <=450&&
                txMouseButtons () ==1&& Menu == true)
            {
                txPlaySound("2.wav", SND_ASYNC);
                //txSleep(350);
            }
        }

        //Ðåäàêòîð
        else
        {
            //Ìåíþ
            txSetFillColour(TX_WHITE);

            //Êîîðäèíàòíàÿ ñåòêà /ôîí
            txTransparentBlt(txDC(), x_Fon, y_Fon, 1300, 750, Fon, 0, 0, TX_YELLOW);


            //Æ¸ëòûå êíîïêè íàâåðõó ýêðàíà
            for(int nomer = 0; nomer < count_button; nomer = nomer +1)
            {
                    drawButton(Button[nomer]);
            }

          //Òåñòîâàÿ êíîïêà
       // Win32::RoundRect (txDC(), 400, 100, 800, 250, 30, 30);
        /*
        txDrawText (400, 150, 800, 200, "êíîïêà");
        if (txMouseX() >= 400 && txMouseX() <= 800 &&
            txMouseY() >= 150 && txMouseY() <= 200 && txMouseButtons() == 1)
        {
            txTextOut(100, 100, "Ýòî ðàáîòàåò!");
        }     */


            if(GetAsyncKeyState('P') && Menu == false)
            {
                Menu = true;
            }

            if (txMouseX() >=1220   && txMouseY() >=10  && txMouseX() <=1300 && txMouseY() <=77&&
                Menu == false)
            {
                x_kadr_Pause = 1;
            }

            else
            {
                x_kadr_Pause = 0;
            }

            if (txMouseX() >=1220   && txMouseY() >=10  && txMouseX() <=1300 && txMouseY() <=77&&
                txMouseButtons () ==1 && Menu == false)
            {
                txPlaySound("2.wav", SND_ASYNC);Menu = true ;

            }


            for (int nomer = 0; nomer < 8; nomer = nomer + 1)
                txTransparentBlt (txDC(), Bed[nomer].x,   Bed[nomer].y, Bed[nomer].width, Bed[nomer].height, Bed[nomer].picture);


                 for (int nomer2 = 0; nomer2 < 4; nomer2 = nomer2 + 1)
                 {
                 if(Table[nomer2].visible)
                            txTransparentBlt (txDC(), Table[nomer2].x,   Table[nomer2].y, Table[nomer2].width, Table[nomer2].height, Table[nomer2].picture);

                  txDrawText (400, 150, 800, 200, "êíîïêà");
                    if (txMouseX() >= 400 && txMouseX() <= 800 &&
                        txMouseY() >= 150 && txMouseY() <= 200 && txMouseButtons() == 1)
                    {
                        Table[nomer2].visible = true;
                        txTextOut(100, 100, "Ýòî ðàáîòàåò!");
                    }
        if(GetAsyncKeyState(VK_SPACE))
        Table[nomer2].visible = false;
        } //ñêîáêà îò for




       if (    txMouseX()  >= Bed[1].x  - 10    &&
            txMouseX()  <= Bed[1].x  + 200  &&
            txMouseY()  >= Bed[1].y  - 10  &&
            txMouseY()  <= Bed[1].y  + 200 &&
            txMouseButtons () ==1    )
            {
             Bed[1].x  =  txMouseX()-100;
             Bed[1].y =  txMouseY()-100;
             }

            txTransparentBlt (txDC(), x_Pause , y_Pause , 74, 67, Pause, 73 * x_kadr_Pause,  0, RGB(255, 127, 39));

        }










        txSleep(20);
        txEnd();
    }

     txDeleteDC(Fon);


    return 0;
}