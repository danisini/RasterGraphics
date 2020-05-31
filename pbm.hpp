#ifndef _PBM_H_
#define _PBM_H_
#include <iostream>
#include "image.h"
#include "vector.hpp"
#include <fstream>

class PBM : public Image
{
    private:
        Vector <bool> pixels;
    public:
        virtual void open() override;
        PBM();
        PBM(String);
        virtual void grayscale(){}
        virtual void monochrome(){}
        virtual void negative();
        virtual void save(const String&);
        virtual void rotate(const String&);
        virtual const RGB get_pixels(const size_t& ind)const{RGB curr; curr.R = curr.G = curr.B = pixels[ind];return curr;}
        virtual void makeCollage(Image*, Image*, const String&);
};

void PBM::makeCollage(Image* im1, Image* im2, const String& direction)
{
    if(direction == "horizontal")
    {
        size_t w = im1->get_width(), h = im1->get_height(), cnt1 = 0, cnt2 = 0;
        for(size_t i = 0; i < h; i ++)
        {
            for(size_t j = 0; j < w; j ++)
            {
                RGB curr = im1->get_pixels(cnt1);
                bool now = (curr.R == 1)?1:0;
                pixels.push_back(now);
                cnt1 ++;
            }
            for(size_t j = 0; j < w; j ++)
            {
                RGB curr = im2->get_pixels(cnt2);
                bool now = (curr.R == 1)?1:0;
                pixels.push_back(now);
                cnt2 ++;
            }
        }
        width = w * 2;
        height = h;
    }
    else
    if(direction == "vertical")
    {
        size_t w = im1->get_width(), h = im1->get_height();
        for(size_t i = 0; i < h * w; i ++)
        {
            RGB curr = im1->get_pixels(i);
            bool now = (curr.R == 1)?1:0;
            pixels.push_back(now);
        }
        for(size_t i = 0; i < h * w; i ++)
        {
            RGB curr = im2->get_pixels(i);
            bool now = (curr.R == 1)?1:0;
            pixels.push_back(now);
        }
        width = w;
        height = h * 2;
    }
    range = (im1->get_range() > im2->get_range())?im1->get_range():im2->get_range();
}
void PBM::rotate(const String& direction)
{
    if(direction == "right")
    {
        Vector <bool> temp;
        for(size_t i = 0; i < width; i ++)
        {
            size_t i1 = width * (height - 1) + i;
            for(size_t j = 0; j < height; j ++)
            {
                temp.push_back(pixels[i1]);
                i1 -= width;
            }
        }
        for(size_t i = 0; i < width * height; i ++)
        {
            pixels[i] = temp[i];
        }

        size_t swp;
        swp = height;
        height = width;
        width = swp;
    }
    else if(direction == "left")
    {
        Vector <bool> temp;
        for(size_t i = 0; i < width; i ++)
        {
            size_t i1 = width - i - 1;
            for(size_t j = 0; j < height; j ++)
            {
                temp.push_back(pixels[i1]);
                i1 += width;
            }
        }
        for(size_t i = 0; i < width * height; i ++)
        {
            pixels[i] = temp[i];
        }
        size_t swp;
        swp = height;
        height = width;
        width = swp;
    }
    else std::cout << "Not a correct inputed direction." << std::endl;;
}
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
        std::cerr << "Couldn't open the file!" << std::endl;;
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
        std::cerr << "Failed to open!" << std::endl;;
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

