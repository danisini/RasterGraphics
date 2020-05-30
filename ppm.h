#ifndef _PPM_H_
#define _PPM_H_
#include <iostream>
#include "string.hpp"
#include "image.h"
#include <fstream>
#include <vector>

struct RGB
{
    size_t R, G, B;
    RGB(size_t R_ = 0, size_t G_ = 0, size_t B_ = 0)
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
        virtual void save(const String&);
        virtual void grayscale();
        virtual void monochrome();
        virtual void negative();
        virtual void rotate(const String&);
        PPM();
        PPM(String);
};
void PPM::rotate(const String& direction)
{
    if(direction == "right")
    {
        std::vector <RGB> temp;
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
        std::vector <RGB> temp;
        std::cout << "tes3 "<< height << " "<< width << std::endl;
        for(size_t i = 0; i < width; i ++)
        {
            size_t i1 = width - i - 1;
            for(size_t j = 0; j < height; j ++)
            {
                temp.push_back(pixels[i1]);
                i1 += width;
            }
        }
        std::cout << "test2" << std::endl;
        for(size_t i = 0; i < width * height; i ++)
        {
            pixels[i].R = temp[i].R;
            pixels[i].G = temp[i].G;
            pixels[i].B = temp[i].B;
        }
        std::cout << "test1" << std::endl;
        size_t swp;
        swp = height;
        height = width;
        width = swp;
    }
    else std::cout << "Not a correct inputed direction." << std::endl;
}
void PPM::negative()
{
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
