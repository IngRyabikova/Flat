///\file Files.cpp
///���������� ������ � �������

#pragma once
#include "TXLib.h"
#include <fstream>
#include <iostream>

using namespace std;

/// �� ������ ������ ��������� ������
int getWidth(const char* address)
{
    char header[54];
    ifstream bmp;
    bmp.open(address, ios::in | ios::binary);

    bmp.read(header, 54);
    int width = *(int *)&header[18];
    return width;
}
/// �� ������ ������ ��������� ������
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
    ///��������� ����� �����
    string str = "";

    //����
    OPENFILENAME ofn;
    char szFile[260];			/// ����� ��� ����� �����

    /// ������������� OPENFILENAME
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

    ///���� ���������, ���� ���������
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


