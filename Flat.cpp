#include "TXLib.h"




int main()
{
txCreateWindow(1200, 800);
//txSetFillColor(TX_BLUE);


 HDC  Picture  = txLoadImage("Картинки\\123.bmp");  //кактус
 int x_Picture = 0;
 int y_Picture = 0;
  bool Menu = false;



if (Menu)
    {
            //txPlaySound("?.wav", SND_ASYNC);



    }


    else
    {

txTransparentBlt (txDC(), x_Picture, y_Picture, 1200, 800,  Picture, 0, 0, RGB(255, 127, 39));






txSleep(30);
}



    return 0;
}
