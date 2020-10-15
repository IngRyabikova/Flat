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

    //Рисование кнопки
    void draw()
    {
        if (text != "")
        {
            txTransparentBlt(txDC(), x, y, width, height, picture, 0, 0, TX_BLACK);

            txSelectFont ("Comic Sans MS", 30);
            txSetColor(TX_BLACK);
            txTextOut(x + 15, y + 10, text);
        }
    };

    //Клик на кнопки
    bool click()
    {
        if (txMouseX() >= x && txMouseX() <= x + width &&
            txMouseY() >= y && txMouseY() <= y + height && txMouseButtons() == 1)
        {
            return true;
        }
    }
};


/*
void drawButton(button Button1)
{
    if (Button1.text != "")
    {
        txTransparentBlt(txDC(), Button1.x, Button1.y, Button1.width, Button1.height, Button1.picture, 0, 0, TX_BLACK);

        txSelectFont ("Comic Sans MS", 30);
        txSetColor(TX_BLACK);
        txTextOut(Button1.x + 15, Button1.y + 10, Button1.text);
    }

    //RGB(255, 127, 39)
};


bool clickButton(button Button_MENU)
{
    if (txMouseX() >= Button_MENU.x && txMouseX() <= Button_MENU.x + Button_MENU.width &&
        txMouseY() >= Button_MENU.y && txMouseY() <= Button_MENU.y + Button_MENU.height && txMouseButtons() == 1)
    {
            return true;
    }
}

*/

//Удаление всех кнопок
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
