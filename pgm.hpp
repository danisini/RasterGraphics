#ifndef _PGM_H_
#define _PGM_H_
#include <iostream>
#include <vector>
#include "image.h"

class PGM : public Image
{
    private:
        std::vector <size_t> pixels;
    public:
        virtual void open(String) override;
        const size_t get_width()const{return width;}
        const size_t get_height()const{return height;}
        virtual Image* clone()const{return new PGM(*this);}
        PGM(String);
        PGM();
};
PGM::PGM()
{
    name = "";
    extension[0] = '\0';
}
PGM::PGM(String path)
{
    open(path);
}
void PGM::open(String path)
{
    std::ifstream file(path.stringToChar(), std::ios::in | std::ios::binary);
    if(!file)
    {
        std::cerr << "Failed to open!" << std::endl;
        return;
    }
    char type[4];
    file.read((char*)&type[0], sizeof(type[0]));
    file.read((char*)&type[1], sizeof(type[1]));
    file.read((char*)&type[2], sizeof(type[2]));

    type[3] = '\0';
    std::cout << "magicNumber=" << type << std::endl;
    size_t range = 0;
    size_t arr[3] = {0, 0, 0};
    char c;
    for(size_t i = 0; i < 3; i ++)
    {
        bool flag = 1;
        while(flag)
        {
            file.read((char*)&c, sizeof(c));
            if(c >= '0' && c <= '9')
                arr[i] = arr[i] * 10 + (c - '0');
            else flag = 0;
        }
    }
    width = arr[0];
    height = arr[1];
    range = arr[2];

    std::cout << width <<" " <<height << "  " << range <<  std::endl;
    size_t curr;
    for(size_t i = 0; i < height*width; i ++)
    {
        curr = 0;
        bool flag = 1;
        while(flag)
        {
            file.read((char*)&c, sizeof(c));
            if(c >= '0' && c <= '9')
                curr = curr * 10 + (c - '0');
            else flag = 0;
        }
        std::cout << curr << std::endl;
        pixels.push_back(curr);
    }
    file.close();
}
#endif // _PGM_H_
