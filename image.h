#ifndef _IMAGE_H_
#define _IMAGE_H_
#include <iostream>
#include "string.hpp"

class Image
{
    protected:
        char extension[3];
        String name;
        size_t height, width;
        //int mat**;
    public:
        Image(){;}
        Image& operator=(const Image&);
        virtual void open(String) = 0;
        virtual Image* clone()const = 0;
        const String get_name()const {return name;}
        void print()const{std::cout << "height = " << height << " width= " << width << std::endl;}
};
#endif // _IMAGE_H_
