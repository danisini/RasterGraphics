#include <iostream>
#include <vector>
#include "session.hpp"

void Session::deleteSession()
{
    v.clear();
    for(size_t i = 0; i < numImages; i ++)
        delete images[i];
    if(images != nullptr)delete[] images;
}

void Session::copySession(const Session &other)
{
    numImages = other.numImages;
    size_t vectorSize = other.operations.size();
    for(size_t i = 0; i < vectorSize; i ++)
        operations[i].push_back(operations[i]);
    images = new Image*[numImages];
    for(size_t i = 0; i < numImages; i ++)
        image[i] = other.image[i];
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
