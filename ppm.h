#ifndef _PPM_H_
#define _PPM_H_
#include <iostream>
#include "string.hpp"
#include "image.h"
#include <fstream>
#include <vector>

struct RGB
{
    int R, G, B;
    RGB(int R_ = 0, int G_ = 0, int B_ = 0)
    {
        R = R_;
        G = G_;
        B = B_;
    }
};
class PPM : public Image
{
    private:
        std::vector <RGB> pixels;
    public:
        virtual void open() override;
        const size_t get_width()const{return width;}
        const size_t get_height()const{return height;}
        virtual Image* clone()const{return new PPM(*this);}
        virtual void save(const String&){};
        PPM();
        PPM(String);
};
PPM::PPM()
{
    name = "";
    extension[0] = '\0';
}
PPM::PPM(String path)
{
    name = path;
    extension[0] = 'p';
    extension[1] = 'p';
    extension[2] = 'm';
    ///open(path);
}
void PPM::open()
{
    std::ifstream file(name.stringToChar(), std::ios::in | std::ios::binary);
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
    char newLine;
    std::cout << "magicNumber=" << type << std::endl;
    range = 0;
    short width_ = 0;
    short height_ = 0;

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
    RGB curr;
    for(size_t i = 0; i < height*width; i ++)
    {
        arr[0] = arr[1] = arr[2] = 0;
        for(size_t j = 0; j < 3; j ++)
        {
            bool flag = 1;
            while(flag)
            {
                file.read((char*)&c, sizeof(c));
                if(c >= '0' && c <= '9')
                    arr[j] = arr[j] * 10 + (c - '0');
                else flag = 0;
            }
        }
        curr.R = arr[0];
        curr.G = arr[1];
        curr.B = arr[2];
        pixels.push_back(curr);
    }
    file.close();
}

#endif // _PPM_H_
