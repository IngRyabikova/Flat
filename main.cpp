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


    HDC Fon = txLoadImage("Картинки/Координатная сетка.bmp");
    int x_Fon = 0;
    int y_Fon = 0;

    int count_button = 5;
    button Button[count_button];

    Button[0] = {txLoadImage("Картинки/Кнопка.bmp"), 0, 0, "Кровати"};
    Button[1] = {txLoadImage("Картинки/Кнопка.bmp"), 250,0, "Диваны"};
    Button[2] = {txLoadImage("Картинки/Кнопка.bmp"), 500,0, "Столы"};
    Button[3] = {txLoadImage("Картинки/Кнопка.bmp"), 750,0, ""};
    Button[4] = {txLoadImage("Картинки/Кнопка.bmp"), 1000,0, ""};
        int x_Menu_ = 0;
    int y_Menu_ = 0;
    int x_kadr_Menu = 0;
    HDC  Menu_ = txLoadImage("Картинки/Меню/Меню.bmp");

    int x_kadr_Pause = 0;
    int x_Pause = 1220;
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
    Bed[0] = {0, 100, 131, 135, txLoadImage("Картинки/кровать_1.bmp")};
    Bed[1] = {0, 250, 189, 131, txLoadImage("Картинки/кровать_2.bmp")};
    Bed[2] = {0, 400, 192, 212, txLoadImage("Картинки/кровать_3.bmp")};
    Bed[3] = {0, 800, 164, 199, txLoadImage("Картинки/кровать_4.bmp")};




    while(!GetAsyncKeyState(VK_ESCAPE))
    {
        txBegin();
        txClear();

        //Стартовая страница
        if (Menu)
        {


            //txPlaySound("?.wav", SND_ASYNC);

            txTransparentBlt (txDC(), x_Menu_, y_Menu_, 1200, 824, Menu_, 1200 * x_kadr_Menu,  0, RGB(255, 127, 39));


            //Надпись в меню / название
            txSelectFont ("Comic Sans MS", 80);
            txSetColor(TX_RED);
            txDrawText(0, 0, txGetExtentX(), txGetExtentY() / 3, "Создай свой дизайн квартиры" );




            //Кнопки в меню


            //Кнопка играть
            if (txMouseX() >=430   && txMouseY() >=200  &&  txMouseX() <=816 &&   txMouseY() <=304)
            {
                txTransparentBlt (txDC(), x_Play , y_Play , 448, 132, Play, 0,  0, RGB(255, 127, 39));
            }


            //Кнопка настройки
            if (txMouseX() >=430 && txMouseY() >=350  && txMouseX() <=816 && txMouseY() <=450 && Menu == true)

            {
                txTransparentBlt (txDC(), x_Settings , y_Settings , 457, 122, Settings, 0,  0, RGB(255, 127, 39));
            }


            //Кнопка выход
            if (txMouseX() >=418 && txMouseY() >=490 && txMouseX() <=816 && txMouseY() <=590 && Menu == true)

            {
                txTransparentBlt (txDC(), x_Leave , y_Leave , 468, 140, Leave, 0,  0, RGB(255, 127, 39));
            }
            //Клик на выход
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

        //Редактор
        else
        {
            //Меню
            txSetFillColour(TX_WHITE);


            //Координатная сетка /фон

            txTransparentBlt(txDC(), x_Fon, y_Fon, 1300, 750, Fon, 0, 0, TX_YELLOW);


            //Жёлтые кнопки наверху экрана

            for(int nomer = 0; nomer < count_button; nomer = nomer +1)
            {
                    drawButton(Button[nomer]);
            }

          //Тестовая кнопка
       // Win32::RoundRect (txDC(), 400, 100, 800, 250, 30, 30);
        /*
        txDrawText (400, 150, 800, 200, "кнопка");
        if (txMouseX() >= 400 && txMouseX() <= 800 &&
            txMouseY() >= 150 && txMouseY() <= 200 && txMouseButtons() == 1)
        {
            txTextOut(100, 100, "Это работает!");
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


            for (int nomer = 0; nomer < 4; nomer = nomer + 1)
                txTransparentBlt (txDC(), Bed[nomer].x,   Bed[nomer].y, Bed[nomer].width, Bed[nomer].height, Bed[nomer].picture);





            txTransparentBlt (txDC(), x_Pause , y_Pause , 74, 67, Pause, 73 * x_kadr_Pause,  0, RGB(255, 127, 39));
        }










        txSleep(20);
        txEnd();
    }

     txDeleteDC(Fon);


    return 0;
}

