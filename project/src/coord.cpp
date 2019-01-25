#include "coord.h"

Coord::Coord() : x(0), y(0) {}
Coord::Coord(float x, float y) : x(x), y(y) {}
Coord::Coord(unsigned int x, unsigned int y) : x((float)x), y((float)y) {}
unsigned int Coord::getX(){ return (unsigned int)round(x); }
unsigned int Coord::getY(){ return (unsigned int)round(y); }
float Coord::getX_f(){ return x; }
float Coord::getY_f(){ return y; }
void Coord::setX(float a){ x = a; }
void Coord::setY(float b){ y = b; }
void Coord::display(){ cout << "(" << x << ", " << y << ")" << endl; }
//translation
void Coord::translation(float a, float b){
  x = x + a;
  y = y + b;
}

//rotates the coordinates around the point (x0,y0) with an angle theta
void Coord::rotation(float theta, unsigned int x0, unsigned int y0){
  float x1 = x;
  float y1 = y;

  x = cos(theta) * (x1-(float)x0) + sin(theta) * (y1-(float)y0) + (float)x0;
  y = -sin(theta) * (x1-(float)x0) + cos(theta) * (y1-(float)y0) + (float)y0;
}

//rotates the coordinates around the point (x0,y0) using the inverse rotation function
void Coord::inverse_rotation(float theta, unsigned int x0, unsigned int y0){
  float x1 = x;
  float y1 = y;

  x = (float)x0 + (x1-(float)x0)*cos(theta) -  (y1-(float)y0)*sin(theta);
  y = (float)y0 + (y1-(float)y0)*cos(theta) +  (x1-(float)x0)*sin(theta);
}
