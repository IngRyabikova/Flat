///\file Button.cpp
#include "TXLib.h"

///Структура "кнопка"
struct button
{
    ///Сама картинка
    HDC picture;
    int x;
    int y;
    ///текст внутри кнопки
    const char* text;
    string category;
    int width;
    int height;

    ///функция рисования кнопки (для файлов размером 200*60)
    void draw()
    {
        if (text != "")
        {
            Win32::TransparentBlt(txDC(), x, y, width, height, picture, 0, 0, 200,60, TX_BLACK);

            txSelectFont ("Comic Sans MS", 30);
            txSetColor(TX_BLACK);
            txTextOut(x + 15, y + 10, text);
        }
    };
    ///функция рисования кнопки
    void draw2()
    {
        if (text != "")
        {
            txTransparentBlt(txDC(), x, y, width, height, picture, 0, 0, TX_BLACK);
            txSelectFont ("Comic Sans MS", 30);
            txSetColor(TX_BLACK);
            txTextOut(x + 15, y + 10, text);
        }
    };

    ///Клик на кнопку
    bool click()
    {
        if (txMouseX() >= x && txMouseX() <= x + width &&
            txMouseY() >= y && txMouseY() <= y + height && txMouseButtons() == 1 &&  activee == true)
        {
            return true;
        }
    }
};

///Удаление картинок всех кнопок чтоб не спамило ыыы -__- у вас не освобождено 79 картинок -__-   ыыы
void deletePic(button* Button,  button* Button_MENU, button Menu)
{
    for(int i = 0; i < 10; i = i +1)
    {
        txDeleteDC(Button[i].picture);
        txDeleteDC(Button_MENU[i].picture);
    }
    txDeleteDC(Menu.picture);
}
