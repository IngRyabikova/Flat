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



string RunDialog(bool isSave)
{
    string str = "";
    OPENFILENAME ofn;			// ��������� ������������ ����������� ����
    char szFile[260];			// ����� ��� ����� �����
    HANDLE hf;              		// ���������� �����

    // ������������� OPENFILENAME
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
    if (GetOpenFileName(&ofn) == TRUE)
    {
        str = szFile;
    }

    return str;
}