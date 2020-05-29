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
        void print()const{std::cout << "height = " << height << " width= " << width << std::endl;}

        //virtual void grayscale(const size_t&) = 0;
        //virtual void monochrome(const size_t&) = 0;
        //virtual void negative(const size_t&) = 0;
        virtual void save(const String&) = 0;

};
#endif // _IMAGE_H_
