#ifndef _IMAGE_H_
#define _IMAGE_H_
#include <iostream>
#include "string.hpp"

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
};
Image& Image::operator=(const Image &other)
{
    for(size_t i = 0; i < 3; i ++)
        extension[i] = other.extension[i];
    return *this;
}

#endif // _IMAGE_H_
