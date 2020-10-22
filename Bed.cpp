#include "TXLib.h"

struct Picture
{
    int x;
    int y;
    const char* address;
    bool visible;
    string category;
    HDC picture;
    int width;
    int height;

    //���������
    void draw()
    {
        txTransparentBlt (txDC(), x, y, width, height, picture);
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

//��������� Bed2
void drawAllBED2(Picture* Bed2, int n_pics)
{
    for (int nomer = 0; nomer <  n_pics; nomer = nomer + 1)
    {
        if(Bed2[nomer].visible == true)
            Bed2[nomer].draw();
    }
}

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
            txMouseButtons() == 1 )
        {
            //Bed2[n].x = txMouseX();
            //Bed2[n].y = txMouseY();
            Active_Pic = n;
        }
    }

    if(Active_Pic >= 0 && txMouseButtons() == 1)
    {
        Bed2[Active_Pic].x = txMouseX();
        Bed2[Active_Pic].y = txMouseY();

    }
    if(txMouseButtons() == 0)
        Active_Pic = -1;

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
