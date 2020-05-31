#ifndef _PPM_H_
#define _PPM_H_
#include <iostream>
#include "string.hpp"
#include "image.h"
#include <fstream>
#include "vector.hpp"

class PPM : public Image
{
    private:
        Vector <RGB> pixels;
    public:
        PPM();
        PPM(String);
        virtual void open() override;
        virtual void save(const String&);
        virtual void grayscale();
        virtual void monochrome();
        virtual void negative();
        virtual void rotate(const String&);
        virtual const RGB get_pixels(const size_t& ind)const{return pixels[ind];}
        virtual void makeCollage(Image*, Image*, const String&);
};
void PPM::makeCollage(Image* im1, Image* im2, const String& direction)
{
    if(direction == "horizontal")
    {
        size_t w = im1->get_width(), h = im1->get_height(), cnt1 = 0, cnt2 = 0;
        for(size_t i = 0; i < h; i ++)
        {
            for(size_t j = 0; j < w; j ++)
            {
                pixels.push_back(im1->get_pixels(cnt1));
                cnt1 ++;
            }
            for(size_t j = 0; j < w; j ++)
            {
                pixels.push_back(im2->get_pixels(cnt2));
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
            pixels.push_back(im1->get_pixels(i));
        }
        for(size_t i = 0; i < h * w; i ++)
        {
            pixels.push_back(im2->get_pixels(i));
        }
        width = w;
        height = h * 2;
    }
    range = (im1->get_range() > im2->get_range())?im1->get_range():im2->get_range();
}
void PPM::rotate(const String& direction)
{
    if(direction == "right")
    {
        Vector <RGB> temp;
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
            pixels[i].R = temp[i].R;
            pixels[i].G = temp[i].G;
            pixels[i].B = temp[i].B;
        }

        size_t swp;
        swp = height;
        height = width;
        width = swp;
    }
    else if(direction == "left")
    {
        Vector <RGB> temp;
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
            pixels[i].R = temp[i].R;
            pixels[i].G = temp[i].G;
            pixels[i].B = temp[i].B;
        }

        size_t swp;
        swp = height;
        height = width;
        width = swp;
    }
    else std::cout << "Not a correct inputed direction." << std::endl;;
}
void PPM::negative()
{
    std::cout << "here" << std::endl;
    for(size_t i = 0; i < pixels.size(); i ++)
    {
        pixels[i].R = range - pixels[i].R;
        pixels[i].G = range - pixels[i].G;
        pixels[i].B = range - pixels[i].B;
    }
}
void PPM::monochrome()
{
    for(size_t i = 0; i < pixels.size(); i ++)
    {
        size_t r = pixels[i].R, g = pixels[i].G, b = pixels[i].B;
        size_t now =  (double)(r * 0.2125) + (double)(g * 0.7154) + (double)(b * 0.0721);
        if(now > range / 2) now = range;
        else now = 0;
        pixels[i].R = pixels[i].G = pixels[i].B = now;
        /*pixels[i].R = (double)(r * 0.2125) + (double)(g * 0.7154) + (double)(b * 0.0721);
        pixels[i].G = (double)(r * 0.2125) + (double)(g * 0.7154) + (double)(b * 0.0721);
        pixels[i].B = (double)(r * 0.2125) + (double)(g * 0.7154) + (double)(b * 0.0721);
        */
    }
}
void PPM::grayscale()
{
    for(size_t i = 0; i < pixels.size(); i ++)
    {
        size_t r = pixels[i].R, g = pixels[i].G, b = pixels[i].B;
        pixels[i].R = (double)(r * 0.299) + (double)(g * 0.587) + (double)(b * 0.114);
        pixels[i].G = (double)(r * 0.299) + (double)(g * 0.587) + (double)(b * 0.114);
        pixels[i].B = (double)(r * 0.299) + (double)(g * 0.587) + (double)(b * 0.114);
    }
}
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
void PPM::save(const String& name_)
{
    name = name_;
    std::ofstream file(name.stringToChar(), std::ios::out);
    if(!file)
    {
        std::cerr << "Couldn't open the file!" << std::endl;
        return;
    }
    file << "P3" << '\n' << width << " " << height << '\n' << range << '\n';
    char c;
    int num, p = 0;
    RGB curr;
    for(size_t i = 0; i < height; i ++)
    {
        for(size_t j = 0; j < width - 1; j ++)
        {
            curr = pixels[p ++];
            file << curr.R << " " << curr.G << " " << curr.B << " ";
        }
        file << pixels[p].R << " " << pixels[p].G << " " << pixels[p].B << '\n';
        p ++;
    }
    file.close();
}
void PPM::open()
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
    size_t arr[3] = {0, 0, 0};
    char c;
    for(size_t i = 0; i < 3; i ++)
    {
        file >> arr[i];
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
            file >> arr[j];
        }
        curr.R = arr[0];
        curr.G = arr[1];
        curr.B = arr[2];
        pixels.push_back(curr);
    }
    file.close();
}

#endif // _PPM_H_
