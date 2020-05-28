#include<iostream>
#include<image.hpp>
Image::Image()
{

}
Image& Image::operator=(const Image &other)
{
    for(size_t i = 0; i < 3; i ++)
        extension[i] = other.extension[i];
}
