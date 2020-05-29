#ifndef _STRING_H
#define _STRING_H
#include <iostream>
#include <cstring>

class String
{
private:
    char* str;
    size_t sz;
    bool flagForEndl;
    void copy_string(const String&);
    void delete_string();
    void add_char(const char);
public:
    String(const char* = "");
    String(const String&);
    String& operator=(const String&);
    ~String();

    size_t size()const;
    bool operator==(const String&)const;
    bool operator<(const String&)const;
    String operator+(const String&)const;
    String operator+(const char&)const;
    String& operator+=(const String&);
    String& operator+=(const char&);
    char& operator[](const size_t&);
    bool operator<=(const String&)const;
    bool operator>=(const String&)const;
    bool operator>(const String&)const;
    const char* stringToChar(){return str;}
    friend std::istream& operator>>(std::istream& is, String& str);
    friend std::ostream& operator<<(std::ostream& os, const String& str);
    friend std::istream& getline(std::istream& is, String& str);

};

void String::copy_string(const String& other)
{
    str = new char [strlen(other.str) + 1];
    strcpy(str, other.str);
    sz = other.sz;
}

void String::delete_string()
{
    delete[] str;
}

void String::add_char(const char ch)
{
    char a[2];
    a[0] = ch;
    a[1] = '\0';
    String temp(a);
    (*this) += temp;
}


String::String(const char* str_)
{
    str = new char [strlen(str_)+1];
    strcpy(str, str_);
    sz=strlen(str_);
}

String::String(const String& other)
{
    copy_string(other);
}

String& String::operator=(const String& other)
{
    if(this!=&other)
    {
        delete_string();
        copy_string(other);
    }
    return *this;
}

String::~String()
{
    delete_string();
}

size_t String::size() const
{
    return sz;
}

bool String::operator==(const String& other) const
{

    if(strcmp(str, other.str) == 0)return 1;
    return 0;
}

bool String::operator<(const String& other) const
{
    if(strcmp(str, other.str) < 0)return 1;
    return 0;
}

String String::operator+(const String& other) const
{
    String temp(*this);
    temp += other;
    return temp;
}
String String::operator+(const char& other) const
{
    String temp(*this);
    temp += other;
    return temp;
}

String& String::operator+=(const char& other)
{
    sz += 1;
    char* temp = new char[sz + 1];
    strcpy(temp, str);
    delete_string();
    temp[sz - 1] = other;
    temp[sz] = '\0';
    str = temp;
    return *this;
}
String& String::operator+=(const String& other)
{
    sz += other.sz;
    char* temp = new char[sz + 1];
    strcpy(temp, str);
    delete_string();
    strcat(temp, other.str);
    temp[sz] = '\0';
    str = temp;
    return *this;
}

char& String::operator[](const size_t& pos)
{
    if (pos < 0 || pos >= sz)return str[sz - 1];
    return str[pos];
}

bool String::operator<=(const String& other) const
{
    return !((*this) > other);
}

bool String::operator>=(const String& other) const
{
    return !((*this) < other);
}

bool String::operator>(const String& other) const
{
    if(strcmp(str, other.str) > 0)return 1;
    return 0;
}

std::istream& operator>>(std::istream& is, String& str)
{
    char ch;
    String temp = "";

    is.get(ch);
    while(ch != '\n' && ch != '\t' && ch != ' ')
    {
        temp.add_char(ch);
        is.get(ch);
    }
    str = temp;

    return is;
}

std::ostream& operator<<(std::ostream& os, const String& str)
{
    os << str.str;

    return os;
}

std::istream& getline(std::istream& is, String& str)
{
    char ch;
    String temp;

    is.get(ch);

    while(ch != '\n')
    {
        temp.add_char(ch);
        is.get(ch);
    }
    str = temp;
    return is;
}

#endif // _STRING_H_
