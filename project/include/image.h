#include <cstdlib>
#include <iostream>
#include <string>
#include <cmath>
//#include <Eigen/Dense>
#include <vector>
#include "CImg.h"
#include "coord.h"


#ifndef IMAGE_H
#define IMAGE_H

using namespace cimg_library;
using namespace std;


class BWImage {
  friend float optimize(BWImage img1, BWImage img2);
  private:
    // we will be using unsigned int all the time because the parameters of the CImg class use it,
    // and also because the coordinates and pixel intensity of a picture are positive numbers.
    CImg<unsigned char> image;
    unsigned int hght;
    unsigned int wdth;
  public:
    BWImage(CImg<unsigned char> image); //constructor
    float toFloat(unsigned int x, unsigned int y);
    unsigned int maxIntensity();
    unsigned int minIntensity();
    void drawRect(unsigned int x, unsigned int y, unsigned int h, unsigned int w, unsigned int color);
    void symmetry_X();
    void symmetry_Y();
    void symmetry_diagonal();
    void translation(int a, int b);
    void rotation(float theta, unsigned int x0, unsigned int y0);
    void inverse_rotation(float theta, unsigned int x0, unsigned int y0);
    void rotation_and_fill(float theta, unsigned int x0, unsigned int y0);
    void display();
    void display_i();
    void display_f();
    unsigned int height();
    unsigned int width();
    void isotropic1(unsigned int x, unsigned int y);
    void isotropic2(unsigned int x, unsigned int y);
    void isotropic3(unsigned int x, unsigned int y);
    void isotropicGauss(unsigned int x, unsigned int y, float alpha);
    void anisotropic(unsigned int x, unsigned int y, float a, float b);
    void anisotropic2(unsigned int x, unsigned int y, float a, float b);
    void anisotropicGauss(unsigned int x, unsigned int y, float a, float b, float alpha);

};

#endif
