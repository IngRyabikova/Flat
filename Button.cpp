
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
};

//Можно сделать это одной функцией

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
    //214 * 66???
    if (txMouseX() >= Button.x && txMouseX() <= Button.x + 214 &&
        txMouseY() >= Button.y && txMouseY() <= Button.y + 66 && txMouseButtons() == 1)
    {
            return true;
    }
}

bool clickButton2(button Button_MENU)
{
    if (txMouseX() >= Button_MENU.x && txMouseX() <= Button_MENU.x + Button_MENU.width &&
        txMouseY() >= Button_MENU.y && txMouseY() <= Button_MENU.y + Button_MENU.height && txMouseButtons() == 1)
    {
            return true;
    }
}

void drawButton2(button Button_MENU)
{
    txTransparentBlt(txDC(), Button_MENU.x, Button_MENU.y, Button_MENU.width, Button_MENU.height, Button_MENU.picture, 0, 0, RGB(255, 127, 39));

    if (Button_MENU.text != "")
    {
        txSelectFont ("Comic Sans MS", 30);
        txSetColor(TX_BLACK);
        txTextOut(Button_MENU.x + 15, Button_MENU.y + 10, Button_MENU.text);
    }
};


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



