#include "TXLib.h"
#include "Bed.cpp"
#include "Button.cpp"

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

  //  string PageCategory = "";



    HDC Fon = txLoadImage("Картинки/Координатная сетка.bmp");
    int x_Fon = 0;
    int y_Fon = 0;

    HDC Krestik = txLoadImage("Картинки/Кнопки/Knopochka.bmp");
    int x_Krestik = 1100;
    int y_Krestik = 60;

    int count_button = 5;
    button Button[count_button];

    Button[0] = {txLoadImage("Картинки/Кнопки/Кнопка.bmp"), 0, 0, "Кровати","Bed"};
    Button[1] = {Button[0].picture, 250,0, "Диваны","Sofa"};
    Button[2] = {Button[0].picture, 500,0, "Столы", "Table"};
    Button[3] = {Button[0].picture, 750,0, "", "" };
    Button[4] = {Button[0].picture, 1000,0, "", ""};


    HDC Strelka =  txLoadImage("Картинки/Кнопки/Стрелочка.bmp");
    int x_Strelka= 0;
    int y_Strelka = 0;

    //Меню стартовой страницы
    button Button_MENU[3];
    Button_MENU[0] = {txLoadImage("Картинки/Меню/Шестерёнка.bmp"), 390, 340, "", "settings", 457, 122};
    Button_MENU[1] = {txLoadImage("Картинки/Меню/Плей.bmp"), 387, 187, "", "start", 448, 132};
    Button_MENU[2] = {txLoadImage("Картинки/Меню/Дверь.bmp"), 355, 480, "", "exit", 468, 140};
    const char* PAGE = "start";

    button Menu = {txLoadImage("Картинки/Меню/Меню.bmp"), 0, 0, ""};
    button Pause = {txLoadImage("Картинки/Меню/Пауза.bmp"), 1200, 0,  "", "", 0};

    int x_Plan = 0;
    int y_Plan = 0;
    HDC Plan = txLoadImage("Картинки/План_квартиры.bmp");

    int x_Plan2 = 0;
    int y_Plan2 = 0;
    HDC Plan2 = txLoadImage("Картинки/План_квартиры2.bmp");

    //А они прям все нужны?
    bool Menu1 = true;

    bool drawOBL = false;

    bool str_1 = false;

    int Active_Pic = 0;


    bool klik = true;
    Picture variants[25];
    variants[0] = {1100, 150, 131, 135, txLoadImage("Картинки/Кровати/кровать_1.bmp"), false, "Bed"};
    variants[1] = {1100, 350, 189, 131, txLoadImage("Картинки/Кровати/Кровать_2.bmp"), false, "Bed"};
    variants[2] = {1100, 550, 192, 212, txLoadImage("Картинки/Кровати/Кровать_3.bmp"), false, "Bed"};
    variants[3] = {1100, 750, 164, 199, txLoadImage("Картинки/Кровати/Кровать_4.bmp"), false, "Bed"};
    variants[4] = {1100, 150, 150,  70, txLoadImage("Картинки/Диваны/Диван_1.bmp"), false, "Sofa"};
    variants[5] = {1100, 250, 150, 70, txLoadImage("Картинки/Диваны/Диван_2.bmp"), false, "Sofa"};
    variants[6] = {1100, 350, 150, 70, txLoadImage("Картинки/Диваны/Диван_3.bmp"), false, "Sofa"};
    variants[7] = {1100, 450, 200, 70, txLoadImage("Картинки/Диваны/Divan2.bmp"), false, "Sofa"};
    variants[8] = {1105, 150, 164, 148, txLoadImage("Картинки/Столы/Стол_1.bmp"), false, "Table"};
    variants[9] = {1105, 350, 131, 130, txLoadImage("Картинки/Столы/Стол_2.bmp"), false, "Table"};
    variants[10] = {1105, 550, 169,  86, txLoadImage("Картинки/Столы/Стол_3.bmp"), false, "Table"};
    variants[11] = {1105, 650, 227, 137, txLoadImage("Картинки/Столы/Стол_4.bmp"), false, "Table"};


    Picture Bed2[2500];
    int n_pics = 0;

    while(!GetAsyncKeyState(VK_ESCAPE))
    {
        txBegin();
        txClear();

        //Стартовая страница
        if (PAGE == "start")
        {
            txTransparentBlt (txDC(), Menu.x, Menu.y, 1300, 750, Menu.picture, 0,  0, RGB(255, 127, 39));

            //Надпись в меню / название
            txSelectFont ("Comic Sans MS", 80);
            txSetColor(TX_RED);
            txDrawText(0, 0, txGetExtentX(), txGetExtentY() / 3, "Создай свой дизайн квартиры" );

            //Кнопки в меню
            for(int nomer = 0; nomer < 3; nomer = nomer +1)
            {
                if (txMouseX() >= Button_MENU[nomer].x &&
                    txMouseY() >= Button_MENU[nomer].y &&
                    txMouseX() <= Button_MENU[nomer].x + 500 &&
                    txMouseY() <= Button_MENU[nomer].y + 100)
                {
                   drawButton2(Button_MENU[nomer]);
                }

                //Может это не категорией назвать? Оставить 3 кликами
                if (clickButton2(Button_MENU[nomer]))
                {
                    category = Button_MENU[nomer].category;
                }
            }

            if (category == Button_MENU[2].category)
            {
                txDisableAutoPause();
                return 0;
            }
            if (category == Button_MENU[1].category)
            {
                PAGE = "redactor";
            }
            if (category == Button_MENU[0].category)
            {
                PAGE = "settings";
            }
        }

        //Настройки
        else if(PAGE == "settings")
        {
            txSetFillColor(TX_WHITE);
            txRectangle(0, 0, 1300, 750);

            txSetColor(TX_BLACK);
            txSelectFont("Arial", 30);
            txDrawText (300, 0, 400, 100, "Назад");

            Win32::TransparentBlt(txDC(), x_Strelka, y_Strelka, 50, 50, Strelka, 0, 0, 225,225, TX_RED);

            if (txMouseX() >= 0 && txMouseX() <= 150 &&
                txMouseY() >= 0 && txMouseY() <= 100 &&
                txMouseButtons() & 1)
            {
                PAGE = "start";
                category = "";
            }

            txTextOut(100, 300, "Привет :)");
        }

        //Редактор
        else if (PAGE == "redactor")
        {
            //Меню
            txSetFillColour(TX_WHITE);

            //Координатная сетка /фон
            txTransparentBlt(txDC(), x_Fon, y_Fon, 1300, 750, Fon, 0, 0, TX_YELLOW);

            //Жёлтые кнопки наверху экрана
            for (int nomer = 0; nomer < 3; nomer = nomer +1)
            {
                drawButton(Button[nomer]);
            }

            if(drawOBL)
            {
                drawObl(Krestik);
            }

            //Выбор категории
            for(int nomer = 0; nomer < count_button; nomer = nomer + 1)
            {
                if (clickButton(Button[nomer]))
                {
                    category = Button[nomer].category;
                    drawOBL = true;
                }
            }

            //Выход из категории
            if(txMouseX() >= 1100   && txMouseY() >= 60  && txMouseX() <= 1140 && txMouseY() <= 100 &&
                txMouseButtons () ==1)
            {
                drawOBL = false;
                category="";
            }


            //А их 12?
            for (int nomer = 0; nomer < 12; nomer = nomer + 1)
            {
                if(Bed2[nomer].visible == true)

                drawBED2(Bed2[nomer]);
                //txTransparentBlt (txDC(), Bed2[nomer].x,   Bed2[nomer].y, Bed2[nomer].width, Bed2[nomer].height, Bed2[nomer].picture);
            }

            for (int nomer = 0; nomer < 12; nomer = nomer + 1)
            {
                 if (category == variants[nomer].category)
                 {
                        drawVariant(variants[nomer]);
                 }
            }
            for (int nomer = 0; nomer <  12; nomer = nomer + 1)
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

            //Движение мышкой
            for (int n = 0; n <  n_pics; n = n + 1)
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

            if(Active_Pic >= 0 && txMouseButtons() == 1 )
            {
                Bed2[Active_Pic].x = txMouseX();
                Bed2[Active_Pic].y = txMouseY();

            }
            if(txMouseButtons() == 0)
            Active_Pic = -1;





            if(txMouseButtons () == 0)
                klik = true;

            for (int nomer = 0; nomer <  n_pics; nomer = nomer + 1)
            {
                txTransparentBlt (txDC(), Bed2[nomer].x,   Bed2[nomer].y, Bed2[nomer].width, Bed2[nomer].height, Bed2[nomer].picture);
            }





            if(GetAsyncKeyState('P'))
            {
                PAGE = "start";
            }

            //А почему не сделать паузу 2 картинками как с настройками и плеем?
            if (txMouseX() >=1220   && txMouseY() >=10  && txMouseX() <=1300 && txMouseY() <=77)
            {
                Pause.x_kadr = 1;
            }
            else
            {
                Pause.x_kadr = 0;
            }

            if (txMouseX() >=1220   && txMouseY() >=10  && txMouseX() <=1300 && txMouseY() <=77&&
                txMouseButtons () ==1)
            {
                txPlaySound("2.wav", SND_ASYNC);
                PAGE = "start";
            }

            txTransparentBlt (txDC(), Pause.x, Pause.y , 74, 67, Pause.picture, 74 * Pause.x_kadr,  0, RGB(255, 127, 39));
        }

        txSleep(20);
        txEnd();
    }




    //Удаление картинок
    txDeleteDC(Fon);
    for(int i = 0; i < 11; i = i +1)
        txDeleteDC(variants[i].picture);


    deletePic(Button, Button_MENU, Menu, Pause);


 //   for(int i = 0; i < 10; i = i +1)
 //       txDeleteDC(Button[i].picture);

    //Зачем это
    Win32::TransparentBlt (txDC(),196,140,200,100,Plan,0,0,800,1100, TX_WHITE);

    Win32::TransparentBlt (txDC(),196,140,200,100,Plan2,0,0,1300,730, TX_WHITE);

    return 0;
}
