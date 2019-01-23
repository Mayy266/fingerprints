#include <cstdlib>
#include <iostream>
#include <math.h>

#ifndef COORD_H
#define COORD_H

#define PI 3.14159265358979323846264338327950
#define EPSILON 0.0001

using namespace std;

class Coord {
  private:
    float x;
    float y;
  public:
    Coord();
    Coord(float x, float y);
    Coord(unsigned int x, unsigned int y);
    unsigned int getX();
    unsigned int getY();
    float getX_f();
    float getY_f();
    void setX(float a);
    void setY(float b);
    void display();
    void translation(int a, int b);
    void rotation(float theta, unsigned int x0, unsigned int y0);
    void inverse_rotation(float theta, unsigned int x0, unsigned int y0);
};

#endif
