#ifndef _PBM_H_
#define _PBM_H_
#include <iostream>
#include "image.h"
#include <vector>
#include <fstream>
class PBM : public Image
{
    private:
        std::vector <bool> pixels;
    public:
        virtual void open() override;
        const size_t get_width()const{return width;}
        const size_t get_height()const{return height;}
        virtual Image* clone()const{return new PBM(*this);}
        PBM();
        PBM(String);
        virtual void grayscale(){}
        virtual void monochrome(){}
        virtual void negative();
        virtual void save(const String&);
        virtual void rotate(const String&){}
};
void PBM::negative()
{
    for(size_t i = 0; i < pixels.size(); i ++)
    {
        pixels[i] = 1 - pixels[i];
    }
}
void PBM::save(const String& name_)
{
    name = name_;
    std::ofstream file(name.stringToChar(), std::ios::out);
    if(!file)
    {
        std::cerr << "Couldn't open the file!" << std::endl;
        return;
    }
    file << "P1" << '\n' << width << " " << height << '\n';
    char c;
    bool num;
    size_t p = 0;
    for(size_t i = 0; i < height; i ++)
    {
        for(size_t j = 0; j < width; j ++)
        {
            num = pixels[p++];
            file << num;
        }
        file << '\n';
    }
    file.close();
}
PBM::PBM()
{
    name = "";
    width = height = range = 0;
    extension[0] = '\0';
}
PBM::PBM(String path)
{
    name = path;
    extension[0] = 'p';
    extension[1] = 'b';
    extension[2] = 'm';
    ///open(path);
}
void PBM::open()
{
    std::ifstream file(name.stringToChar(), std::ios::in);
    if(!file)
    {
        std::cerr << "Failed to open!" << std::endl;
        return;
    }
    char type[4];
    file.get(type[0]);
    file.get(type[1]);
    file.get(type[2]);
    type[3] = '\0';
    size_t arr[2] = {0, 0};
    char c;
    for(size_t i = 0; i < 2; i ++)
    {
        file >> arr[i];
    }
    width = arr[0];
    height = arr[1];
    range = 0;
    char curr;
    for(size_t i = 0; i < width * height;)
    {
            file.get(curr);
            if(curr >= '0'  && curr <= '1')
            {
                pixels.push_back(curr - '0');
                i ++;
            }
    }
    file.close();
}
#endif // _PBM_H_

