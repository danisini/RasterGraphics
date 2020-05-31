#ifndef _SESSION_H_
#define _SESSION_H_
#include <iostream>
#include "image.h"
#include "vector.hpp"
#include "string.hpp"
#include "ppm.h"
#include "pgm.hpp"
#include "pbm.hpp"
class Session
{
    private:
        Image** images;
        Vector <size_t> timeAdded;
        Vector <String> operations;
        size_t numImages, capacity;
        void deleteSession();
        void copySession(const Session&);
        void resizeSession();
    public:
        Session();
        Session(const Session&);
        Session& operator=(const Session&);
        ~Session();
        void addOperation(const String&);
        void undo();
        void addImage(String path);
        void sessionInfo(const size_t&);
        void saveSession(const String&);
        void collage(const String&, String, String, String);
};
void Session::collage(const String& direction, String image1, String image2, String outimage)
{
    int ind1 = -1, ind2 = -1;
    for(size_t i = 0; i < numImages; i ++)
    {
        if(images[i]->get_name() == image1)ind1 = i;
        if(images[i]->get_name() == image2)ind2 = i;
    }
    if(ind1 == -1 || ind2 == -1)
    {
        std::cout << "Images not found for the collage!" << std::endl;;
        return;
    }
    if(images[ind1]->get_width() != images[ind2]->get_width() || images[ind1]->get_height() != images[ind2]->get_height())
    {
        std::cout << "Images don't have the same size!" << std::endl;;
        return;
    }
    if(!(image1[image1.size() - 2] == image2[image2.size() - 2] && image2[image2.size() - 2] == outimage[outimage.size() - 2]))
    {
        std::cout << "The three pictures are not in the same format!" << std::endl;;
        return;
    }
    addImage(outimage);
    images[numImages - 1]->makeCollage(images[ind1], images[ind2], direction);
}
void Session::saveSession(const String& path)
{
    size_t vsz = operations.size();
    for(size_t i = 0; i < vsz; i ++)
    {
        if(operations[i] == "grayscale")
        {
            for(size_t j = 0; j < timeAdded[i]; j ++)
                images[j]->grayscale();
        }
        else if(operations[i] == "monochrome")
        {
            for(size_t j = 0; j < timeAdded[i]; j ++)
                images[j]->monochrome();
        }
        else if(operations[i] == "negative")
        {
            for(size_t j = 0; j < timeAdded[i]; j ++)
                images[j]->negative();
        }
        else if(operations[i] == "rotate left")
        {
            for(size_t j = 0; j < timeAdded[i]; j ++)
                images[j]->rotate("left");
        }
        else if(operations[i] == "rotate right")
        {
            for(size_t j = 0; j < timeAdded[i]; j ++)
                images[j]->rotate("right");
        }
    }
    if(!(path == ""))images[0]->save(path);
    else images[0]->save(images[0]->get_name());

    for(size_t i = 1; i < numImages; i ++)
        images[i]->save(images[i]->get_name());

    while(operations.size() != 0)
    {
        operations.pop_back();
        timeAdded.pop_back();
    }
}
void Session::sessionInfo(const size_t& sessionNum)
{
    std::cout << "Session ID = " << sessionNum + 1<< std::endl;;
    for(size_t i = 0; i < numImages; i ++)
        std::cout << "Image number " << i + 1 << " is: " << images[i]->get_name() << std::endl;;
    for(size_t i = 0; i < operations.size(); i ++)
        std::cout << "Operation number " << i + 1 << " will be: " << operations[i] << " and it will be used on first " << timeAdded[i] << " images if possible." << std::endl;;
}
void Session::resizeSession()
{
    capacity += 8;
    Image** temp = new Image*[capacity];
    for(size_t i = 0; i < numImages; i ++)
    {
        temp[i] = images[i];
        delete images[i];
    }
    delete[] images;
    images = new Image*[capacity];
    images = temp;
}
void Session::addImage(String path)
{
    size_t sz = path.size();
    size_t index = 0;
    if(path[sz - 2] == 'p')index = 1;
    else if(path[sz - 2] == 'g')index = 2;
    else if(path[sz - 2] == 'b')index = 3;
    else
    {
        std::cout << "Not a valid format." << std::endl;;
        return;
    }
    numImages ++;
    if(numImages == capacity)
        resizeSession();
    if(index == 1)
        images[numImages - 1] = new PPM(path);
    else if(index == 2)
        images[numImages - 1] = new PGM(path);
    else if(index == 3)
        images[numImages - 1] = new PBM(path);
    images[numImages - 1]->open();
    std::cout << "Image was added successfully!" << std::endl;
}
void Session::addOperation(const String& operName)
{
    operations.push_back(operName);
    timeAdded.push_back(numImages);///pravim operacii na purvite timeAdded[i] - 1 snimki
}
void Session::deleteSession()
{
    std::cout << numImages << std::endl;
    for(size_t i = 0; i < numImages; i ++)
        if(images[i] != nullptr)delete images[i];
    if(images != nullptr)delete[] images;
}
void Session::undo()
{
    operations.pop_back();
    timeAdded.pop_back();
}
void Session::copySession(const Session &other)
{
    numImages = other.numImages;
    size_t vectorSize = other.operations.size();
    for(size_t i = 0; i < vectorSize; i ++)
        operations.push_back(other.operations[i]);
    vectorSize = other.timeAdded.size();
    for(size_t i = 0; i < vectorSize; i ++)
        timeAdded.push_back(other.timeAdded[i]);
    images = new Image*[numImages];
    for(size_t i = 0; i < numImages; i ++)
        images[i] = other.images[i];
}

Session::Session()
{
    numImages = 0;
    capacity = 8;
    images = new Image*[capacity];
}

Session::Session(const Session &other)
{
    copySession(other);
}

Session& Session::operator=(const Session &other)
{
    if(this != &other)
    {
        deleteSession();
        copySession(other);
    }
    return *this;
}

Session::~Session()
{
    deleteSession();
}

#endif // _SESSION_H_
