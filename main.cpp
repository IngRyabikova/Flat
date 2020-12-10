#include "TXLib.h"
#include "Lib/Bed.cpp"
#include "Lib/Button.cpp"
#include "Lib/Files.cpp"
#include <fstream>
#include <iostream>

using namespace std;

///void drawObl рисование области выбора картинки
void drawObl(HDC Krestik)
{
    txSetColor(TX_ORANGE);
    txSetFillColor(TX_WHITE);
    txRectangle(1100, 60, 1300, 750);
    txTransparentBlt(txDC(), 1100, 60, 60, 60, Krestik, 0, 0, TX_WHITE);
}


///int main главная функция
int main()
{
    txCreateWindow (1300, 750);
    txTextCursor (false);   //убирает курсор *прекол


    ///Колиечство кнопок
    int count_button = 9;
    ///кнопки страницы редактора
    button Button[count_button];
    Button[0] = {txLoadImage("Картинки/Кнопки/Кнопка.bmp"), 0, 0, "Планы","Plan", 200, 60};
    Button[1] = {Button[0].picture, 0, 0, "Кровати","Кровати", 200, 60};
    Button[2] = {Button[0].picture, 0, 0, "Столы", "Столы", 200, 60};
    Button[3] = {Button[0].picture, 0, 0, "Диваны", "Диваны", 200, 60 };
    Button[4] = {Button[0].picture, 0, 0, "Кухня", "туалет", 200, 60};
    Button[5] = {Button[0].picture, 0, 0, "Сохранить", "Save", 200, 60};
    Button[6] = {Button[0].picture, 0, 0, "Загрузить", "Load", 200, 60};
    Button[7] = {Button[0].picture, 0, 0, "Меню", "Кровати", 200, 60};
    Button[8] = {Button[0].picture, 0, 0, "Очистить", "Кровати", 200, 60};

    //Расставляем координаты и ширину кнопкам *прекол
    for(int i = 0; i < count_button; i++)
    {
        Button[i].y = 0;
        Button[i].x = 1298 * i / count_button;
        Button[i].width = 1200 / count_button;
    }

    HDC button_0 = txLoadImage("Картинки/Кнопки/Кнопка.bmp");
    HDC Strelka =  txLoadImage("Картинки/Кнопки/Стрелочка.bmp");
    HDC Krestik = txLoadImage("Картинки/Кнопки/Knopochka.bmp");

    /// button Button_MENU массив кнопок стартовой страницы
    button Button_MENU[3];
    Button_MENU[0] = {txLoadImage("Картинки/Меню/Шестерёнка.bmp"), 390, 340, " ", "settings", 457, 122};
    Button_MENU[1] = {txLoadImage("Картинки/Меню/Плей.bmp"), 387, 187, " ", "start", 448, 132};
    Button_MENU[2] = {txLoadImage("Картинки/Меню/Дверь.bmp"), 355, 480, " ", "exit", 468, 140};
    const char* PAGE = "start";

    button Menu = {txLoadImage("Картинки/Меню/Меню.bmp"), 0, 0, ""};
    HDC reklama = txLoadImage("Картинки/Меню/Реклама 1.bmp");

    //Что это? *прекол
    bool mouse1 = false;
    //Это *прекол
    ///bool drawOBL рисовать/не рисовать меню выбора
    bool drawOBL = false;

    ///int Active_Pic активные картинки
    int Active_Pic = -1;

    bool klik = true;///нужна при проверке чтоб не спавнилось бесконечность предметов на экране при клине на правую штуку(выбор)

    ///Заполнение вариантов диванов, другой мебели
    int count_variants = 0;
    Picture variants[777];
    count_variants = Bot_reading("Картинки/Кровати/", variants, count_variants);
    count_variants = Bot_reading("Картинки/Столы/", variants, count_variants);
    count_variants = Bot_reading("Картинки/Диваны/", variants, count_variants);
    count_variants = Bot_reading("Картинки/туалет/", variants, count_variants);


    fillMebelParams(count_variants, variants);// параметры мебели

    fillMebelCoords(variants, count_variants);//координаты мебели

    ///Picture Plans массив планов
    int count_Plans = 3;
    Picture Plans[count_Plans];
    Plans[0] = {"Картинки/Планы/План_1.bmp", false, "Plan"};
    Plans[1] = {"Картинки/Планы/План_2.bmp", false, "Plan"};
    Plans[2] = {"Картинки/Планы/План_3.bmp", false, "Plan"};

    int y_Plans = 150;      //Координаты планов variants
    for (int nomer = 0; nomer < count_Plans; nomer = nomer + 1)
    {
        Plans[nomer].picture = txLoadImage(Plans[nomer].address.c_str());
        Plans[nomer].width = getWidth (Plans[nomer].address.c_str());
        Plans[nomer].height = getHeight(Plans[nomer].address.c_str());

        Plans[nomer].x = 1100;
        if(Plans[nomer].category == "Plan")
        {
            Plans[nomer].y = y_Plans;
            y_Plans = y_Plans + PIC_SIZE * 1.1;
        }
    }

    HDC Plan_ = Plans[0].picture;


    /// Picture Bed2 массив центральных картинок
    Picture Bed2[2500];
    int n_pics = 0;

    string strokaX;   ///string strokaX строка в которой хранится Bed2.x
    string strokaY;   ///string strokaY строка в которой хранится Bed2.y
    string address;   ///string address строка в которой хранится Bed2.address
    string category = "";   ///string category категория

    while(!GetAsyncKeyState(VK_ESCAPE))
    {
        txBegin();
        txClear();

        ///PAGE == "start" Стартовая страница
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
                    Button_MENU[nomer].draw2();
                }
            }

            //Клик на выход
            if (Button_MENU[2].click())
            {
                txDisableAutoPause();
                return 0;
            }

            //Клик на играть
            if (Button_MENU[1].click())
            {
                PAGE = "redactor";
            }
            //Клик на справку
            if (Button_MENU[0].click())
            {
                PAGE = "settings";
            }
        }

        ///PAGE == "settings" Настройки
        else if(PAGE == "settings")
        {
            txSetFillColor(TX_WHITE);
            txRectangle(0, 0, 1300, 750);

            //Кнопка "назад"
            Win32::TransparentBlt(txDC(), 5, 7, 50, 50, Strelka, 0, 0, 225,225, TX_RED);
            txSetColor(TX_BLACK);
            txSelectFont("Comic Sans MS", 50);
            txTextOut(40, 7, " Назад");

            //2 кровати по бокам в справке
            txTransparentBlt(txDC(), 100,  550, 131, 135, variants[0].picture, 0, 0, TX_YELLOW);
            txTransparentBlt(txDC(), 1000, 550, 189, 131, variants[1].picture, 0, 0, TX_YELLOW);
            //Реклама
            txTransparentBlt(txDC(), 500, 375, 300, 200, reklama, 0, 0, TX_YELLOW);

            //Клик на кнопку "назад"
            if (txMouseX() >= 0 && txMouseX() <= 150 &&
                txMouseY() >= 0 && txMouseY() <= 100 &&
                txMouseButtons() & 1)
            {
                PAGE = "start";
                category = "";
            }

            //Текст в справке
            txSetColor(TX_BLACK);
            txSelectFont("Arial", 50);
            txDrawText(200, 20, 1100, 100,
                        "Привет, это симулятор создания квартиры!");
            txSelectFont("Arial", 40);
            txDrawText(270, 100, 1000, 900, "Цель этой игры - весело провести время!\n"
                        "Ты можешь выбирать любой из данных предметов\n"
                        " мебели, перетаскивать их в нужное место,\n"
                        " и построить свою квартиру! Если нужно \n"
                        " удалить предмет, нажми Delete, и потом на предмет.\n");

            if (txMouseButtons() == 2)
                PAGE = "fun";
        }

        ///PAGE == "redactor" Редактор
        else if (PAGE == "redactor")
        {
            //Меню
            txSetFillColour(TX_WHITE);
            if (Button[7].click() &&  activee == true)
            {
                PAGE = "start";
            }

            //Координатная сетка /фон
            txBitBlt(txDC(), 0, 0, 1290, 740, Plan_);


            //Жёлтые кнопки наверху экрана
            for (int nomer = 0; nomer < count_button; nomer = nomer +1)
            {
                    Button[nomer].draw();
            }
            if(drawOBL )
            {
                drawObl(Krestik);
            }
            //Выбор категории
            for(int nomer = 0; nomer < count_button; nomer = nomer + 1)
            {
                if (Button[nomer].click() && activee == true )
                {
                    category = Button[nomer].category;
                    drawOBL = true;

                }
                 //анимация кнопок
                if (txMouseX() >= Button[nomer].x &&
                    txMouseY() >= Button[nomer].y &&
                    txMouseX() <= Button[nomer].x + Button[nomer].width &&
                    txMouseY() <= Button[nomer].y + Button[nomer].height && activee == true)
                {
                    //PAGE = "start";

                    txSetFillColor(TX_TRANSPARENT);
                    txSetColor(RGB(0, 0, 0), 7);
                    Win32::RoundRect(txDC(), Button[nomer].x + 4, Button[nomer].y + 10, Button[nomer].x + 130, Button[nomer].y + 59, 10, 10);
                }
            }
            //Выход из категории
            if(txMouseX() >= 1100   && txMouseY() >= 60  && txMouseX() <= 1140 && txMouseY() <= 100 &&
                txMouseButtons () ==1)
            {
                drawOBL = false;
                category="";
            }
            //клик на план
            for (int nomer = 0; nomer <  count_Plans; nomer = nomer + 1)
            {
                if (txMouseX() >= Plans[nomer].x    &&
                    txMouseY() >= Plans[nomer].y  &&
                    txMouseX() <= Plans[nomer].x +  150 &&
                    txMouseY() <= Plans[nomer].y +  120 &&
                    txMouseButtons () ==1 && category == Plans[nomer].category)
                {
                    Plan_ = Plans[nomer].picture;
                }
            }
            if (Button[8].click() &&  activee == true )//очистка
            {
                n_pics = 0;
            }
            //Выбор мебели и её рисование(рандомное)
            for (int nomer = 0; nomer <  count_variants; nomer = nomer + 1)
            {
                if (txMouseX() >= variants[nomer].x    &&
                    txMouseY() >= variants[nomer].y  &&
                    txMouseX() <= variants[nomer].x + PIC_SIZE &&
                    txMouseY() <= variants[nomer].y + PIC_SIZE &&
                    txMouseButtons () ==1 && category == variants[nomer].category && klik == true)
                {
                     Bed2[n_pics] = {variants[nomer].address,  true, variants[nomer].category, variants[nomer].picture, variants[nomer].picture1, variants[nomer].picture2,
                     random(100, 800), random(100, 600), variants[nomer].width, variants[nomer].height};


                     n_pics++;
                     klik = false;
                }
            }
            ///   вызов функции движения картинки
            Active_Pic = movePic(Bed2, Active_Pic, n_pics);

                ///Переворот/перерисовка картинки
                if (GetAsyncKeyState('R') && Active_Pic >= 0 &&
                    Bed2[Active_Pic].picture == Bed2[Active_Pic].picture1)
                {
                    Bed2[Active_Pic].picture = Bed2[Active_Pic].picture2;
                    txSleep(200);
                }
                else if(GetAsyncKeyState('R') && Active_Pic >= 0 &&
                    Bed2[Active_Pic].picture == Bed2[Active_Pic].picture2)
                {
                    Bed2[Active_Pic].picture = Bed2[Active_Pic].picture1;
                    txSleep(200);
                }

             if (Active_Pic >= 0 && txMouseButtons() == 1 && txMouseY() >= 675  )
             Bed2[Active_Pic].y = Bed2[Active_Pic].y - 150;

             if (Active_Pic >= 0 && txMouseButtons() == 1 && txMouseX() + 50 >= 1283  )
             Bed2[Active_Pic].x = Bed2[Active_Pic].x - 150;


            //Удаление картинки путём смены местами Active_Pic и n_pics
            if(Active_Pic >= 0 && txMouseButtons() == 1 && GetAsyncKeyState(VK_DELETE) && klik == true)
            {

                if (n_pics > 1)
                {

                    Bed2[Active_Pic].height = Bed2[n_pics-1].height;
                    Bed2[Active_Pic].width = Bed2[n_pics-1].width;
                    Bed2[Active_Pic].x = Bed2[n_pics-1].x;
                    Bed2[Active_Pic].y = Bed2[n_pics-1].y;
                    Bed2[Active_Pic].picture = Bed2[n_pics-1].picture;
                }


                n_pics = n_pics - 1;
                Active_Pic = -999;
            }

            if(txMouseButtons () == 0)
                klik = true;


            //Кто ж про это клавишу знает?
            if(GetAsyncKeyState('P'))
            {
                PAGE = "start";
            }


            /// drawAllPlans вызов рисования планов
            drawAllPlans(category, Plans, count_Plans);
            ///drawAllBED2, drawAllVariants Рисование мебели
            drawAllBED2(Bed2, n_pics);
            drawAllVariants(category, variants, count_variants);


            if (Button[5].click() && txMouseButtons() == 1 &&  activee == true)
            {

            system("imageViewer Картинки\Планы\План_1.bmp");
                /*string fileName = RunDialog(true);

                // Покажем диалоговое окно Открыть (Open).
                if (fileName.size() > 0)
                {
                    //Открыть файл
                    ofstream file2(fileName);

                    //Пробежать по всем картинкам
                    for (int i = 0; i < n_pics; i++)
                    {
                        //И сохранить вот это
                        file2 << Bed2[i].x << endl;
                        file2 << Bed2[i].y << endl;
                        file2 << Bed2[i].address << endl;
                    }

                    file2.close();

                    txMessageBox("Успешно сохранено");
                }    */

            }

            if (Button[6].click() && txMouseButtons() == 1 &&  activee == true)
            {
                string fileName = RunDialog(false);
                // Покажем диалоговое окно Открыть (Open)
                if (fileName.size() > 0)
                {
                    n_pics = 0;
                    ifstream file2(fileName);

                    n_pics = readFile(Bed2, strokaX, strokaY, address, n_pics, fileName);

                    txMessageBox("Загрузка Завершена");

                    file2.close();
                }
            }
        }

        else if(PAGE == "fun")
        {
            int x1 = 0;
            int y1 = 0;

            txSetColor(RGB(0, 0, 0) ,6);
            txCircle( x1 + 300,  y1 + 60, 15);

            while (GetAsyncKeyState(VK_UP))
            {
                if (txMouseButtons() & 1)
                    txCircle (txMouseX(), txMouseY(), 1);
                txSleep (20);
            }

            if(txMouseButtons () == 2)
            {
                txLine(303 + x1, 60 + y1, txMouseX() ,txMouseY() );
                txCircle(txMouseX() ,txMouseY(), 15);
                txRectangle( txMouseX(), txMouseY(), 303 + x1, 60 + y1 );
                txSetColor(RGB(0, 0, 0), 5);
                txLine(50, 50, txMouseX(), txMouseY());
                txSleep (10);
            }

            if(GetAsyncKeyState('8'))
                PAGE = "settings";

            ///это пасхалка будет, весело и полезно
        }

        txSleep(20);
        txEnd();
    }


    //Удаление картинок
    txDeleteDC(Strelka);
    txDeleteDC(Krestik);
    txDeleteDC(reklama);
    txDeleteDC(button_0);
    txDeleteDC(Plan_);

    deletePicBed(variants, count_variants, Plans, Bed2, n_pics);
    deletePic(Button, Button_MENU, Menu);

    return 0;
}
