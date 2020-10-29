#include "TXLib.h"

struct button
{
    HDC picture;
    int x;
    int y;
    const char* text;
    string category;
    int width;
    int height;
    int x_kadr;

    //��������� ������
    void draw()
    {
        if (text != "")
        {
            //txTransparentBlt(txDC(), x, y, width, height, picture, 0, 0, TX_BLACK);
            Win32::TransparentBlt(txDC(), x, y, width, height, picture, 0, 0, 200,60, TX_BLACK);

            txSelectFont ("Comic Sans MS", 30);
            txSetColor(TX_BLACK);
            txTextOut(x + 15, y + 10, text);
        }
    };
    void draw2()
    {
        if (text != "")
        {
            txTransparentBlt(txDC(), x, y, width, height, picture, 0, 0, TX_BLACK);
            //Win32::TransparentBlt(txDC(), x, y, width, height, picture, 0, 0, 200,60, TX_BLACK);

            txSelectFont ("Comic Sans MS", 30);
            txSetColor(TX_BLACK);
            txTextOut(x + 15, y + 10, text);
        }
    };






    //���� �� ������
    bool click()
    {
        if (txMouseX() >= x && txMouseX() <= x + width &&
            txMouseY() >= y && txMouseY() <= y + height && txMouseButtons() == 1)
        {
            return true;
        }
    }
};


//�������� ���� ������
void deletePic(button* Button,  button* Button_MENU, button Menu, button Pause)
{
    for(int i = 0; i < 10; i = i +1)
    {
        txDeleteDC(Button[i].picture);
        txDeleteDC(Button_MENU[i].picture);
    }
    txDeleteDC(Menu.picture);
    txDeleteDC(Pause.picture);
}
