#include <cstdlib>
#include <iostream>
#include <math.h>

#ifndef COORD_H
#define COORD_H

#define PI 3.14159265358979323846

using namespace std;

class Coord {
  private:
    unsigned int x;
    unsigned int y;
  public:
    Coord(unsigned int x, unsigned int y);
    unsigned int getX();
    unsigned int getY();
    void setX(unsigned int a);
    void setY(unsigned int b);
    void display();
    void translation(int a, int b);
    void rotation(float theta, unsigned int x0, unsigned int y0);
    void inverse_rotation(float theta, unsigned int x0, unsigned int y0);
};

#endif
