#include "TXLib.h"
#include "Bed.cpp"

struct button
{
   // HDC Click;
    HDC picture;
    int x;
    int y;
    const char* text;
    int x_kadr;
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

void drawObl()
{
    txSetColor(TX_ORANGE);
    txSetFillColor(TX_WHITE);
    txRectangle(1100, 60, 1300, 750);
    txSetFillColor(TX_RED);
    txRectangle(1100, 60, 1140, 100);


}

int main()
{
    txCreateWindow (1300, 750);


    HDC Fon = txLoadImage("Êàðòèíêè/Êîîðäèíàòíàÿ ñåòêà.bmp");
    int x_Fon = 0;
    int y_Fon = 0;

    int count_button = 5;
    button Button[count_button];

    Button[0] = {txLoadImage("Êàðòèíêè/Êíîïêà.bmp"), 0, 0, "Êðîâàòè"};
    Button[1] = {txLoadImage("Êàðòèíêè/Êíîïêà.bmp"), 250,0, "Äèâàíû"};
    Button[2] = {txLoadImage("Êàðòèíêè/Êíîïêà.bmp"), 500,0, "Ñòîëû"};
    Button[3] = {txLoadImage("Êàðòèíêè/Êíîïêà.bmp"), 750,0, ""};
    Button[4] = {txLoadImage("Êàðòèíêè/Êíîïêà.bmp"), 1000,0, ""};

    button settings = {txLoadImage("Êàðòèíêè/Ìåíþ/Øåñòåð¸íêà.bmp"), 390, 340, ""};
    button Play = {txLoadImage("Êàðòèíêè/Ìåíþ/Ïëåé.bmp"), 387, 187, ""};
    button Leave = {txLoadImage("Êàðòèíêè/Ìåíþ/Äâåðü.bmp"), 355, 480, ""};
    button Menu_ = {txLoadImage("Êàðòèíêè/Ìåíþ/Ìåíþ.bmp"), 0, 0, ""};
    button Pause = {txLoadImage("Êàðòèíêè/Ìåíþ/Ïàóçà.bmp"), 0, 0,  "", 0};
    //Ýòó äè÷ü òîæå ìîæíî ñäåëàòü êíîïêàìè (íîâûé ìàññèâ èëè íîâûå ïåðåìåííûå)

  int x_Plan = 0;
   int y_Plan = 0;
  HDC Plan = txLoadImage("Êàðòèíêè/Ïëàí_êâàðòèðû.bmp");




    bool Menu = true;

    Picture Bed[8];
    
    bool Menu = true;

    bool drawOBL = false;



    Picture Bed[8];
    //Êàêèå-òî êàðòèíêè íå ñîõðàíèëèñü, ïîýòîìó ÿ èçìåíèë àäðåñà
    Bed[0] = {1100, 150, 131, 135, txLoadImage("Êàðòèíêè/êðîâàòü_1.bmp")};
    Bed[1] = {1100, 350, 189, 131, txLoadImage("Êàðòèíêè/êðîâàòü_2.bmp")};
    Bed[2] = {1100, 550, 192, 212, txLoadImage("Êàðòèíêè/êðîâàòü_3.bmp")};
    Bed[3] = {1100, 750, 164, 199, txLoadImage("Êàðòèíêè/êðîâàòü_4.bmp")};
    bool drawBed = false;

    Bed[4] = {1100, 150, 191, 90, txLoadImage("Êàðòèíêè/Äèâàí_1.bmp")};
    Bed[5] = {1100, 150, 192, 133, txLoadImage("Êàðòèíêè/Äèâàí_1.bmp")};
    Bed[6] = {1100, 300, 202, 92, txLoadImage("Êàðòèíêè/Äèâàí_1.bmp")};
    Bed[7] = {1100, 450, 268, 142, txLoadImage("Êàðòèíêè/Äèâàí_1.bmp")};
    bool drawSofa = false;

    Picture Table[4];
    Table[0] = {1250, 0, 164, 148, txLoadImage("Êàðòèíêè/ñòîë_1.bmp"), false};
    Table[1] = {1250, 200, 131, 130, txLoadImage("Êàðòèíêè/ñòîë_2.bmp"), false};
    Table[2] = {1250, 350, 169, 86, txLoadImage("Êàðòèíêè/ñòîë_3.bmp"), false};
    Table[3] = {1200, 500, 227, 137, txLoadImage("Êàðòèíêè/ñòîë_4.bmp"), false};


    while(!GetAsyncKeyState(VK_ESCAPE))
    {
        txBegin();
        txClear();

        //Ñòàðòîâàÿ ñòðàíèöà
        if (Menu)
        {
            txTransparentBlt (txDC(), Menu_.x, Menu_.y, 1300, 750, Menu_.picture, 0,  0, RGB(255, 127, 39));


            //Íàäïèñü â ìåíþ / íàçâàíèå
            txSelectFont ("Comic Sans MS", 80);
            txSetColor(TX_RED);
            txDrawText(0, 0, txGetExtentX(), txGetExtentY() / 3, "Ñîçäàé ñâîé äèçàéí êâàðòèðû" );


            //Êíîïêè â ìåíþ
            //À ìîã áû áûòü öèêë

            //Êíîïêà èãðàòü
            if (txMouseX() >=430   && txMouseY() >=200  &&  txMouseX() <=816 &&   txMouseY() <=304)
            {
                txTransparentBlt (txDC(), Play.x , Play.y , 448, 132, Play.picture, 0,  0, RGB(255, 127, 39));
            }

            //Êíîïêà íàñòðîéêè
            if (txMouseX() >=430 && txMouseY() >=350  && txMouseX() <=816 && txMouseY() <=450 && Menu == true)
            {
                txTransparentBlt (txDC(), settings.x , settings.y , 457, 122, settings.picture, 0,  0, RGB(255, 127, 39));
            }

            //Êíîïêà âûõîä
            if (txMouseX() >=418 && txMouseY() >=490 && txMouseX() <=816 && txMouseY() <=590 && Menu == true)
            {
                txTransparentBlt (txDC(), Leave.x , Leave.y , 468, 140, Leave.picture, 0,  0, RGB(255, 127, 39));
            }

            //Êëèê íà âûõîä
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
                //txSleep(350);
            }

            if (txMouseX() >=430   && txMouseY() >=350  && txMouseX() <=816 &&  txMouseY() <=450&&
                txMouseButtons () ==1)
            {
                txPlaySound("2.wav", SND_ASYNC);
                //txSleep(350);
            }
        }


        //Ðåäàêòîð
        else
        {
            //Ìåíþ
            txSetFillColour(TX_WHITE);

             txTransparentBlt (txDC(), x_Plan, y_Plan , 1300, 750, Plan, 0,  0, RGB(255, 127, 39));


            //Êîîðäèíàòíàÿ ñåòêà /ôîí
            txTransparentBlt(txDC(), x_Fon, y_Fon, 1300, 750, Fon, 0, 0, TX_YELLOW);




            //Æ¸ëòûå êíîïêè íàâåðõó ýêðàíà
            for(int nomer = 0; nomer < count_button; nomer = nomer +1)
            {
                    drawButton(Button[nomer]);
            }

            if (clickButton(Button[0]))
            {
                drawBed = true;
                drawSofa = false;

            }
            if (clickButton(Button[1]))
            {
                drawSofa = true;
                drawBed = false;

            }

            if(drawOBL)
            {
                drawObl();
            }


            if(txMouseX() >= 1100   && txMouseY() >= 60  && txMouseX() <= 1140 && txMouseY() <= 100 &&
                txMouseButtons () ==1)
            {
                drawOBL = false;
                drawSofa = false;
                drawBed = false;
            }

            if(drawSofa)
                 for (int nomer = 4; nomer < 7; nomer = nomer + 1)
                 {
                    txTransparentBlt (txDC(), Bed[nomer].x,   Bed[nomer].y, Bed[nomer].width, Bed[nomer].height, Bed[nomer].picture);
                    drawOBL = true;
                 }


            else if(drawBed)
                 for (int nomer =0; nomer < 3; nomer = nomer + 1)
                 {
                    txTransparentBlt (txDC(), Bed[nomer].x,   Bed[nomer].y, Bed[nomer].width, Bed[nomer].height, Bed[nomer].picture);
                    drawOBL = true;
                 }


            //Ìåíþ == ëîæü ìîæíî íå ïðîâåðÿòü
            if(GetAsyncKeyState('P') && Menu == false)
            {
                Menu = true;
            }

            //À ïî÷åìó íå ñäåëàòü ïàóçó 2 êàðòèíêàìè êàê ñ íàñòðîéêàìè è ïëååì?
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
                txPlaySound("2.wav", SND_ASYNC);Menu = true ;

            }


       if (    txMouseX()  >= Bed[1].x  - 10    &&
            txMouseX()  <= Bed[1].x  + 200  &&
            txMouseY()  >= Bed[1].y  - 10  &&
            txMouseY()  <= Bed[1].y  + 200 &&
            txMouseButtons () ==1    )
            {
             Bed[1].x  =  txMouseX()-100;
             Bed[1].y =  txMouseY()-100;
             }
              //íà ðàáîòàåò õç ïî÷åìó
            txTransparentBlt (txDC(), Pause.x, Pause.y , 74, 67, Pause.picture, 74 * Pause.x_kadr,  0, RGB(255, 127, 39));

        }










        txSleep(20);
        txEnd();
    }

    txDeleteDC(Fon);
    //Åùå âàãîí êàðòèíîê ìîæíî áû óäàëèòü


    return 0;
}
