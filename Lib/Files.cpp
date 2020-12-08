#pragma once
#include "TXLib.h"
#include <fstream>
#include <iostream>

using namespace std;

int getWidth(const char* address)
{
    char header[54];
    ifstream bmp;
    bmp.open(address, ios::in | ios::binary);

    bmp.read(header, 54);
    int width = *(int *)&header[18];
    return width;
}
int getHeight(const char* address)
{
    char header[54];
    ifstream bmp;
    bmp.open(address, ios::in | ios::binary);

    bmp.read(header, 54);
    int width = *(int *)&header[22];
    return width;
}



string RunDialog(bool isSave)
{
    string str = "";
    OPENFILENAME ofn;			// структура стандартного диалогового окна
    char szFile[260];			// буфер для имени файла
    HANDLE hf;              		// дескриптор файла

    // Инициализация OPENFILENAME
    ZeroMemory(&ofn, sizeof(OPENFILENAME));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = txWindow();
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = "Text\0*.TXT\0";
    ofn.nFilterIndex = 0;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;


    if(isSave == false)
    {
       if(GetOpenFileName(&ofn) == TRUE)
            str = szFile;
    }
    else if(isSave)
    {
        GetSaveFileName(&ofn) == TRUE;
        str = szFile;
    }

    return str;
}



     /*
int readFile(Picture* Bed2, string strokaX, string strokaY, string address, int n_pics,  )
{
    ifstream file2(fileName);
    //Прочитал первую строку
    while (file2.good())
    {
        getline(file2, strokaX);
        if (strokaX.size() > 0)
        {
            Bed2[n_pics].x = atoi(strokaX.c_str());

            //Строка2 (y)
            getline(file2, strokaY);
            Bed2[n_pics].y = atoi(strokaY.c_str());

            //Строка3 (адрес)
            getline(file2, address);
            Bed2[n_pics].address = address.c_str();

            bool addressFind = false;
            for(int i = 0; i < n_pics; i++)
               if(Bed2[i].address == address)
               {
                  addressFind = true;
                  Bed2[n_pics].picture =Bed2[i].picture;
               }
           if(!addressFind)
                Bed2[n_pics].picture = txLoadImage(Bed2[n_pics].address.c_str());


            Bed2[n_pics].visible = true;
            //Bed2[n_pics].picture = txLoadImage(Bed2[n_pics].address.c_str());
            //Ширина и высота из свойств файла
            Bed2[n_pics].width = getWidth (Bed2[n_pics].address.c_str());
            Bed2[n_pics].height = getHeight(Bed2[n_pics].address.c_str());

            n_pics = n_pics + 1;

    }

return n_pics;
}   */

