
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
//using namespace Eigen;


class BWImage {
  friend float optimize(BWImage img1, BWImage img2);
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
    void rotation(float theta, unsigned int x0, unsigned int y0); // simple rotation
    void rotation2(float theta, unsigned int x0, unsigned int y0); // rotation + filling of the lost information
    void rotation3(float theta, unsigned int x0, unsigned int y0); // optimized rotation to minimize the lost of information
    void inverse_rotation(float theta, unsigned int x0, unsigned int y0);
    unsigned int bilinear_interpolation(Coord p1, Coord p2, Coord p3, Coord p4, unsigned int intensity1,
      unsigned int intensity2, unsigned int intensity3, unsigned int intensity4);
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
