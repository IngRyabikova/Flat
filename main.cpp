  //полезный комментарий:
    //проект начался
#include "TXLib.h"
#include "Bed.cpp"
#include "Bed2.cpp"

struct button
{

    HDC picture;
    int x;
    int y;
    const char* text;
    int x_kadr;
    int width;
    int height;
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

bool clickButton(button Button)
{
    if (txMouseX() >= Button.x && txMouseX() <= Button.x + 214 &&
        txMouseY() >= Button.y && txMouseY() <= Button.y + 66 && txMouseButtons() == 1)
    {
            return true;
    }


}

void drawObl(HDC Krestik)
{
    int x_Krestik = 1100;
    int y_Krestik = 60;

    txSetColor(TX_ORANGE);
    txSetFillColor(TX_WHITE);
    txRectangle(1100, 60, 1300, 750);


    txTransparentBlt(txDC(), x_Krestik, y_Krestik, 60, 60, Krestik, 0, 0, TX_WHITE);

}

int main()
{
    txCreateWindow (1300, 750);

    string category = "";


    HDC Fon = txLoadImage("Картинки/Координатная сетка.bmp");
    int x_Fon = 0;
    int y_Fon = 0;

    HDC Krestik = txLoadImage("Картинки/Knopochka.bmp");
    int x_Krestik = 1100;
    int y_Krestik = 60;

    int count_button = 5;
    button Button[count_button];

    Button[0] = {txLoadImage("Картинки/Кнопка.bmp"), 0, 0, "Кровати"};
    Button[1] = {Button[0].picture, 250,0, "Диваны"};
    Button[2] = {Button[0].picture, 500,0, "Столы"};
    Button[3] = {Button[0].picture, 750,0, ""};
    Button[4] = {Button[0].picture, 1000,0, ""};

    //Эту дичь тоже можно сделать кнопками (новый массив или новые переменные)
    //
    //Button[5]
    button settings = {txLoadImage("Картинки/Меню/Шестерёнка.bmp"), 390, 340, ""};
    button Play = {txLoadImage("Картинки/Меню/Плей.bmp"), 387, 187, ""};
    button Leave = {txLoadImage("Картинки/Меню/Дверь.bmp"), 355, 480, ""};
    button Menu_ = {txLoadImage("Картинки/Меню/Меню.bmp"), 0, 0, ""};
    button Pause = {txLoadImage("Картинки/Меню/Пауза.bmp"), 1200, 0,  "", 0};




    int x_Plan = 0;
    int y_Plan = 0;

    HDC Plan = txLoadImage("Картинки/План_квартиры.bmp");

    int x_Plan2 = 0;
    int y_Plan2 = 0;

    HDC Plan2 = txLoadImage("Картинки/План_квартиры2.bmp");

    bool Menu = true;

    bool drawOBL = false;

    bool str_1 = false;




    Picture Bed[25];
    Bed[0] = {1100, 150, 131, 135, txLoadImage("Картинки/кровать_1.bmp"), false, "Bed"};
    Bed[1] = {1100, 350, 189, 131, txLoadImage("Картинки/кровать_2.bmp"), false, "Bed"};
    Bed[2] = {1100, 550, 192, 212, txLoadImage("Картинки/кровать_3.bmp"), false, "Bed"};
    Bed[3] = {1100, 750, 164, 199, txLoadImage("Картинки/кровать_4.bmp"), false, "Bed"};
    Bed[4] = {1100, 150, 150,  70, txLoadImage("Картинки/Диван_1.bmp"), false, "Sofa"};
    Bed[5] = {1100, 250, 150, 70, txLoadImage("Картинки/Диван_2.bmp"), false, "Sofa"};
    Bed[6] = {1100, 350, 150, 70, txLoadImage("Картинки/Диван_3.bmp"), false, "Sofa"};
    Bed[7] = {1100, 450, 268, 142, txLoadImage("Картинки/Диваны/divan4.bmp"), false, "Sofa"};
    Bed[8] = {1105, 150, 164, 148, txLoadImage("Картинки/стол_1.bmp"), false, "Table"};
    Bed[9] = {1105, 350, 131, 130, txLoadImage("Картинки/стол_2.bmp"), false, "Table"};
    Bed[10] = {1105, 550, 169,  86, txLoadImage("Картинки/стол_3.bmp"), false, "Table"};
    Bed[11] = {1105, 650, 227, 137, txLoadImage("Картинки/стол_4.bmp"), false, "Table"};

    Picture2 Bed2[25];
    Bed2[0] = {500, 200, 131, 135, Bed[0].picture, false, "Bed"};
    Bed2[1] = {500, 200, 189, 131, Bed[1].picture, false, "Bed"};
    Bed2[2] = {500, 200, 192, 212, Bed[2].picture, false, "Bed"};
    Bed2[3] = {500, 200, 164, 199, Bed[3].picture, false, "Bed"};
    Bed2[4] = {500, 200, 150,  70, Bed[4].picture, false, "Sofa"};
    Bed2[5] = {500, 200, 150, 70, Bed[5].picture, false, "Sofa"};
    Bed2[6] = {500, 200, 150, 70, Bed[6].picture, false, "Sofa"};
    Bed2[7] = {500, 200, 268, 142, Bed[7].picture, false, "Sofa"};
    Bed2[8] = {505, 200, 164, 148, Bed[8].picture, false, "Table"};
    Bed2[9] = {505, 200, 131, 130, Bed[9].picture, false, "Table"};
    Bed2[10] = {505, 200, 169,  86, Bed[10].picture, false, "Table"};
    Bed2[11] = {505, 200, 227, 137, Bed[11].picture, false, "Table"};
    //bool drawTables = false;




    while(!GetAsyncKeyState(VK_ESCAPE))
    {
        txBegin();
        txClear();

        //Стартовая страница
        if (Menu)
        {
            txTransparentBlt (txDC(), Menu_.x, Menu_.y, 1300, 750, Menu_.picture, 0,  0, RGB(255, 127, 39));

            //Надпись в меню / название
            txSelectFont ("Comic Sans MS", 80);
            txSetColor(TX_RED);
            txDrawText(0, 0, txGetExtentX(), txGetExtentY() / 3, "Создай свой дизайн квартиры" );

            //Кнопки в меню
            //А мог бы быть цикл

            //Кнопка играть
            if (txMouseX() >=430   && txMouseY() >=200  &&  txMouseX() <=816 &&   txMouseY() <=304)
            {
                txTransparentBlt (txDC(), Play.x , Play.y , 448, 132, Play.picture, 0,  0, RGB(255, 127, 39));
            }

            //Кнопка настройки
            if (txMouseX() >=430 && txMouseY() >=350  && txMouseX() <=816 && txMouseY() <=450 && Menu == true)
            {
                txTransparentBlt (txDC(), settings.x , settings.y , 457, 122, settings.picture, 0,  0, RGB(255, 127, 39));
            }
            if (txMouseX() >=430 && txMouseY() >=350  && txMouseX() <=816 && txMouseY() <=450 && Menu == true && txMouseButtons () ==1)
            {
                txTransparentBlt (txDC(), settings.x , settings.y , 457, 122, settings.picture, 0,  0, RGB(255, 127, 39));
                str_1 = true;
            }
            if(str_1)
            {
                txClear();


                txTextOut(100, 100, "Привет :)");



            }

            //Кнопка выход
            if (txMouseX() >=418 && txMouseY() >=490 && txMouseX() <=816 && txMouseY() <=590 && Menu == true)
            {
                txTransparentBlt (txDC(), Leave.x , Leave.y , 468, 140, Leave.picture, 0,  0, RGB(255, 127, 39));
            }

            //Клик на выход
            if (txMouseX() >=418 && txMouseY() >=490 && txMouseX() <=816 && txMouseY() <=590 && txMouseButtons () ==1 )
            {
                txDisableAutoPause();
                return 0;
            }


            if (txMouseX() >=430 && txMouseY() >=200 && txMouseX() <=816 && txMouseY() <=304 &&
                txMouseButtons () ==1)
            {
                txPlaySound("2.wav", SND_ASYNC);
                Menu=false;

            }

            if (txMouseX() >=430   && txMouseY() >=350  && txMouseX() <=816 &&  txMouseY() <=450&&
                txMouseButtons () ==1)
            {
                txPlaySound("2.wav", SND_ASYNC);

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
            for(int nomer = 0; nomer < 4; nomer = nomer +1)
            {
                    drawButton(Button[nomer]);
            }

            if(drawOBL)
            {
                drawObl(Krestik);
            }



            if (clickButton(Button[0]))
            {
                category="Bed";
                drawOBL = true;
            }

            if (clickButton(Button[1]))
            {
                category="Sofa";
                drawOBL = true;
            }

            if (clickButton(Button[2]))
            {
                category="Table";
                drawOBL = true;
            }





            if(txMouseX() >= 1100   && txMouseY() >= 60  && txMouseX() <= 1140 && txMouseY() <= 100 &&
                txMouseButtons () ==1)
            {
                drawOBL = false;
                category="";

            }


for (int nomer = 0; nomer < 12; nomer = nomer + 1)
{
    if(Bed2[nomer].visible == true)
        txTransparentBlt (txDC(), Bed2[nomer].x,   Bed2[nomer].y, Bed2[nomer].width, Bed2[nomer].height, Bed2[nomer].picture);
}

            for (int nomer = 0; nomer < 12; nomer = nomer + 1)
            {
                     if (category == Bed[nomer].category)
                     {
                        txTransparentBlt (txDC(), Bed[nomer].x,   Bed[nomer].y, Bed[nomer].width, Bed[nomer].height, Bed[nomer].picture);
                     }


                    if(txMouseX() >= Bed[nomer].x  - 100    && txMouseY() >= Bed[nomer].y- 100  && txMouseX() <= Bed[nomer].x+ 100 && txMouseY() <= Bed[nomer].x + 100 &&
                    txMouseButtons () ==1 && category == Bed[nomer].category)
                    {
                     Bed2[nomer].visible = true;

                    }
                    if(Bed2[nomer].visible == true)
                    {
                       Bed2[nomer].visible = false;
                       Bed2[nomer].visible = true;
                       //я пытался)
                    }
            }










            if(GetAsyncKeyState('P'))
            {
                Menu = true;
            }

            //А почему не сделать паузу 2 картинками как с настройками и плеем?
            if (txMouseX() >=1220   && txMouseY() >=10  && txMouseX() <=1300 && txMouseY() <=77&&
                Menu == false)
            {
                Pause.x_kadr = 1;
            }
            else
            {
                Pause.x_kadr = 0;
            }

            if (txMouseX() >=1220   && txMouseY() >=10  && txMouseX() <=1300 && txMouseY() <=77&&
                txMouseButtons () ==1 && Menu == false)
            {
                txPlaySound("2.wav", SND_ASYNC);
                Menu = true ;

            }

            txTransparentBlt (txDC(), Pause.x, Pause.y , 74, 67, Pause.picture, 74 * Pause.x_kadr,  0, RGB(255, 127, 39));
        }

        txSleep(20);
        txEnd();
    }




    txDeleteDC(Fon);
    //Еще вагон картинок можно бы удалить
    for(int i = 0; i < 11; i = i +1)
        txDeleteDC(Bed[i].picture);

    for(int i = 0; i < 11; i = i +1)
        txDeleteDC(Bed2[i].picture);

    for(int i = 0; i < 10; i = i +1)
        txDeleteDC(Button[i].picture);

    Win32::TransparentBlt (txDC(),196,140,200,100,Plan,0,0,800,1100, TX_WHITE);

    Win32::TransparentBlt (txDC(),196,140,200,100,Plan2,0,0,1300,730, TX_WHITE);

    return 0;
}

  //полезный комментарий:
    //проект закончился
