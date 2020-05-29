#include <iostream>
#include "image.h"
#include "ppm.h"
#include "pgm.hpp"
#include "pbm.hpp"
#include <fstream>
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
    PBM im2;
    im2.open("picture6.pbm");

    return 0;
}
