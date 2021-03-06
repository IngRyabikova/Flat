#include "TXLib.h"
#include "Lib/Bed.cpp"
#include "Lib/Button.cpp"
#include "Lib/Files.cpp"
#include <fstream>
#include <iostream>

using namespace std;

///��������� ������� ������ ��������
void drawObl(HDC Krestik)
{
    txSetColor(TX_ORANGE);
    txSetFillColor(TX_WHITE);
    txRectangle(1100, 60, 1300, 750);
    txTransparentBlt(txDC(), 1100, 60, 60, 60, Krestik, 0, 0, TX_WHITE);
}


///������� �������
int main()
{
    txCreateWindow (1300, 750);
    txTextCursor (false);   //������� ������ *������


    ///���������� ������
    int count_button = 9;
    ///������ �������� ���������
    button Button[count_button];
    Button[0] = {txLoadImage("��������/������/������.bmp"), 0, 0, "�����","Plan", 200, 60};
    Button[1] = {Button[0].picture, 0, 0, "�������","�������", 200, 60};
    Button[2] = {Button[0].picture, 0, 0, "�����", "�����", 200, 60};
    Button[3] = {Button[0].picture, 0, 0, "������", "������", 200, 60 };
    Button[4] = {Button[0].picture, 0, 0, "�����", "������", 200, 60};
    Button[5] = {Button[0].picture, 0, 0, "���������", "Save", 200, 60};
    Button[6] = {Button[0].picture, 0, 0, "���������", "Load", 200, 60};
    Button[7] = {Button[0].picture, 0, 0, "����", "�������", 200, 60};
    Button[8] = {Button[0].picture, 0, 0, "��������", "�������", 200, 60};

    //����������� ���������� � ������ ������� *������
    for(int i = 0; i < count_button; i++)
    {
        Button[i].y = 0;
        Button[i].x = 1298 * i / count_button;
        Button[i].width = 1200 / count_button;
    }

    HDC button_0 = txLoadImage("��������/������/������.bmp");
    HDC Strelka =  txLoadImage("��������/������/���������.bmp");
    HDC Krestik = txLoadImage("��������/������/Knopochka.bmp");

    /// button Button_MENU ������ ������ ��������� ��������
    button Button_MENU[3];
    Button_MENU[0] = {txLoadImage("��������/����/���������.bmp"), 390, 340, " ", "settings", 457, 122};
    Button_MENU[1] = {txLoadImage("��������/����/����.bmp"), 387, 187, " ", "start", 448, 132};
    Button_MENU[2] = {txLoadImage("��������/����/�����.bmp"), 355, 480, " ", "exit", 468, 140};
    const char* PAGE = "start";

    button Menu = {txLoadImage("��������/����/����.bmp"), 0, 0, ""};
    HDC reklama = txLoadImage("��������/����/������� 1.bmp");

    //��� ���? *������
    bool mouse1 = false;
    //��� *������
    ///bool drawOBL ��������/�� �������� ���� ������
    bool drawOBL = false;

    ///int Active_Pic �������� ��������
    int Active_Pic = -1;

    bool klik = true;///����� ��� �������� ���� �� ���������� ������������� ��������� �� ������ ��� ����� �� ������ �����(�����)

    ///���������� ��������� �������, ������ ������
    int count_variants = 0;
    Picture variants[777];
    count_variants = Bot_reading("��������/�������/", variants, count_variants);
    count_variants = Bot_reading("��������/�����/", variants, count_variants);
    count_variants = Bot_reading("��������/������/", variants, count_variants);
    count_variants = Bot_reading("��������/������/", variants, count_variants);


    fillMebelParams(count_variants, variants);// ��������� ������

    fillMebelCoords(variants, count_variants);//���������� ������

    ///Picture Plans ������ ������
    int count_Plans = 3;
    Picture Plans[count_Plans];
    Plans[0] = {"��������/�����/����_1.bmp", false, "Plan"};
    Plans[1] = {"��������/�����/����_2.bmp", false, "Plan"};
    Plans[2] = {"��������/�����/����_3.bmp", false, "Plan"};

    int y_Plans = 150;      //���������� ������ variants
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


    /// Picture Bed2 ������ ����������� ��������
    Picture Bed2[2500];
    int n_pics = 0;

    string strokaX;   ///string strokaX ������ � ������� �������� Bed2.x
    string strokaY;   ///string strokaY ������ � ������� �������� Bed2.y
    string address;   ///string address ������ � ������� �������� Bed2.address
    string category = "";   ///string category ���������

    while(!GetAsyncKeyState(VK_ESCAPE))
    {
        txBegin();
        txClear();

        ///PAGE == "start" ��������� ��������
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
                    Button_MENU[nomer].draw2();
                }
            }

            //���� �� �����
            if (Button_MENU[2].click())
            {
                txDisableAutoPause();
                return 0;
            }

            //���� �� ������
            if (Button_MENU[1].click())
            {
                PAGE = "redactor";
            }
            //���� �� �������
            if (Button_MENU[0].click())
            {
                PAGE = "settings";
            }
        }

        ///PAGE == "settings" ���������
        else if(PAGE == "settings")
        {
            txSetFillColor(TX_WHITE);
            txRectangle(0, 0, 1300, 750);

            //������ "�����"
            Win32::TransparentBlt(txDC(), 5, 7, 50, 50, Strelka, 0, 0, 225,225, TX_RED);
            txSetColor(TX_BLACK);
            txSelectFont("Comic Sans MS", 50);
            txTextOut(40, 7, " �����");

            //2 ������� �� ����� � �������
            txTransparentBlt(txDC(), 100,  550, 131, 135, variants[0].picture, 0, 0, TX_YELLOW);
            txTransparentBlt(txDC(), 1000, 550, 189, 131, variants[1].picture, 0, 0, TX_YELLOW);
            //�������
            txTransparentBlt(txDC(), 500, 375, 300, 200, reklama, 0, 0, TX_YELLOW);

            //���� �� ������ "�����"
            if (txMouseX() >= 0 && txMouseX() <= 150 &&
                txMouseY() >= 0 && txMouseY() <= 100 &&
                txMouseButtons() & 1)
            {
                PAGE = "start";
                category = "";
            }

            //����� � �������
            txSetColor(TX_BLACK);
            txSelectFont("Arial", 50);
            txDrawText(200, 20, 1100, 100,
                        "������, ��� ��������� �������� ��������!");
            txSelectFont("Arial", 40);
            txDrawText(270, 100, 1000, 900, "���� ���� ���� - ������ �������� �����!\n"
                        "�� ������ �������� ����� �� ������ ���������\n"
                        " ������, ������������� �� � ������ �����,\n"
                        " � ��������� ���� ��������! ���� ����� \n"
                        " ������� �������, ������� Delete, � ����� �� �������.\n"
                        " ����� ������� �������� ������� Print Screen.\n");
            if (txMouseButtons() == 2)
                PAGE = "fun";
        }

        //��������
        else if (PAGE == "redactor")
        {
            //����
            txSetFillColour(TX_WHITE);
            if (Button[7].click() &&  activee == true)
            {
                PAGE = "start";
            }

            //������������ ����� /���
            txBitBlt(txDC(), 0, 0, 1290, 740, Plan_);


            //Ƹ���� ������ ������� ������
            for (int nomer = 0; nomer < count_button; nomer = nomer +1)
            {
                    Button[nomer].draw();
            }
            if(drawOBL )
            {
                drawObl(Krestik);
            }
            //����� ���������
            for(int nomer = 0; nomer < count_button; nomer = nomer + 1)
            {
                if (Button[nomer].click() && activee == true )
                {
                    category = Button[nomer].category;
                    drawOBL = true;

                }
                 //�������� ������
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
            //����� �� ���������
            if(txMouseX() >= 1100   && txMouseY() >= 60  && txMouseX() <= 1140 && txMouseY() <= 100 &&
                txMouseButtons () ==1)
            {
                drawOBL = false;
                category="";
            }
            //���� �� ����
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
            if (Button[8].click() &&  activee == true )//�������
            {
                n_pics = 0;
            }
            //����� ������ � � ���������(���������)
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
                     //if(GetAsyncKeyState('+'))
                     //{
                     //Bed2[n_pics] = {variants[nomer].address,  true, variants[nomer].category, variants[nomer].picture, variants[nomer].picture1, variants[nomer].picture2,
                     //random(100, 800), random(100, 600), variants[nomer].width * 2, variants[nomer].height * 2};
                     //}


                     n_pics++;
                     klik = false;
                }

            }

            /*int width2  = Bed2[Active_Pic].width;
            int height2 = Bed2[Active_Pic].height;
            if (GetAsyncKeyState('+'))//&& Activer_Pic > 0)
            {
                Bed2[Active_Pic].width  = width2  / 2;
                Bed2[Active_Pic].height = height2 / 2;
            } */

            //   ����� ������� �������� ��������
            Active_Pic = movePic(Bed2, Active_Pic, n_pics);

                //���������/����������� ��������
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


            //�������� �������� ���� ����� ������� Active_Pic � n_pics
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


            //��� � ��� ��� ������� �����?
            if(GetAsyncKeyState('P'))
            {
                PAGE = "start";
            }


            /// drawAllPlans ����� ��������� ������
            drawAllPlans(category, Plans, count_Plans);
            ///drawAllBED2, drawAllVariants ��������� ������
            drawAllBED2(Bed2, n_pics);
            drawAllVariants(category, variants, count_variants);

            if(GetAsyncKeyState(VK_SNAPSHOT))
            {
                ScreenCapture(0, 60, 1300, 680, "screen.bmp");
                txMessageBox("�������� ��������");
                txSleep(200);
            }




            //if (GetAsyncKeyState('-'))
            //{
                //aPictures[nomer].widthPic = aPictures[nomer].widthPic - 15;
                //aPictures[nomer].heightPic = aPictures[nomer].heightPic - 5;
            //}


            if (Button[5].click() && txMouseButtons() == 1 &&  activee == true)
            {

           // system("imageViewer ��������\�����\����_1.bmp");
                string fileName = RunDialog(true);

                // ������� ���������� ���� ������� (Open).
                if (fileName.size() > 0)
                {
                    //������� ����
                    ofstream file2(fileName);

                    //��������� �� ���� ���������
                    for (int i = 0; i < n_pics; i++)
                    {
                        //� ��������� ��� ���
                        file2 << Bed2[i].x << endl;
                        file2 << Bed2[i].y << endl;
                        file2 << Bed2[i].address << endl;
                    }

                    file2.close();

                    txMessageBox("������� ���������");
                }

            }

            if (Button[6].click() && txMouseButtons() == 1 &&  activee == true)
            {
                string fileName = RunDialog(false);
                // ������� ���������� ���� ������� (Open)
                if (fileName.size() > 0)
                {
                    n_pics = 0;
                    ifstream file2(fileName);

                    n_pics = readFile(Bed2, strokaX, strokaY, address, n_pics, fileName);

                    txMessageBox("�������� ���������");

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

            ///��� �������� �����, ������ � �������
        }

        txSleep(20);
        txEnd();
    }


    //�������� ��������
    txDeleteDC(Strelka);
    txDeleteDC(Krestik);
    txDeleteDC(reklama);
    txDeleteDC(button_0);
    txDeleteDC(Plan_);

    deletePicBed(variants, count_variants, Plans, Bed2, n_pics);
    deletePic(Button, Button_MENU, Menu);

    return 0;
}
