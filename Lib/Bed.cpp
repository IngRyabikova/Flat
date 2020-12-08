#pragma once
#include "TXLib.h"
#include "Files.cpp"

const int PIC_SIZE = 100;

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
        if (width > height * 1.2)
            Win32::TransparentBlt (txDC(), x, y, PIC_SIZE, PIC_SIZE * height / width, picture, 0, 0, width, height, TX_WHITE);

        else if (height > width * 1.2)
            Win32::TransparentBlt (txDC(), x, y, PIC_SIZE * width / height, PIC_SIZE, picture, 0, 0, width, height, TX_WHITE);
        else
            Win32::TransparentBlt (txDC(), x, y, PIC_SIZE * 0.8, PIC_SIZE * 0.8, picture, 0, 0, width, height, TX_WHITE);
    }

    //��������� ������ �����
    void draw2()
    {
        Win32::TransparentBlt (txDC(), x, y, 150, 120, picture, 0, 0, width, height, TX_YELLOW);
    }
};

int Bot_reading(const char* address, Picture*variants, int N)
{
    setlocale(LC_ALL, "Russian");
    WIN32_FIND_DATA FindFileData;
    HANDLE hf;
    string str = address;
    str = str + "*";

    hf=FindFirstFile(str.c_str(), &FindFileData);

    //
    if (hf!=INVALID_HANDLE_VALUE){
        do{

            str = FindFileData.cFileName;
            str = (string)address + str;

            if (str.find(".bmp") != -1)
            {
                string s = str;
                variants[N] = {s.c_str()};
                N = N + 1;
                txSleep(20);
            }
        }
        while (FindNextFile(hf,&FindFileData)!=0);
        FindClose(hf);
    }

    return N;
}

void fillMebelParams(int count_variants, Picture* variants)
{
    for (int nomer = 0; nomer < count_variants; nomer = nomer + 1)
    {
        ///���������� ���������
        string s = variants[nomer].address;
        int pos = s.find("/", 0);
        int pos2 = s.find("/",pos + 1);
        variants[nomer].category = s.substr(pos + 1,pos2 - pos - 1);  //�� ������� / �� �������

        variants[nomer].visible = false;

        //���������� �������� ���� � �������1 ������ �������
        string category1 = variants[nomer].category;
        int pos1 = s.find(category1) ;
        s = s.replace(pos1, category1.size(),category1 + "1");


        variants[nomer].picture2 = txLoadImage(s.c_str());
        variants[nomer].picture1 = txLoadImage(variants[nomer].address.c_str());
        variants[nomer].picture = variants[nomer].picture1;


        ///������ � ������, �������� �� ������� �����
        variants[nomer].width = getWidth (variants[nomer].address.c_str());
        variants[nomer].x = 1100 + ((150 - variants[nomer].width) / 2);
        variants[nomer].height = getHeight(variants[nomer].address.c_str());
    }
}

void fillMebelCoords(Picture* variants, int count_variants)
{
    int y_Bed = 150;        ///int y_Bed ���������� �������� variants
    int y_Sofa = 150;       ///int y_Sofa ���������� ������� variants
    int y_Table = 150;      ///int y_Table ���������� ������ variants
    int y_Kuhna = 150;      ///int y_Kuhna ���������� Kuhna variants
    for (int i = 0; i < count_variants; i = i + 1)
    {
        variants[i].x = 1120;
        if (variants[i].category == "�������")
        {
            variants[i].y = y_Bed;
            y_Bed = y_Bed + PIC_SIZE * 1.1;

        }
        if (variants[i].category == "������")
        {
            variants[i].y = y_Sofa;
            y_Sofa = y_Sofa + PIC_SIZE * 1.1;
        }

        if(variants[i].category == "�����")
        {
            variants[i].y = y_Table;
            //x_Table = 700;
            y_Table = y_Table + PIC_SIZE * 1.1;
        }
        if(variants[i].category == "������")
        {
            variants[i].y = y_Kuhna;
            y_Kuhna = y_Kuhna + PIC_SIZE * 1.1;
        }
    }

}


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
//��������� ���� ������
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
            txMouseX() <= Bed2[n].x + PIC_SIZE &&
            txMouseY() <= Bed2[n].y + PIC_SIZE &&
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
                 x < Bed2[Active_Pic].x + Bed2[Active_Pic].width * 0.8;
                 x = x + 5)
        {
            for (int y = Bed2[Active_Pic].y;
                     y < Bed2[Active_Pic].y + Bed2[Active_Pic].height * 0.8;
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
            Bed2[Active_Pic].x = random(100, 950);
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
