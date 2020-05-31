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
        virtual void grayscale(){;}
        virtual void monochrome();
        virtual void negative();
        virtual void rotate(const String&);
        void set_pixel(const size_t& ind){pixels.push_back(ind);}
        PGM(String);
        virtual const RGB get_pixels(const size_t& ind)const
        {
            RGB curr;
            curr.R = curr.G = curr.B = pixels[ind];
            return curr;
        }
        PGM();
        virtual void makeCollage(Image*, Image*, const String&);
};
void PGM::makeCollage(Image* im1, Image* im2, const String& direction)
{
    if(direction == "horizontal")
    {
        size_t w = im1->get_width(), h = im1->get_height(), cnt1 = 0, cnt2 = 0;
        for(size_t i = 0; i < h; i ++)
        {
            for(size_t j = 0; j < w; j ++)
            {
                RGB curr = im1->get_pixels(cnt1);
                pixels.push_back(curr.R);
                cnt1 ++;
            }
            for(size_t j = 0; j < w; j ++)
            {
                RGB curr = im2->get_pixels(cnt2);
                pixels.push_back(curr.R);
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
            pixels.push_back(curr.R);
        }
        for(size_t i = 0; i < h * w; i ++)
        {
            RGB curr = im2->get_pixels(i);
            pixels.push_back(curr.R);
        }
        width = w;
        height = h * 2;
    }
    range = (im1->get_range() > im2->get_range())?im1->get_range():im2->get_range();
}
void PGM::rotate(const String& direction)
{
    if(direction == "right")
    {
        std::vector <size_t> temp;
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
        std::vector <size_t> temp;
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
    else std::cout << "Not a correct inputed direction." << std::endl;
}
void PGM::negative()
{
    for(size_t i = 0; i < pixels.size(); i ++)
    {
        pixels[i] = range - pixels[i];
    }
}
void PGM::monochrome()
{
    for(size_t i = 0; i < pixels.size(); i ++)
    {
        if(pixels[i] > range / 2)pixels[i] = range;
        else pixels[i] = 0;
    }
}
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

