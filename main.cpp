#include "TXLib.h"
#include "Bed.cpp"

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


    HDC Fon = txLoadImage("��������/������������ �����.bmp");
    int x_Fon = 0;
    int y_Fon = 0;

    HDC Krestik = txLoadImage("��������/Knopochka.bmp");
    int x_Krestik = 1100;
    int y_Krestik = 60;

    int count_button = 5;
    button Button[count_button];

    Button[0] = {txLoadImage("��������/������.bmp"), 0, 0, "�������"};
    Button[1] = {txLoadImage("��������/������.bmp"), 250,0, "������"};
    Button[2] = {txLoadImage("��������/������.bmp"), 500,0, "�����"};
    Button[3] = {txLoadImage("��������/������.bmp"), 750,0, ""};
    Button[4] = {txLoadImage("��������/������.bmp"), 1000,0, ""};

    //��� ���� ���� ����� ������� �������� (����� ������ ��� ����� ����������)
    //
    //Button[5]
    button settings = {txLoadImage("��������/����/���������.bmp"), 390, 340, ""};
    button Play = {txLoadImage("��������/����/����.bmp"), 387, 187, ""};
    button Leave = {txLoadImage("��������/����/�����.bmp"), 355, 480, ""};
    button Menu_ = {txLoadImage("��������/����/����.bmp"), 0, 0, ""};
    button Pause = {txLoadImage("��������/����/�����.bmp"), 1200, 0,  "", 0};

    /*
settings
Play
Leave
Menu
     */



    int x_Plan = 0;
    int y_Plan = 0;

    HDC Plan = txLoadImage("��������/����_��������.bmp");

    int x_Plan2 = 0;
    int y_Plan2 = 0;

    HDC Plan2 = txLoadImage("��������/����_��������2.bmp");

    bool Menu = true;

    bool drawOBL = false;

    bool str_1 = false;




    Picture Bed[25];
    //�����-�� �������� �� �����������, ������� � ������� ������
    Bed[0] = {1100, 150, 131, 135, txLoadImage("��������/�������_1.bmp"), false, "Bed"};
    Bed[1] = {1100, 350, 189, 131, txLoadImage("��������/�������_2.bmp"), false, "Bed"};
    Bed[2] = {1100, 550, 192, 212, txLoadImage("��������/�������_3.bmp"), false, "Bed"};
    Bed[3] = {1100, 750, 164, 199, txLoadImage("��������/�������_4.bmp"), false, "Bed"};
    Bed[4] = {1100, 150, 150,  70, txLoadImage("��������/�����_1.bmp"), false, "Sofa"};
    Bed[5] = {1100, 250, 150, 70, txLoadImage("��������/�����_2.bmp"), false, "Sofa"};
    Bed[6] = {1100, 350, 150, 70, txLoadImage("��������/�����_3.bmp"), false, "Sofa"};
    Bed[7] = {1100, 450, 268, 142, txLoadImage("��������/������/divan4.bmp"), false, "Sofa"};
    Bed[8] = {1105, 150, 164, 148, txLoadImage("��������/����_1.bmp"), false, "Table"};
    Bed[9] = {1105, 350, 131, 130, txLoadImage("��������/����_2.bmp"), false, "Table"};
    Bed[10] = {1105, 550, 169,  86, txLoadImage("��������/����_3.bmp"), false, "Table"};
    Bed[11] = {1105, 650, 227, 137, txLoadImage("��������/����_4.bmp"), false, "Table"};
    //bool drawTables = false;




    while(!GetAsyncKeyState(VK_ESCAPE))
    {
        txBegin();
        txClear();

        //��������� ��������
        if (Menu)
        {
            txTransparentBlt (txDC(), Menu_.x, Menu_.y, 1300, 750, Menu_.picture, 0,  0, RGB(255, 127, 39));

            //������� � ���� / ��������
            txSelectFont ("Comic Sans MS", 80);
            txSetColor(TX_RED);
            txDrawText(0, 0, txGetExtentX(), txGetExtentY() / 3, "������ ���� ������ ��������" );

            //������ � ����
            //� ��� �� ���� ����

            //������ ������
            if (txMouseX() >=430   && txMouseY() >=200  &&  txMouseX() <=816 &&   txMouseY() <=304)
            {
                txTransparentBlt (txDC(), Play.x , Play.y , 448, 132, Play.picture, 0,  0, RGB(255, 127, 39));
            }

            //������ ���������
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


                txTextOut(100, 100, "������ :)");



            }

            //������ �����
            if (txMouseX() >=418 && txMouseY() >=490 && txMouseX() <=816 && txMouseY() <=590 && Menu == true)
            {
                txTransparentBlt (txDC(), Leave.x , Leave.y , 468, 140, Leave.picture, 0,  0, RGB(255, 127, 39));
            }

            //���� �� �����
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

        //��������
        else
        {
            //����
            txSetFillColour(TX_WHITE);


            //������������ ����� /���
            txTransparentBlt(txDC(), x_Fon, y_Fon, 1300, 750, Fon, 0, 0, TX_YELLOW);




            //Ƹ���� ������ ������� ������
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
                 if (category == Bed[nomer].category)
                 {
                    txTransparentBlt (txDC(), Bed[nomer].x,   Bed[nomer].y, Bed[nomer].width, Bed[nomer].height, Bed[nomer].picture);
                 }
            }






            if(GetAsyncKeyState('P'))
            {
                Menu = true;
            }

            //� ������ �� ������� ����� 2 ���������� ��� � ����������� � �����?
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


/*
           for(int nomer = 0; nomer < 4; nomer = nomer + 1)
           {
                if (txMouseX()  >= Bed[nomer].x  - 10    && txMouseX()  <= Bed[nomer].x  + 200  &&
                    txMouseY()  >= Bed[nomer].y  - 10  && txMouseY()  <= Bed[nomer].y  + 200 &&
                    txMouseButtons () ==1    )
                {
                    Bed[nomer].x  =  txMouseX()-100;
                    Bed[nomer].y =  txMouseY()-100;
                }

            }

            /*for(int nomer = 4; nomer < 7; nomer = nomer + 1)
            {
                if (txMouseX()  >= Bed[nomer].x  - 10    && txMouseX()  <= Bed[nomer].x  + 200  &&
                    txMouseY()  >= Bed[nomer].y  - 10  && txMouseY()  <= Bed[nomer].y  + 200 &&
                    txMouseButtons () ==1    )
                {
                    Bed[nomer].x  =  txMouseX()-100;
                    Bed[nomer].y =  txMouseY()-100;
                }

            }
            for(int nomer = 0; nomer < 4; nomer = nomer + 1)
            {
                if (txMouseX()  >= Table[nomer].x  - 10    && txMouseX()  <= Table[nomer].x  + 200  &&
                    txMouseY()  >= Table[nomer].y  - 10  && txMouseY()  <= Table[nomer].y  + 200 &&
                    txMouseButtons () ==1    )
                {
                    Table[nomer].x  =  txMouseX()-100;
                    Table[nomer].y =  txMouseY()-100;
                }

            }     */







            txTransparentBlt (txDC(), Pause.x, Pause.y , 74, 67, Pause.picture, 74 * Pause.x_kadr,  0, RGB(255, 127, 39));
        }

        txSleep(20);
        txEnd();
    }




    txDeleteDC(Fon);
    //��� ����� �������� ����� �� �������
    for(int i = 0; i < 11; i = i +1)
        txDeleteDC(Bed[i].picture);

    for(int i = 0; i < 10; i = i +1)
        txDeleteDC(Button[i].picture);

    Win32::TransparentBlt (txDC(),196,140,200,100,Plan,0,0,800,1100, TX_WHITE);

    Win32::TransparentBlt (txDC(),196,140,200,100,Plan2,0,0,1300,730, TX_WHITE);

    return 0;
}
