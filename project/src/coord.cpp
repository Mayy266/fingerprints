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
//return -1 if one of the coordinates is negative (in this case, the coordinates aren't modified), 1 else.
void Coord::rotation(float theta, unsigned int x0, unsigned int y0){
  unsigned int x1 = x;
  unsigned int y1 = y;
  x = (unsigned int)(cos(theta) * ((float)x1-(float)x0) - sin(theta) * ((float)y1-(float)y0) + (float)x0);
  y = (unsigned int)(sin(theta) * ((float)x1-(float)x0) + cos(theta) * ((float)y1-(float)y0) + (float)y0);

  // if((cos(theta) * ((int)x1-(int)x0) - sin(theta) * ((int)y1-(int)y0) + (int)x0) < 0){
  //   return -1;
  // }
  // if((sin(theta) * ((int)x1-(int)x0) + cos(theta) * ((int)y1-(int)y0) + (int)y0) < 0){
  //   return -1;
  // }

  // if(x == x0-10 && y == y0-10){
  //   cout << "theta : " << theta << endl;
  //   cout << "cos(theta) : " << cos(theta) << endl;
  //   cout << "sin(theta) : " << sin(theta) << endl;
  //   cout << "x1 : " << x1 << endl;
  //   cout << "y1 : " << y1 << endl;
  //   cout << "x0 : " << x0 << endl;
  //   cout << "y0 : " << y0 << endl;
  //   cout << "x : " << x << endl;
  //   cout << "y : " << y << endl;
  //   cout << "(x1-x0) : " << (x1-x0) << endl;
  //   cout << "(y1-y0) : " << (y1-y0) << endl;
  //   cout << "cos(theta) * (x1-x0) : " << cos(theta) * (x1-x0) << endl;
  //   cout << "sin(theta) * (y1-y0) : " << sin(theta) * (y1-y0) << endl;
  // }
}
