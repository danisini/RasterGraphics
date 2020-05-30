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
        virtual void open() override;
        const size_t get_width()const{return width;}
        const size_t get_height()const{return height;}
        virtual Image* clone()const{return new PGM(*this);}
        virtual void save(const String&);
        PGM(String);
        PGM();
};
PGM::PGM()
{
    name = "";
    extension[0] = '\0';
    width = height = range = 0;
}
PGM::PGM(String path)
{
    name = path;
    extension[0] = 'p';
    extension[1] = 'g';
    extension[2] = 'm';
    ///open(path);
}
void PGM::save(const String& name_)
{
    name = name_;
    std::ofstream file(name.stringToChar(), std::ios::out);
    if(!file)
    {
        std::cerr << "Couldn't open the file!" << std::endl;
        return;
    }
    file << "P2" << '\n' << width << " " << height << '\n' << range << '\n';
    char c;
    int num, p = 0;
    for(size_t i = 0; i < height; i ++)
    {
        for(size_t j = 0; j < width - 1; j ++)
        {
            num = pixels[p++];
            file << num << " ";
        }
        file << pixels[p ++] << '\n';
    }
    file.close();
}
void PGM::open()
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
    size_t arr[3] = {0, 0, 0};
    char c;
    for(size_t i = 0; i < 3; i ++)
    {
        file >> arr[i];
    }
    width = arr[0];
    height = arr[1];
    range = arr[2];
    size_t curr;
    for(size_t i = 0; i < width * height; i ++)
    {
            file >> curr;
            pixels.push_back(curr);
    }
    file.close();
}
#endif // _PGM_H_

