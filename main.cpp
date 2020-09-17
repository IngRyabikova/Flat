#include "TXLib.h"
#include "Bed.cpp"

struct button
{
    HDC picture;
    int x;
    int y;
    const char* text;
    int x_kadr;
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
    button settings = {txLoadImage("Картинки/Меню/Шестерёнка.bmp"), 390, 340, ""};
    button Play = {txLoadImage("Картинки/Меню/Плей.bmp"), 387, 187, ""};
    button Leave = {txLoadImage("Картинки/Меню/Дверь.bmp"), 355, 480, ""};
    button Menu_ = {txLoadImage("Картинки/Меню/Меню.bmp"), 0, 0, ""};
    button Pause = {txLoadImage("Картинки/Меню/Пауза.bmp"), 0, 0,  "", 0};
    //Эту дичь тоже можно сделать кнопками (новый массив или новые переменные)

  int x_Plan = 0;
   int y_Plan = 0;
  HDC Plan = txLoadImage("Картинки/План_квартиры.bmp");




    bool Menu = true;

    Picture Bed[8];
    //Какие-то картинки не сохранились, поэтому я изменил адреса
    Bed[0] = {0, 0, 131, 135, txLoadImage("Картинки/кровать_1.bmp"), false};
    Bed[1] = {0, 200, 189, 131, txLoadImage("Картинки/кровать_2.bmp"), false};
    Bed[2] = {0, 400, 192, 212, txLoadImage("Картинки/кровать_3.bmp"), false};
    Bed[3] = {0, 600, 164, 199, txLoadImage("Картинки/кровать_4.bmp"), false};
    Bed[4] = {200, 0, 191, 90, txLoadImage("Картинки/Диван_1.bmp"), false};
    Bed[5] = {200, 150, 192, 133, txLoadImage("Картинки/Диван_2.bmp"), false};
    Bed[6] = {200, 300, 202, 92, txLoadImage("Картинки/Диван_3.bmp"), false};
    Bed[7] = {200, 450, 268, 142, txLoadImage("Картинки/Диван_4.bmp"), false};

    Picture Table[4];
    Table[0] = {450, 0, 164, 148, txLoadImage("Картинки/стол_1.bmp"), false};
    Table[1] = {450, 200, 131, 130, txLoadImage("Картинки/стол_2.bmp"), false};
    Table[2] = {450, 350, 169, 86, txLoadImage("Картинки/стол_3.bmp"), false};
    Table[3] = {500, 500, 227, 137, txLoadImage("Картинки/стол_4.bmp"), false};




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
                //txSleep(350);
            }

            if (txMouseX() >=430   && txMouseY() >=350  && txMouseX() <=816 &&  txMouseY() <=450&&
                txMouseButtons () ==1)
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

             txTransparentBlt (txDC(), x_Plan, y_Plan , 1300, 750, Plan, 0,  0, RGB(255, 127, 39));


            //Координатная сетка /фон
           // txTransparentBlt(txDC(), x_Fon, y_Fon, 1300, 750, Fon, 0, 0, TX_YELLOW);




           //Тестовая кнопка
           // Win32::RoundRect (txDC(), 400, 100, 800, 250, 30, 30);
            /*
            txDrawText (400, 150, 800, 200, "кнопка");
            if (txMouseX() >= 400 && txMouseX() <= 800 &&
                txMouseY() >= 150 && txMouseY() <= 200 && txMouseButtons() == 1)
            {
                txTextOut(100, 100, "Это работает!");
            }     */


            //Меню == ложь можно не проверять
            if(GetAsyncKeyState('P') && Menu == false)
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
                txPlaySound("2.wav", SND_ASYNC);Menu = true ;

            }

//int nomer = 0;
//int nomer2 = 0;




       if (    txMouseX()  >= Bed[1].x  - 10    &&
            txMouseX()  <= Bed[1].x  + 200  &&
            txMouseY()  >= Bed[1].y  - 10  &&
            txMouseY()  <= Bed[1].y  + 200 &&
            txMouseButtons () ==1    )
            {
             Bed[1].x  =  txMouseX()-100;
             Bed[1].y =  txMouseY()-100;
             }
              //на работает хз почему
            txTransparentBlt (txDC(), Pause.x, Pause.y , 74, 67, Pause.picture, 74 * Pause.x_kadr,  0, RGB(255, 127, 39));

  //Жёлтые кнопки наверху экрана
            for(int nomer = 0; nomer < count_button; nomer = nomer +1)
            {
                    drawButton(Button[nomer]);
            }



        }













        txSleep(20);
        txEnd();
    }

    txDeleteDC(Fon);
    //Еще вагон картинок можно бы удалить


    return 0;
}
