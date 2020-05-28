#ifndef _SESSION_H_
#define _SESSION_H_
#include <iostream>
#include "image.hpp"
#include <vector>
#include "string.hpp"
class Session
{
    private:
        Image** images;
        size_t numImages;
        vector <String> operations;
        void deleteSession();
        void copySession(const Session&);
    public:
        Session();
        Session(const Session&);
        Session& operator=(const Session&);
        ~Session();
};

#endif // _SESSION_H_
