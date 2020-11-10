//#include <stdafx>
#include "windows.h"
#include <iostream>

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
	WIN32_FIND_DATA FindFileData;
	HANDLE hf;
	//hf=FindFirstFile("c:\\*", &FindFileData);





	hf=FindFirstFile("Картинки/Кровати/*", &FindFileData);


	if (hf!=INVALID_HANDLE_VALUE)
	{
        do
		{
            string str = FindFileData.cFileName;
            str = "Картинки/Кровати/" + str;
            if(str.find(".bmp") != -1)
            {
                cout << str << endl;
            }
		}
		while (FindNextFile(hf,&FindFileData)!=0);
		FindClose(hf);
	}

	int a;
	std::cin >> a;
}
