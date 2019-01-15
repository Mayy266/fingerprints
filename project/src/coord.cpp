#include "coord.h"

Coord::Coord(unsigned int x, unsigned int y) : x(x), y(y) {}
unsigned int Coord::getX(){ return x; }
unsigned int Coord::getY(){ return y; }
void Coord::setX(unsigned int a){ x = a; }
void Coord::setY(unsigned int b){ y = b; }
void Coord::display(){ cout << "(" << x << ", " << y << ")" << endl; }
//translation
void Coord::translation(int a, int b){
  x = (unsigned int)((int)x+a);
  y = (unsigned int)((int)y+b);
}

//rotates the coordinates around the point (x0,y0) with an angle theta
void Coord::rotation(float theta, unsigned int x0, unsigned int y0){
  unsigned int x1 = x;
  unsigned int y1 = y;

  x = (unsigned int)(cos(theta) * ((float)x1-(float)x0) - sin(theta) * ((float)y1-(float)y0) + (float)x0);
  y = (unsigned int)(sin(theta) * ((float)x1-(float)x0) + cos(theta) * ((float)y1-(float)y0) + (float)y0);
}


void Coord::inverse_rotation(float theta, unsigned int x0, unsigned int y0){
  unsigned int x1 = x;
  unsigned int y1 = y;

  x = (unsigned int)round((float)x0 + ((float)x1-(float)x0)*cos(theta) -  ((float)y1-(float)y0)*sin(theta));
  y = (unsigned int)round((float)y0 + ((float)y1-(float)y0)*cos(theta) +  ((float)x1-(float)x0)*sin(theta));
}
