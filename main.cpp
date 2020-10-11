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



    HDC Fon = txLoadImage("��������/������������ �����.bmp");
    int x_Fon = 0;
    int y_Fon = 0;

    HDC Krestik = txLoadImage("��������/������/Knopochka.bmp");
    int x_Krestik = 1100;
    int y_Krestik = 60;

    int count_button = 5;
    button Button[count_button];

    Button[0] = {txLoadImage("��������/������/������.bmp"), 0, 0, "�������","Bed", 200, 60};
    Button[1] = {Button[0].picture, 250,0, "������","Sofa", 200, 60};
    Button[2] = {Button[0].picture, 500,0, "�����", "Table", 200, 60};
    Button[3] = {Button[0].picture, 750,0, "", "", 200, 60 };
    Button[4] = {Button[0].picture, 1000,0, "", "", 200, 60};


    HDC Strelka =  txLoadImage("��������/������/���������.bmp");
    int x_Strelka= 0;
    int y_Strelka = 0;

    //���� ��������� ��������
    button Button_MENU[3];
    Button_MENU[0] = {txLoadImage("��������/����/���������.bmp"), 390, 340, "", "settings", 457, 122};
    Button_MENU[1] = {txLoadImage("��������/����/����.bmp"), 387, 187, "", "start", 448, 132};
    Button_MENU[2] = {txLoadImage("��������/����/�����.bmp"), 355, 480, "", "exit", 468, 140};
    const char* PAGE = "start";

    button Menu = {txLoadImage("��������/����/����.bmp"), 0, 0, ""};
    button Pause = {txLoadImage("��������/����/�����.bmp"), 1200, 0,  "", "", 0};

    int x_Plan = 0;
    int y_Plan = 0;
    HDC Plan = txLoadImage("��������/����_��������.bmp");

    int x_Plan2 = 0;
    int y_Plan2 = 0;
    HDC Plan2 = txLoadImage("��������/����_��������2.bmp");

    //� ��� ���� ��� �����?
    bool Menu1 = true;

    bool drawOBL = false;

    bool str_1 = false;

    int Active_Pic = 0;


    bool klik = true;
    Picture variants[25];
    variants[0] = {1100, 150, 131, 135, txLoadImage("��������/�������/�������_1.bmp"), false, "Bed"};
    variants[1] = {1100, 350, 189, 131, txLoadImage("��������/�������/�������_2.bmp"), false, "Bed"};
    variants[2] = {1100, 550, 192, 212, txLoadImage("��������/�������/�������_3.bmp"), false, "Bed"};
    variants[3] = {1100, 750, 164, 199, txLoadImage("��������/�������/�������_4.bmp"), false, "Bed"};
    variants[4] = {1100, 150, 150,  70, txLoadImage("��������/������/�����_1.bmp"), false, "Sofa"};
    variants[5] = {1100, 250, 150, 70, txLoadImage("��������/������/�����_2.bmp"), false, "Sofa"};
    variants[6] = {1100, 350, 150, 70, txLoadImage("��������/������/�����_3.bmp"), false, "Sofa"};
    variants[7] = {1100, 450, 200, 70, txLoadImage("��������/������/Divan2.bmp"), false, "Sofa"};
    variants[8] = {1105, 150, 164, 148, txLoadImage("��������/�����/����_1.bmp"), false, "Table"};
    variants[9] = {1105, 350, 131, 130, txLoadImage("��������/�����/����_2.bmp"), false, "Table"};
    variants[10] = {1105, 550, 169,  86, txLoadImage("��������/�����/����_3.bmp"), false, "Table"};
    variants[11] = {1105, 650, 227, 137, txLoadImage("��������/�����/����_4.bmp"), false, "Table"};


    Picture Bed2[2500];
    int n_pics = 0;

    while(!GetAsyncKeyState(VK_ESCAPE))
    {
        txBegin();
        txClear();

        //��������� ��������
        if (PAGE == "start")
        {
            txTransparentBlt (txDC(), Menu.x, Menu.y, 1300, 750, Menu.picture, 0,  0, RGB(255, 127, 39));

            //������� � ���� / ��������
            txSelectFont ("Comic Sans MS", 80);
            txSetColor(TX_RED);
            txDrawText(0, 0, txGetExtentX(), txGetExtentY() / 3, "������ ���� ������ ��������" );

            //������ � ����
            for(int nomer = 0; nomer < 3; nomer = nomer +1)
            {
                if (txMouseX() >= Button_MENU[nomer].x &&
                    txMouseY() >= Button_MENU[nomer].y &&
                    txMouseX() <= Button_MENU[nomer].x + 500 &&
                    txMouseY() <= Button_MENU[nomer].y + 100)
                {
                   drawButton(Button_MENU[nomer]);
                }

                //����� ��� �� ���������� �������? �������� 3 �������
                if (clickButton(Button_MENU[nomer]))
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

        //���������
        else if(PAGE == "settings")
        {
            txSetFillColor(TX_WHITE);
            txRectangle(0, 0, 1300, 750);

            Win32::TransparentBlt(txDC(), x_Strelka + 5, y_Strelka + 5, 50, 50, Strelka, 0, 0, 225,225, TX_RED);
            //2 ������� �� ����� � �������
            txTransparentBlt(txDC(), 100,  550, 131, 135, variants[0].picture, 0, 0, TX_YELLOW);
            txTransparentBlt(txDC(), 1000, 550, 189, 131, variants[1].picture, 0, 0, TX_YELLOW);

            if (txMouseX() >= 0 && txMouseX() <= 150 &&
                txMouseY() >= 0 && txMouseY() <= 100 &&
                txMouseButtons() & 1)
            {
                PAGE = "start";
                category = "";
            }

            txSetColor(TX_BLACK);
            txSelectFont("Arial", 50);
            txDrawText(200, 100, 1100, 200,
                        "������, ��� ��������� �������� ��������!");
            txSelectFont("Arial", 40);
            txDrawText(270, 200, 1000, 900, "���� ���� ���� - ������ �������� �����!\n"
                        "�� ������ �������� ����� �� ������ ���������\n"
                        " ������, ������������� �� � ������ �����,\n"
                        " � ��������� ���� ��������! ���� ����� \n"
                        " ������� �������, ����� ��� � ����� delete!\n");
        }

        //��������
        else if (PAGE == "redactor")
        {
            //����
            txSetFillColour(TX_WHITE);

            //������������ ����� /���
            txTransparentBlt(txDC(), x_Fon, y_Fon, 1300, 750, Fon, 0, 0, TX_YELLOW);

            //Ƹ���� ������ ������� ������
            for (int nomer = 0; nomer < 3; nomer = nomer +1)
            {
                drawButton(Button[nomer]);
            }

            if(drawOBL)
            {
                drawObl(Krestik);
            }


            //����� ���������
            for(int nomer = 0; nomer < count_button; nomer = nomer + 1)
            {
                if (clickButton(Button[nomer]))
                {
                    category = Button[nomer].category;
                    drawOBL = true;
                }
            }

            //����� �� ���������
            if(txMouseX() >= 1100   && txMouseY() >= 60  && txMouseX() <= 1140 && txMouseY() <= 100 &&
                txMouseButtons () ==1)
            {
                drawOBL = false;
                category="";
            }


            drawAllBED2(Bed2, n_pics);
            drawAllVariants(category, variants);

            for (int nomer = 0; nomer <  12; nomer = nomer + 1)
            {
                if (txMouseX() >= variants[nomer].x    &&
                    txMouseY() >= variants[nomer].y  &&
                    txMouseX() <= variants[nomer].x +  variants[nomer].width &&
                    txMouseY() <= variants[nomer].y +  variants[nomer].height &&
                    txMouseButtons () ==1 && category == variants[nomer].category && klik == true)
                {
                     Bed2[n_pics] = {random(100, 800), random(100, 600),  variants[nomer].width,  variants[nomer].height, variants[nomer].picture, true};
                     n_pics++;
                     klik = false;
                }
            }

            Active_Pic = movePic(Bed2, Active_Pic, n_pics);

            //�������� �������� ���� ����� ������� Active_Pic � n_pics
            if(Active_Pic >= 0 && txMouseButtons() == 1 && GetAsyncKeyState(VK_DELETE) && klik == true)
            {
                Bed2[Active_Pic].x = Bed2[n_pics-1].x;
                Bed2[Active_Pic].y = Bed2[n_pics-1].y;
                Bed2[Active_Pic].picture = Bed2[n_pics-1].picture;

                n_pics = n_pics - 1;
                Active_Pic = -999;
            }


            if(txMouseButtons () == 0)
                klik = true;






            if(GetAsyncKeyState('P'))
            {
                PAGE = "start";
            }

            //� ������ �� ������� ����� 2 ���������� ��� � ����������� � �����?
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




    //�������� ��������
    txDeleteDC(Fon);
    for(int i = 0; i < 11; i = i +1)
        txDeleteDC(variants[i].picture);


    deletePic(Button, Button_MENU, Menu, Pause);


 //   for(int i = 0; i < 10; i = i +1)
 //       txDeleteDC(Button[i].picture);

    //����� ���
    Win32::TransparentBlt (txDC(),196,140,200,100,Plan,0,0,800,1100, TX_WHITE);

    Win32::TransparentBlt (txDC(),196,140,200,100,Plan2,0,0,1300,730, TX_WHITE);

    return 0;
}
