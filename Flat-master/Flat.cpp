#include "TXLib.h"


int main()
{
    txCreateWindow(1200, 800);
    txSetFillColor(TX_YELLOW);
    txSetColor(TX_BLUE);


    HDC  Picture  = txLoadImage("Картинки\\Фон.bmp");
    int x_Picture = 0;
    int y_Picture = 0;
    bool Menu = false;

    while (true)
    {
        txTransparentBlt (txDC(), x_Picture, y_Picture, 1200, 800,  Picture, 0, 0, RGB(255, 127, 39));
        Win32::RoundRect (txDC(), 400, 100, 800, 250, 30, 30);

        txDrawText (400, 150, 800, 200, "кнопка");
        if (txMouseX() >= 400 && txMouseX() <= 800 &&
            txMouseY() >= 150 && txMouseY() <= 200 && txMouseButtons() == 1)
        {
            txTextOut(100, 100, "Это работает!");
        }




        txSleep(30);
    }

    return 0;
}
