#include <fstream>
#include <iostream>

using namespace std;
int main(const char* address)
{
    char header[54];
    ifstream bmp;
    bmp.open(address, ios::in | ios::binary);


    bmp.read(header, 54);
    int width = *(int *)&header[18];
    int width2 = *(int *)&header[22];
    cout << width << " " << width2;

}

