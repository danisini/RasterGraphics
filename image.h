#ifndef _IMAGE_H_
#define _IMAGE_H_
#include <iostream>
#include "string.hpp"
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
class Image
{
    protected:
        char extension[3];
        String name;
        size_t height, width, range;
        //int mat**;
    public:
        Image(){;}
        Image& operator=(const Image&);
        virtual void open() = 0;
        virtual Image* clone()const = 0;
        const String get_name()const {return name;}
        virtual void grayscale() = 0;
        virtual void monochrome() = 0;
        virtual void negative() = 0;
        virtual void save(const String&) = 0;
        virtual void rotate(const String&) = 0;
        virtual const size_t get_range()const{return range;}
        virtual const RGB get_pixels(const size_t&)const = 0;
        const size_t get_width()const{return width;}
        const size_t get_height()const{return height;}
        virtual void makeCollage(Image*, Image*, const String&) = 0;
};
Image& Image::operator=(const Image &other)
{
    for(size_t i = 0; i < 3; i ++)
        extension[i] = other.extension[i];
    return *this;
}

#endif // _IMAGE_H_
