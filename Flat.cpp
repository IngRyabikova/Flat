#include "TXLib.h"




int main()
{
txCreateWindow(1200, 800);
//txSetFillColor(TX_BLUE);


 HDC  ??? = txLoadImage("Картинки/???.bmp");  //кактус
 int x_??? = 300;
 int y_??? = 407;

while (!GetAsyncKeyState(VK_ESCAPE))
{
txBegin();
txClear();


if (Menu)
    {
            txPlaySound("???.wav", SND_ASYNC);



    }


    else
    {

txTransparentBlt (txDC(), x_???, y_???, 1248, 608, ???, 0, 0, RGB(255, 127, 39));






txSleep(30);
}


txSleep(30);
txEnd();

}

    return 0;
}
