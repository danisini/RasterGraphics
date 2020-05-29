#ifndef _USER_H_
#define _USER_H_
#include <iostream>
#include "session.hpp"
#include "image.h"
using namespace std;
class User
{
    private:
        Session** sessions;
        size_t numSessions, capacity, currSession;
        void deleteUser();
        void copyUser(const User&);
        void resizeSessions();
        void save(const String&);
    public:
        User();
        User(const User&);
        User& operator=(const User&);
        ~User();
};
void User::deleteUser()
{
    for(size_t i = 0; i < capacity; i ++)
        delete sessions[i];
    if(sessions != nullptr)delete[] sessions;
}
void User::resizeSessions()
{
    capacity += 8;
    Session** temp = new Session*[capacity];
    for(size_t i = 0; i < numSessions; i ++)
    {
        temp[i] = sessions[i];
        delete sessions[i];
    }
    delete[] sessions;
    sessions = new Session*[capacity];
    sessions = temp;
    ///ask if this will work or try it
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
            currSession = numSessions;
            numSessions ++;
            if(capacity == numSessions)
            {
                resizeSessions();
            }
            sessions[currSession] = new Session();
            sessions[currSession]->addImage(path);
            cout << "Session with ID " << currSession + 1 << " started!" << endl;
        }
        else
        if(command == "grayscale")
        {
            sessions[currSession]->addOperation("grayscale");///grayscale = 0
        }
        else
        if(command == "monochrome")
        {
            sessions[currSession]->addOperation("monochrome");///monochrome = 1
        }
        else
        if(command == "negative")
        {
            sessions[currSession]->addOperation("negative");///negative = 2
        }
        else
        if(command == "rotate")
        {
            String direction;
            cin >> direction;
            if(direction == "left")
                sessions[currSession]->addOperation("rotate left");/// rotate left = 3
            else if(direction == "right")
                sessions[currSession]->addOperation("rotate right");///rotate right = 4
            else
                cout << "Not valid direction." << endl;
        }
        else
        if(command == "undo")
        {
            sessions[currSession]->undo();
        }
        else
        if(command == "add")
        {
            String path;
            cin >> path;
            sessions[currSession]->addImage(path);
        }
        else
        if(command == "session")
        {
            cin >> command;
            if(command == "info")
            {
                sessions[currSession]->sessionInfo(currSession);
            }
            else cout << "Invalid command." << endl;
        }
        else
        if(command == "switch")
        {
            int num;
            cin >> num;
            if(num <= 0 || num > numSessions)
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
        else
        if(command == "save")
        {
            sessions[currSession]->saveSession("");
        }
        else
        if(command == "saveas")
        {
            String path;
            cin >> path;
            sessions[currSession]->saveSession(path);
        }
        else
        if(command == "close")
        {
            //sessions[currSession]->close();
        }
        else
        if(command == "help")
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
    capacity = other.capacity;
    sessions = new Session*[capacity];
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
