#ifndef _USER_H_
#define _USER_H_
#include <iostream>
#include "session.hpp"
#include "image.h"

class User
{
    private:
        Session** sessions;
        size_t numSessions;
        size_t currSession;
        void deleteUser();
        void copyUser(const User&);
    public:
        User();
        User(const User&);
        User& operator=(const User&);
        ~User();
};
void User::deleteUser()
{
    for(size_t i = 0; i < numSessions; i ++)
        delete sessions[i];
    if(sessions != nullptr)delete[] sessions;
}
User::User()
{
    numSessions = 0;
    capacity = 8;
    currSession = 0;
    sessions = new Session*[capacity];
    ///numSession = capacity -> capacity += 8
    cout << "Please, start using 'load <picture_name>' command." << endl;
    String command = "";
    while(!(command == "exit"))
    {
        cin >> command;
        if(command == "load")
        {
            String path;
            cin >> path;
            numSessions ++;
            currSession = numSession;
            if(capacity == numSessions)
            {
                resizeSessions();
            }
            sessions[currSession].addImage(path);
        }
        else
        if(command == "grayscale")
        {
            sessions[currSession].addOperation(0);///grayscale = 0
        }
        else
        if(command == "monochrome")
        {
            sessions[currSession].addOperation(1);///monochrome = 1
        }
        else
        if(command == "negative")
        {
            sessions[currSession].addOperation(2);///negative = 2
        }
        else
        if(command == "rotate")
        {
            String direction;
            cin >> direction;
            if(direction == "left")
                sessions[currSession].addOperation(3);/// rotate left = 3
            else if(direction == "right")
                sessions[currSession].addOperation(4);///rotate right = 4
            else
                cout << "Not valid direction." << endl;
        }
        else
        if(command == "undo")
        {
            sessions[currSession].undo();
        }
        else
        if(command == "add")
        {
            String path;
            cin >> path;
            sessions[currSession].addImage(path);
        }
        else
        if(command == "session")
        {
            cin >> command;
            if(command == "info")
            {
                sessions[currSession].sessionInfo();
            }
            else cout << "Invalid command." << endl;
        }
        else
        if(command == "switch")
        {
            int num;
            cin >> num;
            if(num < 0 || num > numSessions)
            {
                cout << "Not a valid session number." << endl;
            }
            else
            {
                currSession = num;
            }
        }
        else
        if(command == "collage")
        {

        }
    }
}

User::~User()
{
    deleteUser();
}
void User::copyUser(const User &other)
{
    numSessions = other.numSessions;
    sessions = new Session*[numSessions];
    for(size_t i = 0; i < numSessions; i ++)
        sessions[i] = other.sessions[i];
}

User::User(const User &other)
{
    copyUser(other);
}

User& User::operator=(const User &other)
{
    if(this != &other)
    {
        deleteUser();
        copyUser(other);
    }
    return *this;
}


#endif // _USER_H_
