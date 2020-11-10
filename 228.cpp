#include<windows.h>
//#include "dirent.h"
#include<iostream>
#include<fstream>

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    WIN32_FIND_DATA FindFileData;
    HANDLE hf;
    hf=FindFirstFile("Картинки/Кровати/*", &FindFileData);

    //
    if (hf!=INVALID_HANDLE_VALUE){
        do{
            string str = FindFileData.cFileName;
            str = "Картинки/Кровати/"+ str;
            if (str.find(".bmp") != -1)
            {
                std::cout << str << "\n";
            }
        }
        while (FindNextFile(hf,&FindFileData)!=0);
        FindClose(hf);
    }
}
