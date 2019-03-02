#include "coord.h"

Coord::Coord() : x(0), y(0) {}
Coord::Coord(float x, float y) : x(x), y(y) {}
Coord::Coord(unsigned int x, unsigned int y) : x((float)x), y((float)y) {}

/**
 * \fn unsigned int Coord::getX() const
 * \brief Function to get the x value of the coordinate as an unsigned int.
 * \return the x value of the coordinate as an unsigned int.
 */
unsigned int Coord::getX() const { return (unsigned int)round(x); }

/**
 * \fn unsigned int Coord::getY() const
 * \brief Function to get the y value of the coordinate as an unsigned int.
 * \return the y value of the coordinate as an unsigned int.
 */
unsigned int Coord::getY() const { return (unsigned int)round(y); }

/**
 * \fn unsigned int Coord::getX_f() const
 * \brief Function to get the exact x value of the coordinate.
 * \return the exact x value of the coordinate.
 */
float Coord::getX_f() const { return x; }

/**
 * \fn unsigned int Coord::getY_f() const
 * \brief Function to get the exact y value of the coordinate.
 * \return the exact y value of the coordinate.
 */
float Coord::getY_f() const { return y; }

/**
 * \fn void Coord::setX(float a)
 * \brief Function to set the x value of the coordinate.
 * \param a the new x value.
 */
void Coord::setX(float a){ x = a; }

/**
 * \fn void Coord::setY(float b)
 * \brief Function to set the y value of the coordinate.
 * \param b the new y value.
 */
void Coord::setY(float b){ y = b; }

/**
 * \fn void Coord::display()
 * \brief Function to display the coordinate.
 */
void Coord::display() const { std::cout << "(" << x << ", " << y << ")" << std::endl; }

/**
 * \fn void Coord::translation(float a, float b)
 * \brief Function to apply a translation of the coordinate.
 * \param a the translation on the x-axis.
 * \param b the translation on the y-axis.
 */
void Coord::translation(float a, float b){
  x = x + a;
  y = y + b;
}

/**
 * \fn void Coord::rotation(float theta, unsigned int x0, unsigned int y0)
 * \brief Function to rotates the coordinates around the point (x0,y0) with an angle theta.
 * \param theta the rotation angle.
 * \param x0 the x-axis coordinate of the point around which we rotate.
 * \param y0 the y-axis coordinate of the point around which we rotate.
 */
void Coord::rotation(float theta, unsigned int x0, unsigned int y0){
  float x1 = x;
  float y1 = y;

  x = cos(theta) * (x1-(float)x0) + sin(theta) * (y1-(float)y0) + (float)x0;
  y = -sin(theta) * (x1-(float)x0) + cos(theta) * (y1-(float)y0) + (float)y0;
}

/**
 * \fn void Coord::inverse_rotation(float theta, unsigned int x0, unsigned int y0)
 * \brief Function to apply the inverse rotation of the coordinates around the point (x0,y0) with an angle theta.
 * \param theta the rotation angle.
 * \param x0 the x-axis coordinate of the point around which we rotate.
 * \param y0 the y-axis coordinate of the point around which we rotate.
 */
void Coord::inverse_rotation(float theta, unsigned int x0, unsigned int y0){
  float x1 = x;
  float y1 = y;

  x = (float)x0 + (x1-(float)x0)*cos(theta) -  (y1-(float)y0)*sin(theta);
  y = (float)y0 + (y1-(float)y0)*cos(theta) +  (x1-(float)x0)*sin(theta);
}
