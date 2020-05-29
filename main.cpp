#include <iostream>
#include <fstream>
#include "user.h"
#include "image.h"
#include "ppm.h"
#include "pgm.hpp"
#include "pbm.hpp"
using namespace std;
//#include "user.hpp"
int main()
{
    /*
    ofstream oFile;
    oFile.open("picture1.ppm");
    oFile << "P3" << ' ' << 3 << " " << 4 << " " << 5 << endl;
    for(int i = 0; i < 3*4; i ++)oFile << 3 << " ";
    oFile.close();
    */
    /**PPM im;
    im.open("picture3.ppm");
    im.print();
    PGM im1;
    im1.open("picture4.pgm");
    */
    PBM im2("picture6.pbm");
    im2.open();
    im2.save("picture6.pbm");
    //User u;
    return 0;
}
