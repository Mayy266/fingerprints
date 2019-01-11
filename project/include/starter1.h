#include <cstdlib>
#include <iostream>
#include <string>
#include <math.h>
#include <vector>
#include "CImg.h"
#include "coord.h"


#ifndef STARTER
#define STARTER

using namespace cimg_library;
using namespace std;


class BWImage {
  private:
    // we will be using unsigned int all the time because the parameters of the CImg class use it,
    // and also because the coordinates and pixel intensity of a picture are positive numbers.
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
    void translation(int a, int b);
    void rotation(float theta, unsigned int x0, unsigned int y0);
    void rotation_and_fill(float theta, unsigned int x0, unsigned int y0);
    void display();
    void display_i();
    void display_f();
    unsigned int height();
    unsigned int width();
    void isotropic1(unsigned int x, unsigned int y);
    void isotropic2(unsigned int x, unsigned int y);
    void isotropic3(unsigned int x, unsigned int y);
    void anisotropic1(unsigned int x, unsigned int y);

};

#endif
