#ifndef _SESSION_H_
#define _SESSION_H_
#include <iostream>
#include "image.h"
#include <vector>
#include "string.hpp"
class Session
{
    private:
        Image** images;
        std::vector <size_t> timeAdded;
        size_t numImages;
        std::vector <String> operations;
        size_t currOperNum;
        void deleteSession();
        void copySession(const Session&);
    public:
        Session();
        Session(const Session&);
        Session& operator=(const Session&);
        ~Session();
        void addOperation(const size_t&);
        void undo();
};
void Session::addOperation(const size_t& operNum)
{
    operations.push_back(operNum);
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
    images = nullptr;
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
