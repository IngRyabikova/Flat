///\file Files.cpp
///Библиотека работы с файлами

#pragma once
#include "TXLib.h"
#include <fstream>
#include <iostream>

using namespace std;

/// по адресу узнают автоматом ширину
int getWidth(const char* address)
{
    char header[54];
    ifstream bmp;
    bmp.open(address, ios::in | ios::binary);

    bmp.read(header, 54);
    int width = *(int *)&header[18];
    return width;
}
/// по адресу узнают автоматом высоту
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
    ///Выбранный адрес файла
    string str = "";

    //Окно
    OPENFILENAME ofn;
    char szFile[260];			/// буфер для имени файла

    /// Инициализация OPENFILENAME
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

    ///Либо сохраняем, либо открываем
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


