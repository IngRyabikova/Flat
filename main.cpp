
#include "TXLib.h"

struct button
{
    HDC picture;
    int x;
    int y;
};

void drawButton(button Button1)
{
    txTransparentBlt(txDC(), Button1.x, Button1.y, 200, 60, Button1.picture, 0, 0, TX_WHITE);
    //txSetColor(TX_BLACK);
    //txTextOut(Button1.x, Button1.y, "1");

};

int main()
    {
         txCreateWindow (1300, 750);


        HDC Fon = txLoadImage("��������/������������ �����.bmp");
        int x_Fon = 0;
        int y_Fon = 0;

        int count_button = 5;
        button Button[count_button];

        Button[0] = {txLoadImage("��������/������.bmp"), 0,0};
        Button[1] = {txLoadImage("��������/������.bmp"), 250,0};
        Button[2] = {txLoadImage("��������/������.bmp"), 500,0};
        Button[3] = {txLoadImage("��������/������.bmp"), 750,0};
        Button[4] = {txLoadImage("��������/������.bmp"), 1000,0};



       /* HDC Button = txLoadImage("��������/������.bmp");
        int x_Button = 0;
        int y_Button = 0;
                          */


        while(!GetAsyncKeyState(VK_ESCAPE))
        {
            txBegin();
            txClear();

            txTransparentBlt(txDC(), x_Fon, y_Fon, 1300, 750, Fon, 0, 0, TX_YELLOW);

            for(int nomer = 0; nomer < count_button; nomer = nomer +1)
            {
                drawButton(Button[nomer]);
            }
            txSetColor(TX_BLACK);
            txTextOut(30, 30, "������ 1");




            txEnd();
        }

         txDeleteDC(Fon);


    return 0;
    }

