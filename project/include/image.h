
#include <cstdlib>
#include <iostream>
#include <string>
#include <cmath>
#include <Eigen/Dense>
#include <vector>
#include <cassert>
#include "CImg.h"
#include "coord.h"

#ifndef IMAGE_H
#define IMAGE_H

class BWImage {
  private:
    // we will be using unsigned int all the time because the parameters of the CImg class use it,
    // and also because the coordinates and pixel intensity of a picture are positive numbers.
    cimg_library::CImg<unsigned char> image;
    unsigned int hght;
    unsigned int wdth;
  public:
    BWImage(cimg_library::CImg<unsigned char> image);
    BWImage(const BWImage& img);
    float toFloat(unsigned int x, unsigned int y) const;
    void save(std::string path) const;
    int getIntensity(unsigned int x, unsigned int y) const;
    void setIntensity(unsigned int x, unsigned int y, unsigned int newIntensity);
    unsigned int height() const;
    unsigned int width() const;
    unsigned int maxIntensity() const;
    unsigned int minIntensity() const;
    void drawRect(unsigned int x, unsigned int y, unsigned int h, unsigned int w, unsigned int color);
    void symmetry_X();
    void symmetry_Y();
    void symmetry_diagonal();
    void translation(int a, int b);
    void translation_f(float a, float b);
    void rotation(float theta, unsigned int x0, unsigned int y0); // simple rotation
    void rotation2(float theta, unsigned int x0, unsigned int y0); // optimized rotation to minimize the lost of information
    void rotation3(float theta, unsigned int x0, unsigned int y0); // rotation + filling of the lost information
    void inverse_rotation(float theta, unsigned int x0, unsigned int y0);
    unsigned int bilinear_interpolation(Coord p1, Coord p2, Coord p3, Coord p4, unsigned int intensity1, unsigned int intensity2, unsigned int intensity3, unsigned int intensity4) const;
    unsigned int bilinear_interpolation2(Coord c, Coord p1, Coord p2, unsigned int value1, unsigned int value2, unsigned int value3, unsigned int value4) const;
    void local_rotation(float theta, unsigned int x0, unsigned int y0, float dist_max, float m);
    void display() const;
    void isotropic1(unsigned int x, unsigned int y);
    void isotropic2(unsigned int x, unsigned int y);
    void isotropic3(unsigned int x, unsigned int y);
    void isotropicGauss(unsigned int x, unsigned int y, float alpha);
    void anisotropic(unsigned int x, unsigned int y, float a, float b);
    void anisotropic2(unsigned int x, unsigned int y, float a, float b);
    void anisotropicGauss(unsigned int x, unsigned int y, float a, float b, float alpha);

};
#endif
