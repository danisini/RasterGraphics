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
    PPM im("picture1.ppm");
    im.open();
    im.rotate("right");
    im.save("picture2.ppm");

    PGM im1("picture14.pgm");
    im1.open();
    im1.negative();
    im1.save("picture15.pgm");

    PBM im2("picture3.pbm");
    im2.open();
    im2.save("picture3.pbm");
    //User u;
    return 0;
}
