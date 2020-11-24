#include "TXLib.h"
#include "Bed.cpp"
#include "Button.cpp"
#include <fstream>
#include <iostream>


using namespace std;

int getWidth(const char* address)
{
    char header[54];
    ifstream bmp;
    bmp.open(address, ios::in | ios::binary);

    bmp.read(header, 54);
    int width = *(int *)&header[18];
    return width;
}
int getHeight(const char* address)
{
    char header[54];
    ifstream bmp;
    bmp.open(address, ios::in | ios::binary);

    bmp.read(header, 54);
    int width = *(int *)&header[22];
    return width;
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

int Bot_reading(const char* address, Picture*variants, int N)
{
    setlocale(LC_ALL, "Russian");
    WIN32_FIND_DATA FindFileData;
    HANDLE hf;
    string str = address;
    str = str + "*";

    hf=FindFirstFile(str.c_str(), &FindFileData);

    //
    if (hf!=INVALID_HANDLE_VALUE){
        do{

            str = FindFileData.cFileName;
            str = (string)address + str;

            if (str.find(".bmp") != -1)
            {
                string s = str;
                variants[N] = {s.c_str()};
                N = N + 1;
                txSleep(20);
            }
        }
        while (FindNextFile(hf,&FindFileData)!=0);
        FindClose(hf);
    }

    return N;
}


int main()
{
    txCreateWindow (1300, 750);
    txTextCursor (false);   //������� ������
    // POINT size = txGetConsoleFontSize();
  //txSetConsoleCursorPos ( * size.x, 0 * size.y);


    string category = "";

    HDC Fon = txLoadImage("��������/������������ �����.bmp");
    int x_Fon = 0;
    int y_Fon = 0;

    HDC Krestik = txLoadImage("��������/������/Knopochka.bmp");
    int x_Krestik = 1100;
    int y_Krestik = 60;

    int count_button = 9;
    button Button[count_button];
    //����� 2 ������, �� � ��� ������ ������  #� ��� ����? ##���� ����� ������ ��������
    Button[0] = {txLoadImage("��������/������/������.bmp"), 0, 0, "�����","Plan", 200, 60};
    Button[1] = {Button[0].picture, 0, 0, "�������","�������", 200, 60};
    Button[2] = {Button[0].picture, 0, 0, "�����", "�����", 200, 60};
    Button[3] = {Button[0].picture, 0, 0, "������", "������", 200, 60 };
    Button[4] = {Button[0].picture, 0, 0, "�����", "������", 200, 60};
    Button[5] = {Button[0].picture, 0, 0, "���������", "Save", 200, 60};
    Button[6] = {Button[0].picture, 0, 0, "���������", "Load", 200, 60};
    Button[7] = {Button[0].picture, 0, 0, "����", "�������", 200, 60};
    Button[8] = {Button[0].picture, 0, 0, "��������", "�������", 200, 60};




    //����������� ���������� � ������ �������
    for(int i = 0; i < count_button; i++)
    {
        Button[i].y = 0;
        Button[i].x = 1298 * i / count_button;
        Button[i].width = 1200 / count_button;
    }

    //���������� ������ ������ ������ �� PAGE = "redactor"
    /*for(int i = 0; i < count_button; i = i + 1)
    {
        Button[i].y = 0;
        Button[i].x = i * 250;
        ������, ������
    } */

    HDC button_0 = txLoadImage("��������/������/������.bmp");
    int x_button_0 = 0;
    int y_button_0 = 0;

    HDC Strelka =  txLoadImage("��������/������/���������.bmp");
    int x_Strelka= 0;
    int y_Strelka = 0;



    //���� ��������� ��������
    button Button_MENU[3];
    Button_MENU[0] = {txLoadImage("��������/����/���������.bmp"), 390, 340, " ", "settings", 457, 122};
    Button_MENU[1] = {txLoadImage("��������/����/����.bmp"), 387, 187, " ", "start", 448, 132};
    Button_MENU[2] = {txLoadImage("��������/����/�����.bmp"), 355, 480, " ", "exit", 468, 140};
    const char* PAGE = "start";

    if (category == "redactor")
        PAGE = "start";

    button Menu = {txLoadImage("��������/����/����.bmp"), 0, 0, ""};
    //button Pause = {txLoadImage("��������/����/�����.bmp"), 1200, 0,  "", "", 0};

    HDC reklama = txLoadImage("��������/����/������� 1.bmp");
    int x_reklama = 0;
    int y_reklama = 0;

    //Cursor =- 1;


    bool mouse1 = false;

    //��� ��
    bool drawOBL = false;
    int Active_Pic = -1;
    bool klik = true;

    int count_variants = 0;
    Picture variants[777];

    count_variants = Bot_reading("��������/�������/", variants, count_variants);
    count_variants = Bot_reading("��������/�����/", variants, count_variants);
    count_variants = Bot_reading("��������/������/", variants, count_variants);
    count_variants = Bot_reading("��������/������/", variants, count_variants);


    for (int nomer = 0; nomer < count_variants; nomer = nomer + 1)
    {
        string s = variants[nomer].address;
        int pos = s.find("/", 0);
        int pos2 = s.find("/",pos + 1);
        variants[nomer].category = s.substr(pos + 1,pos2 - pos - 1);  //�� ������� / �� �������

        variants[nomer].visible = false;

        variants[nomer].picture1 = txLoadImage(variants[nomer].address.c_str());




                 //   string address = variants[Active_Pic].address;
        category = variants[nomer].category;

        int pos1 = s.find(category) ;
        s = s.replace(pos1, category.size(),category + "1");

        variants[nomer].picture2 = txLoadImage(s.c_str());


        //variants[nomer].picture2 = txLoadImage(("1" + (string)variants[nomer].address).c_str());
        variants[nomer].picture = variants[nomer].picture1;

        //������ � ������ �� ������� �����
        variants[nomer].width = getWidth (variants[nomer].address.c_str());
        variants[nomer].x = 1100 + ((150 - variants[nomer].width) / 2);
        variants[nomer].height = getHeight(variants[nomer].address.c_str());
    }


    int y_Bed = 150;        //���������� �������� variants
    int y_Sofa = 150;       //���������� ������� variants
    int y_Table = 150;      //���������� ������ variants
    int y_Kuhna = 150;      //���������� Kuhna variants
    for (int i = 0; i < count_variants; i = i + 1)
    {
        if (variants[i].category == "�������")
        {
            variants[i].y = y_Bed;
            y_Bed = y_Bed + 150;
        }
        if (variants[i].category == "������")
        {
            variants[i].y = y_Sofa;
            y_Sofa = y_Sofa + 100;
        }

        if(variants[i].category == "�����")
        {
            variants[i].y = y_Table;
            y_Table = y_Table + 150;
        }
        if(variants[i].category == "������")
        {
            variants[i].y = y_Kuhna;
            y_Kuhna = y_Kuhna + 100;
        }
    }


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
            y_Plans = y_Plans + 200;
        }
    }

    HDC Plan_ = Plans[0].picture;
    int x_Plan_ = 0;
    int y_Plan_ = 0;

    //�����. ��������
    Picture Bed2[2500];
    int n_pics = 0;

   //int n_pics2 = 0;
    string strokaX;
    string strokaY;
    string address;



    while(!GetAsyncKeyState(VK_ESCAPE))
    {
        txBegin();
        txClear();

        //��������� ��������)
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

        //���������
        else if(PAGE == "settings")
        {
            txSetFillColor(TX_WHITE);
            txRectangle(0, 0, 1300, 750);

            //������ "�����"
            Win32::TransparentBlt(txDC(), x_Strelka + 5, y_Strelka + 5, 50, 50, Strelka, 0, 0, 225,225, TX_RED);
            txSetColor(TX_BLACK);
            txSelectFont("Comic Sans MS", 50);
            txTextOut(40, 7, "�����");

            //2 ������� �� ����� � �������
            txTransparentBlt(txDC(), 100,  550, 131, 135, variants[0].picture, 0, 0, TX_YELLOW);
            txTransparentBlt(txDC(), 1000, 550, 189, 131, variants[1].picture, 0, 0, TX_YELLOW);
            //�������
            txTransparentBlt(txDC(), 500, 450, 300, 200, reklama, 0, 0, TX_YELLOW);

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
            txDrawText(200, 100, 1100, 200,
                        "������, ��� ��������� �������� ��������!");
            txSelectFont("Arial", 40);
            txDrawText(270, 200, 1000, 900, "���� ���� ���� - ������ �������� �����!\n"
                        "�� ������ �������� ����� �� ������ ���������\n"
                        " ������, ������������� �� � ������ �����,\n"
                        " � ��������� ���� ��������! ���� ����� \n"
                        " ������� �������, ����� ��� � ����� Delete!\n");
        }

        //��������)
        else if (PAGE == "redactor")
        {

            //����
            txSetFillColour(TX_WHITE);
            if (Button[7].click() &&  activee == true)
            {
                PAGE = "start";
            }

            //������������ ����� /���
            txBitBlt(txDC(), x_Plan_, y_Plan_, 1290, 740, Plan_);

            for (int nomer = 0; nomer < count_button; nomer = nomer +1)
            {
                //� ��� ���� ���������� ����� ������ �� �����?
                txTransparentBlt(txDC(), x_button_0,  y_button_0, 214, 66, button_0, 0, 0, TX_YELLOW);
                x_button_0 = x_button_0 + 250;
            }

            //Ƹ���� ������ ������� ������
            for (int nomer = 0; nomer < count_button; nomer = nomer +1)
            {

                {
                    Button[nomer].draw();
                }
            }

            if(drawOBL )
            {
                drawObl(Krestik);
            }



            //����� ���������
            for(int nomer = 0; nomer < count_button; nomer = nomer + 1)
            {
                if (Button[nomer].click() && mouse1 == false && activee == true )
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
                    txMouseX() <= variants[nomer].x +  variants[nomer].width &&
                    txMouseY() <= variants[nomer].y +  variants[nomer].height &&
                    txMouseButtons () ==1 && category == variants[nomer].category && klik == true)
                {
                     Bed2[n_pics] = {variants[nomer].address,  true, variants[nomer].category, variants[nomer].picture, variants[nomer].picture1, variants[nomer].picture2,
                     random(100, 800), random(100, 600), variants[nomer].width, variants[nomer].height};

                     n_pics++;
                     klik = false;
                }
                     //������� ������������ ���������
                /*if (Bed2[Active_Pic].x == Bed2[n_pics].x + 150 &&
                    //Bed2[Active_Pic].x == Bed2[n_pics].x + 50 &&
                    //Bed2[Active_Pic].y == Bed2[n_pics].y - 50 &&
                    Bed2[Active_Pic].y == Bed2[n_pics].y + 150 )
                    Bed2[Active_Pic].y = Bed2[Active_Pic].y + 50;   */
             }

            //�������� ��������
            Active_Pic = movePic(Bed2, Active_Pic, n_pics);




            //���������/����������� ��������
                if(GetAsyncKeyState('R') && Active_Pic >= 0)
                {

                   /* string address = variants[Active_Pic].address;
                    category = variants[Active_Pic].category;



                    int pos1 = address.find(category) ;
                    address = address.replace(pos1, category.size(),category + "1");
                    cout << address << endl;

                    txSleep(2000);  */

       // variants[Active_Pic].picture2 = txLoadImage(("1" + (string)variants[Active_Pic].address).c_str());




                Bed2[Active_Pic].picture = Bed2[Active_Pic].picture2;

                }

             if (Active_Pic >= 0 && txMouseButtons() == 1 && txMouseY() >= 675  )
             Bed2[Active_Pic].y = Bed2[Active_Pic].y - 150;

             if (Active_Pic >= 0 && txMouseButtons() == 1 && txMouseX() + 50 >= 1283  )
             Bed2[Active_Pic].x = Bed2[Active_Pic].x - 150;


            //�������� �������� ���� ����� ������� Active_Pic � n_pics
            if(Active_Pic >= 0 && txMouseButtons() == 1 && GetAsyncKeyState(VK_DELETE) && klik == true)
            {
               /* char str[100];
                sprintf(str, "%d", Active_Pic);
                txMessageBox(str);*/

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

            //���� ��������� �� ������ ���� � �����
            /*for (int nomer = 0; nomer <  9; nomer = nomer + 1)
            nomer =

            if(txGetPixel(Bed2[Active_Pic].x, Bed2[Active_Pic].y) == TX_BLACK)
            {
                Bed2[Active_Pic].x = Bed2[Active_Pic].x + 200;
            }*/



            if(GetAsyncKeyState('P'))
            {
                PAGE = "start";
            }

            //� ������ �� ������� ����� 2 ���������� ��� � ����������� � �����?
            /*if (txMouseX() >= 1210   && txMouseY() >=10  && txMouseX() <=1290 && txMouseY() <=50)
            {
                Pause.x_kadr = 1;
            }
            else
            {
                Pause.x_kadr = 0;
            }
              */
            /*if (txMouseX() >=1220   && txMouseY() >= 1  && txMouseX() <=1300 && txMouseY() <=77&&
                txMouseButtons () ==1Plans)
            {
                txPlaySound("2.wav", SND_ASYNC);
                PAGE = "start";Plans
            } */



            //���������); ������ ��������
            drawAllPlans(category, Plans, count_Plans);
            //��������� ������
            drawAllBED2(Bed2, n_pics);
            drawAllVariants(category, variants, count_variants);

          //  txTransparentBlt (txDC(), Pause.x + 5, Pause.y , 80, 45, Pause.picture, 80 * Pause.x_kadr,  0, RGB(255, 127, 39));



            if (Button[5].click() && txMouseButtons() == 1 &&  activee == true)
            {
                //������� ����
                ofstream file2("��������.txt");

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

            if (Button[6].click() && txMouseButtons() == 1 &&  activee == true)
            {

    OPENFILENAME ofn;			// ��������� ������������ ����������� ����
    char szFile[260];			// ����� ��� ����� �����
    HWND hwnd;              		// ���� ���������
    HANDLE hf;              		// ���������� �����

    // ������������� OPENFILENAME
    ZeroMemory(&ofn, sizeof(OPENFILENAME));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = txWindow();
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = "All\0*.*\0Text\0*.TXT\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    // ������� ���������� ���� ������� (Open).

    if (GetSaveFileName(&ofn) == TRUE)
     {

        string fileName = ofn.lpstrFile;
        ofstream file2(fileName);
        for (int i = 0; i < n_pics; i++)
        {

            file2 << Bed2[i].x << endl;
            file2 << Bed2[i].y << endl;
            file2 << Bed2[i].address << endl;
        }

        file2.close();
     }


              /*  //�������� ������ ������
                while (file.good())
                {
                    //������1 (x)
                    getline(file, strokaX);
                    Bed2[n_pics].x = atoi(strokaX.c_str());

                    //������2 (y)
                    getline(file, strokaY);
                    Bed2[n_pics].y = atoi(strokaY.c_str());

                    //������3 (�����)
                    getline(file, address);
                    Bed2[n_pics].address = address.c_str();



                    Bed2[n_pics].visible = true;

                    Bed2[n_pics].picture = txLoadImage(Bed2[n_pics].address.c_str());
                    //������ � ������ �� ������� �����
                    Bed2[n_pics].width = getWidth (Bed2[n_pics].address.c_str());
                    Bed2[n_pics].height = getHeight(Bed2[n_pics].address.c_str());

                    n_pics = n_pics + 1;
                }

                txMessageBox("��������...");*/
            }
        }

        txSleep(20);
        txEnd();
    }





    //�������� ��������
    txDeleteDC(Fon);
    txDeleteDC(Strelka);
    txDeleteDC(Krestik);
    txDeleteDC(reklama);
    txDeleteDC(button_0);
    txDeleteDC(Plan_);
    //txDeleteDC(Button);
    //txDeleteDC(Plans);

    deletePicBed(variants, count_variants, Plans);
    //deletePic(Button, Button_MENU, Menu);

    return 0;
}
