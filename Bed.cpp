#include "TXLib.h"

struct Picture
{
    string address;
    bool visible;
    string category;
    HDC picture;
    HDC picture1;
    HDC picture2;
    int x;
    int y;
    int width;
    int height;

    //���������
    void draw()
    {

//variants[i].x, variants[i].y, 100 , 100, variants[i].picture, 0, 0, variants[i].width, variants[i].height,  TX_WHITE);
         Win32::TransparentBlt (txDC(), x, y, width, height, picture, 0, 0, width, height, TX_WHITE);
    }

    //��������� ������ �����
    void draw2()
    {
        Win32::TransparentBlt (txDC(), x, y, 150, 120, picture, 0, 0, width, height, TX_YELLOW);
    }
};


//��������� ���� ��������� � �����
void drawAllVariants(string category, Picture* variants, int count_variants)
{
    for (int nomer = 0; nomer < count_variants; nomer = nomer + 1)
    {
        if (category == variants[nomer].category)
        {



            variants[nomer].draw();


        }
    }
}
void drawAllPlans(string category, Picture* variants, int count_variants)
{
    for (int nomer = 0; nomer < count_variants; nomer = nomer + 1)
    {
        if (category == variants[nomer].category)
        {
            variants[nomer].draw2();
        }
    }
}

//��������� Bed2
void drawAllBED2(Picture* Bed2, int n_pics)
{
    for (int nomer = 0; nomer <  n_pics; nomer = nomer + 1)
    {
        if(Bed2[nomer].visible == true)
            Bed2[nomer].draw();
    }
}








 bool activee = true;
//�������� ��������
int movePic(Picture* Bed2, int Active_Pic, int n_pics)
{
    //�������� ������
    for (int n = 0; n < n_pics; n = n + 1)
    {
        if(txMouseX() >= Bed2[n].x &&      //!!!!!!!!!!!!!
            txMouseY() >= Bed2[n].y &&
            txMouseX() <= Bed2[n].x +  Bed2[n].width &&
            txMouseY() <= Bed2[n].y +  Bed2[n].height  &&
            txMouseButtons() == 1 && activee == true)
        {
            //Bed2[n].x = txMouseX();
            //Bed2[n].y = txMouseY();
            Active_Pic = n;
            activee = false;
        }
    }
    if (txMouseButtons() == 0)
    activee = true;



    if(Active_Pic >= 0 && txMouseButtons() == 1)
    {
        Bed2[Active_Pic].x = txMouseX();
        Bed2[Active_Pic].y = txMouseY();

    }


     bool monolit = true;
     int x1 = 0, y1 = 0;

    if(Active_Pic >= 0 && txMouseButtons() == 0)
    {
        for (int x = Bed2[Active_Pic].x;
                 x < Bed2[Active_Pic].x + Bed2[Active_Pic].width;
                 x = x + 5)
        {
            for (int y = Bed2[Active_Pic].y;
                     y < Bed2[Active_Pic].y + Bed2[Active_Pic].height;
                     y = y + 5)

            {
                if (txGetPixel(x, y) == TX_BLACK)
                {
                    monolit = false;
                    x1 = x - 200;
                    y1 = y - 200;
                }
            }
        }

        //���� ����������� � ������, ������ �����
        if (!monolit)
        {
            Bed2[Active_Pic].x = random(100, 1100);
            Bed2[Active_Pic].y = random(100, 650);

            //if (Bed2[Active_Pic].x <= 50);
            //Bed2[Active_Pic].x = 100;
        }




        Active_Pic = -1;
    }

    return Active_Pic;
}


//�������� ���� ��������
void deletePicBed(Picture* variants, int count_variants, Picture* Plans)
{
    for(int i = 0; i < count_variants; i = i +1)
    {
        txDeleteDC(variants[i].picture);
        txDeleteDC(Plans[i].picture);
    }
}
