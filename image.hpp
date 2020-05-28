#ifndef _IMAGE_H_
#define _IMAGE_H_
#include <iostream>
#include "string.hpp"
class Image
{
    private:
        char extension[3];
        //int mat**;
    public:
        Image();
        Image& operator=(const Image&);
};
#endif // _IMAGE_H_
