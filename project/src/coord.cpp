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

  if(x == 126 && y == 136){
    cout << "theta : " << theta << endl;
    cout << "cos(theta) : " << cos(theta) << endl;
    cout << "sin(theta) : " << sin(theta) << endl;
    cout << "x1 (input) : " << x1 << endl;
    cout << "y1 (input) : " << y1 << endl;
    cout << "x0 : " << x0 << endl;
    cout << "y0 : " << y0 << endl;
    cout << "x (output) : " << x << endl;
    cout << "y (output) : " << y << endl;
    cout << "(x1-x0) : " << ((float)x1-(float)x0) << endl;
    cout << "(y1-y0) : " << ((float)y1-(float)y0) << endl;
    cout << "(x1 - x0 + sin(theta)*(y1-y0) )/cos(theta) : " << ((float)x1-(float)x0 + sin(theta)*((float)y1-(float)y0))/cos(theta) << endl;
    cout << "(y1 - y0 - sin(theta)*(x1-x0) )/cos(theta) : " << ((float)y1-(float)y0 - sin(theta)*((float)x1-(float)x0))/cos(theta) << endl;
  }
}

void Coord::inverse_rotation(float theta, unsigned int x0, unsigned int y0){
  unsigned int x1 = x;
  unsigned int y1 = y;

  if(cos(theta)==0){
    x = (unsigned int)((float)x0 + (float)y1 - (float)y0 );
    y = (unsigned int)((float)x0 + (float)y0 - (float)x1 );
  }
  else{
    x = (unsigned int)((float)x0 + ( (float)x1 - (float)x0 + sin(theta)*((float)y1-(float)y0) )/cos(theta));
    y = (unsigned int)((float)y0 + ( (float)y1 - (float)y0 - sin(theta)*((float)x1-(float)x0) )/cos(theta));
  }


  if(x == x0-11 && y ==y0-10){
    cout << "--------------------------------" << endl;
    cout << "theta : " << theta << endl;
    cout << "cos(theta) : " << cos(theta) << endl;
    cout << "sin(theta) : " << sin(theta) << endl;
    cout << "x1 (intput) : " << x1 << endl;
    cout << "y1 (intput) : " << y1 << endl;
    cout << "x0 : " << x0 << endl;
    cout << "y0 : " << y0 << endl;
    cout << "x (output) : " << x << endl;
    cout << "y (output) : " << y << endl;
    cout << "(x1-x0) : " << ((float)x1-(float)x0) << endl;
    cout << "(y1-y0) : " << ((float)y1-(float)y0) << endl;
    cout << "(x1 - x0 + sin(theta)*(y1-y0) )/cos(theta) : " << ((float)x1-(float)x0 + sin(theta)*((float)y1-(float)y0))/cos(theta) << endl;
    cout << "(y1 - y0 - sin(theta)*(x1-x0) )/cos(theta) : " << ((float)y1-(float)y0 - sin(theta)*((float)x1-(float)x0))/cos(theta) << endl;
  }

}
