#ifndef _SESSION_H_
#define _SESSION_H_
#include <iostream>
#include "image.h"
#include <vector>
#include "string.hpp"
#include "ppm.h"
#include "pgm.hpp"
#include "pbm.hpp"
using namespace std;
class Session
{
    private:
        Image** images;
        std::vector <size_t> timeAdded;
        std::vector <String> operations;
        size_t numImages, capacity, currOperNum, currImageNum;
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
};
void Session::saveSession(const String& path)
{
    for(size_t i = 0; i < numImages; i ++)
        images[i]->open();
    size_t vsz = operations.size();
    /*for(size_t i = 0; i < vsz; i ++)
    {
        if(operations[i] == "grayscale")
        {
            for(size_t j = 0; j < timeAdded[i] - 1; j ++)
                images[j]->grayscale();
        }
        else if(operations[i] == "monochrome")
        {
            for(size_t j = 0; j < timeAdded[i] - 1; j ++)
                images[j]->monochrome(j);
        }
        else if(operations[i] == "negative")
        {
            for(size_t j = 0; j < timeAdded[i] - 1; j ++)
                images[j]->negative(j);
        }
        else if(operations[i] == "collage")
        {

        }
    }*/

    if(!(path == ""))images[0]->save(path);
    else images[0]->save(images[0]->get_name());///trqbva i name da stane tva podadenoto chrez parametura zaduljitelno!!!!

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
    std::cout << "Session ID = " << sessionNum + 1<< std::endl;
    for(size_t i = 0; i < numImages; i ++)
        std::cout << "Image number " << i + 1 << " is: " << images[i]->get_name() << std::endl;
    for(size_t i = 0; i < operations.size(); i ++)
        std::cout << "Operation number " << i + 1 << " will be: " << operations[i] << " and it will be used on first " << timeAdded[i] << " images if possible." << std::endl;
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
        cout << "Not a valid format." << endl;
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

}
void Session::addOperation(const String& operName)
{
    operations.push_back(operName);
    timeAdded.push_back(numImages);///pravim operacii na purvite timeAdded[i] - 1 snimki
}
void Session::deleteSession()
{
    operations.clear();
    timeAdded.clear();
    for(size_t i = 0; i < numImages; i ++)
        delete images[i];
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
    currOperNum = 0;
    currImageNum = 0;
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
