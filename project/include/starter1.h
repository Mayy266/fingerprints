#include <cstdlib>
#include <iostream>
#include <string>
#include "CImg.h"


#ifndef STARTER
#define STARTER

using namespace cimg_library;
using namespace std;


class BWImage {
  private:
    CImg<unsigned char> image;
    unsigned int hght;
    unsigned int wdth;
  public:
    BWImage(CImg<unsigned char> image);
    float toFloat(unsigned int x, unsigned int y);
    unsigned int maxIntensity();
    unsigned int minIntensity();
    void drawRect(unsigned int x, unsigned int y, unsigned int h, unsigned int w, unsigned int color);
    void symmetry_X();
    void symmetry_Y();
    void symmetry_diagonal();
    void display();
    void display_i();
    void display_f();
    unsigned int height();
    unsigned int width();
};

#endif
