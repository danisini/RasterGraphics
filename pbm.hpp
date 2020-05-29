#ifndef _PBM_H_
#define _PBM_H_
#include <iostream>
#include "image.h"
#include <vector>

class PBM : public Image
{
    private:
        std::vector <bool> pixels;
    public:
        virtual void open(String) override;
        const size_t get_width()const{return width;}
        const size_t get_height()const{return height;}
        virtual Image* clone()const{return new PBM(*this);}
        PBM();
        PBM(String);
};
PBM::PBM()
{
    name = "";
    extension[0] = '\0';
}
PBM::PBM(String path)
{
    open(path);
}
void PBM::open(String path)
{
    std::ifstream file(path.stringToChar(), std::ios::in | std::ios::binary);
    if(!file)
    {
        std::cerr << "Failed to open!" << std::endl;
        return;
    }
    char type[4];
    file.read((char*)&type[0], sizeof(type[0]));
    file.read((char*)&type[1], sizeof(type[1]));
    file.read((char*)&type[2], sizeof(type[2]));

    type[3] = '\0';
    std::cout << "magicNumber=" << type << std::endl;
    size_t range = 0;
    size_t arr[3] = {0, 0, 0};
    char c;
    for(size_t i = 0; i < 3; i ++)
    {
        bool flag = 1;
        while(flag)
        {
            file.read((char*)&c, sizeof(c));
            if(c >= '0' && c <= '9')
                arr[i] = arr[i] * 10 + (c - '0');
            else flag = 0;
        }
    }
    width = arr[0];
    height = arr[1];
    range = arr[2];

    std::cout << width <<" " <<height << "  " << range <<  std::endl;
    bool curr;
    for(size_t i = 0; i < height*width;)
    {
        file.get(c);
        for(int j = 7; j >= 0; j --)
        {
            int now = (c >> i) & 1;

            if(now >= 0 && now <= 1)
            {
                curr = now;
                std::cout << curr << std::endl;
                pixels.push_back(curr);
                i ++;
            }
        }
    }
    file.close();
}
#endif // _PBM_H_

