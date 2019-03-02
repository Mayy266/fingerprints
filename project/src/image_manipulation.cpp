#include "image.h"
#include "externalFunctions.h"
using namespace cimg_library;
using namespace std;
using namespace Eigen;

//constuctor
BWImage::BWImage(CImg<unsigned char> img):image(img){
  image.channel(0);
  wdth = (unsigned int)image.width();
  hght = (unsigned int)image.height();
}

// copy constructor
BWImage::BWImage(const BWImage& img){
  image = cimg_library::CImg<unsigned char>(img.image);
  wdth = img.width();
  hght = img.height();
}

void BWImage::save(std::string path) const {
  image.save(path.c_str());
}

/**
 * \fn float BWImage::toFloat(unsigned int x, unsigned int y) const
 * \brief Conversion to float of the intensity of the pixels.
 * \param theta the rotation angle.
 * \param x the x-axis coordinate of the point.
 * \param y the y-axis coordinate of the point.
 * \return the intensity of the pixel at the given coordinates, as a float (between 0 and 1).
 */
float BWImage::toFloat(unsigned int x, unsigned int y) const {
  return (float)(image(x,y,0,0)/255.0);
}

/**
 * \fn int BWImage::getIntensity(unsigned int x, unsigned int y) const
 * \brief Gives the pixel's intensity at a given point.
 * \param x the x-axis coordinate of the point.
 * \param y the y-axis coordinate of the point.
 * \return the pixel's intensity at a given point as an integer (between 0 and 255).
 */
int BWImage::getIntensity(unsigned int x, unsigned int y) const {
  return image(x,y,0,0);
}

/**
 * \fn void BWImage::setIntensity(unsigned int x, unsigned int y, unsigned int newIntensity)
 * \brief Changes the pixel's intensity at a given point.
 * \param x the x-axis coordinate of the point.
 * \param y the y-axis coordinate of the point.
 */
void BWImage::setIntensity(unsigned int x, unsigned int y, unsigned int newIntensity) {
  image(x,y,0,0) = newIntensity;
}

/**
 * \fn unsigned int BWImage::maxIntensity() const
 * \brief Finds the maximum intensity of the pixels of the image.
 * \return the maximum intensity of the pixels.
 */
unsigned int BWImage::maxIntensity() const {
  unsigned int max = 0;
  for(unsigned int i = 0; i<wdth; i++){
    for(unsigned int j = 0; j<hght; j++){
      if(image(i,j,0,0) > max){
        max = image(i,j,0,0);
      }
    }
  }
  return max;
}

/**
 * \fn unsigned int BWImage::minIntensity() const
 * \brief Finds the minimum intensity of the pixels of the image.
 * \return the minimum intensity of the pixels.
 */
unsigned int BWImage::minIntensity() const {
  unsigned int min = 256;
  for(unsigned int i = 0; i<wdth; i++){
    for(unsigned int j = 0; j<hght; j++){
      if(image(i,j,0,0) < min){
        min = image(i,j,0,0);
      }
    }
  }
  return min;
}


/**
 * \fn unsigned int BWImage::height() const
 * \return the height of the image.
 */
unsigned int BWImage::height() const {
  return hght;
}

/**
 * \fn unsigned int BWImage::width() const
 * \return the width of the image.
 */
unsigned int BWImage::width() const {
  return wdth;
}


/**
 * \fn void BWImage::drawRect(unsigned int x, unsigned int y, unsigned int h, unsigned int w, unsigned int color)
 * \brief Draws rectangles on the picture.
 * \param x the x-axis coordinate of the starting point.
 * \param y the y-axis coordinate of the starting point.
 * \param h the height of the rectangle.
 * \param w the width of the rectangle.
 * \param color the color of the rectangle (an integer between 0-black and 255-white).
 */
void BWImage::drawRect(unsigned int x, unsigned int y, unsigned int h, unsigned int w, unsigned int color){
  for(unsigned int i = x; i < x+w; i++){
      for(unsigned int j = y; j < y+h; j++){
        image(i,j,0,0) = color;
      }
    }
    image.save("../project/output_images/output_rect.png"); //saves the new image
}

//symmetry along the Y axis

/**
 * \fn void BWImage::symmetry_Y()
 * \brief Performs symmetry of the image along the y-axis.
 */
void BWImage::symmetry_Y(){
  unsigned int w = (wdth%2 == 1 ? wdth - 1 : wdth); //checks wether the width of the image is even or odd
  for (unsigned int y = 0; y < hght; y++){
    for (unsigned int x = 0; x < (unsigned int)(w/2); x++){
      unsigned int tmp = image(x,y,0,0);
      image(x,y,0,0) = image(wdth-x-1,y,0,0);
      image(wdth-x-1,y,0,0) = tmp;
    }
  }
  image.save("../project/output_images/output_symmetry_Y.png"); //saves the new image
}


/**
 * \fn void BWImage::symmetry_X()
 * \brief Performs symmetry of the image along the x-axis.
 */
void BWImage::symmetry_X(){
  unsigned int h = (hght%2 == 1 ? hght - 1 : hght); ////checks wether the height of the image is even or odd
  for (unsigned int y = 0; y < (unsigned int)(h/2); y++){
    for (unsigned int x = 0; x < wdth; x++){
      unsigned int tmp = image(x,y,0,0);
      image(x,y,0,0) = image(x,hght-y-1,0,0);
      image(x,hght-y-1,0,0) = tmp;
    }
  }
  image.save("../project/output_images/output_symmetry_X.png"); //saves the new image
}

/**
 * \fn void BWImage::symmetry_diagonal()
 * \brief Performs symmetry of the image along the diagonal-axis.
 */
void BWImage::symmetry_diagonal(){
  unsigned int h = (hght%2 == 1 ? hght - 1 : hght); //checks wether the height of the image is even or odd
  for (unsigned int y = hght-wdth; y < h; y++){
    for (unsigned int x = 0; x < (unsigned int)(y-(hght-wdth)); x++){
      unsigned int tmp = image(x,y,0,0);
      image(x,y,0,0) = image(y-(hght-wdth),x+(hght-wdth),0,0);
      image(y-(hght-wdth),x+(hght-wdth),0,0) = tmp; //we crop the image so its width and height are the same, then we perform the symmetry
    }
  }
  drawRect(0, 0, hght-wdth, wdth, 255); //it sets the top part of the image to white
  image.save("../project/output_images/output_symmetry_diag.png"); //saves the new image
}

/**
 * \fn void BWImage::translation(int a, int b)
 * \brief Performs a translation of the image given the parameters.
 * \param a the translation parameter along the x-axis.
 * \param b the translation parameter along the y-axis.
 */
void BWImage::translation(int a, int b){
    //initializes a temporary matrix, used to do the rotation
    Eigen::MatrixXf tmpPict(wdth, hght);


    for (unsigned int i = 0; i < wdth; i++){
      for (unsigned int j = 0; j < hght; j++){
        tmpPict(i, j) = 255; //fill cut part with white
      }
    }

    for (unsigned int y = 0; y < hght; y++){
      for (unsigned int x = 0; x < wdth; x++){
        Coord c = Coord(x,y);
        c.translation(a, b);
        if(c.getX()<wdth && c.getY()<hght){
          tmpPict(c.getX(), c.getY()) = image(x,y,0,0);
        }
      }
    }

    for (unsigned int i = 0; i < wdth; i++){
      for (unsigned int j = 0; j < hght; j++){
        image(i,j,0,0) = tmpPict(i, j);
      }
    }

    // image.save("../project/output_images/output_translation.png"); //saves the new image
}

/**
 * \fn void BWImage::translation_f(float a, float b)
 * \brief Performs a translation of the image given the parameters.
 * \param a the translation parameter along the x-axis.
 * \param b the translation parameter along the y-axis.
 */
void BWImage::translation_f(float a, float b){
    //initializes a temporary matrix, used to do the rotation
    Eigen::MatrixXf tmpPict(wdth, hght);
    for (unsigned int x = 0; x < wdth; x++){
      for (unsigned int y = 0; y < hght; y++){
        Coord c = Coord(x,y);
        c.translation(-a,-b); //computes the coordinates in the starting picture of the pixel (x,y) of the rotated picture.
        if(c.getX_f()<0 || c.getX_f()>=wdth-1 || c.getY_f()<0 || c.getY_f()>=hght-1){tmpPict(x, y) = 255;} // if we are outside the boundaries of the starting picture, we put a white pixel
        else{
          //find 4 close enough neighboors of the pixel in the starting picture.
          // 1. coordinates :
          Coord cp1 = Coord(std::floor(c.getX_f()), std::floor(c.getY_f()));
          Coord cp2 = Coord(std::floor(c.getX_f()), std::ceil(c.getY_f()));
          Coord cp3 = Coord(std::ceil(c.getX_f()), std::floor(c.getY_f()));
          Coord cp4 = Coord(std::ceil(c.getX_f()), std::ceil(c.getY_f()));

          float deltaX = abs(c.getX_f()-c.getX());
          float deltaY = abs(c.getY_f()-c.getY());

          // if the x and y inverse coordinates aren't both integers (ie : we need to interpolate) :
          if(deltaX > EPSILON || deltaY > EPSILON){
            // if the ceil value of x is equal to the floor value of x (it's a problem to interpolate) :
            if(deltaX < EPSILON){
              // if the ceil value is smaller than the width, we increment the ceil value
              if(std::ceil(c.getX_f()) < wdth-1){
                cp3 = Coord(std::ceil(c.getX_f())+1, std::floor(c.getY_f()));
                cp4 = Coord(std::ceil(c.getX_f())+1, std::ceil(c.getY_f()));
              }
              // else we decrement the floor value
              else{
                cp1 = Coord(std::floor(c.getX_f())-1, std::floor(c.getY_f()));
                cp2 = Coord(std::floor(c.getX_f())-1, std::ceil(c.getY_f()));
              }
            }
            // else if the ceil value of y is equal to the floor value of y (it's a problem to interpolate) :
            else if(deltaY < EPSILON){
              // if the ceil value is smaller than the height, we increment the ceil value
              if(std::ceil(c.getY_f()) < hght-1){
                cp2 = Coord(std::floor(c.getX_f()), std::ceil(c.getY_f())+1);
                cp4 = Coord(std::ceil(c.getX_f()), std::ceil(c.getY_f())+1);
              }
              // else we decrement the floor value
              else if(std::ceil(c.getY_f()) >= hght-1){
                cp1 = Coord(std::floor(c.getX_f()), std::floor(c.getY_f())-1);
                cp3 = Coord(std::ceil(c.getX_f()), std::floor(c.getY_f())-1);

              }
            }

            // 2. pixels intensity values :
            unsigned int p1 = image(cp1.getX(),cp1.getY(),0,0);
            unsigned int p2 = image(cp2.getX(),cp2.getY(),0,0);
            unsigned int p3 = image(cp3.getX(),cp3.getY(),0,0);
            unsigned int p4 = image(cp4.getX(),cp4.getY(),0,0);

            tmpPict(x, y) = bilinear_interpolation2(c, cp1, cp4, p1, p2, p3, p4);
          }
          // else, if the x and y inverse coordinatesare both integers, we don't need to interpolate :
          else{
            tmpPict(x, y) = image(c.getX(), c.getY(), 0, 0);
          }
        }
      }
    }
    for (unsigned int i = 0; i < wdth; i++){
      for (unsigned int j = 0; j < hght; j++){
        image(i,j,0,0) = tmpPict(i, j);//we copy the values of the matrix into the initial image
      }
    }

    // image.save("../project/output_images/output_translation_f.png"); //saves the new image
}


/**
 * \fn void BWImage::rotation(float theta, unsigned int x0, unsigned int y0)
 * \brief Performs a rotation of the image given the rotation angle and rotation center.
 * \param theta the rotation angle.
 * \param x0 the x coordinate of the rotation center.
 * \param y0 the y coordinate of the rotation center.
 */
void BWImage::rotation(float theta, unsigned int x0, unsigned int y0){

  //initializes a temporary matrix, used to do the rotation
  Eigen::MatrixXf tmpPict(wdth, hght);

  for (unsigned int i = 0; i < wdth; i++){
    for (unsigned int j = 0; j < hght; j++){
      tmpPict(i, j) = 255;
    }
  }
  for (unsigned int y = 0; y < hght; y++){
    for (unsigned int x = 0; x < wdth; x++){
      Coord c = Coord(x,y);
      c.rotation(theta, x0, y0);//uses the rotation function to rotate the coordinates
      if(c.getX()<wdth && c.getY()<hght){
        tmpPict(c.getX(), c.getY()) = image(x,y,0,0);//fills the matrix wih the intensity values of the image
      }
    }
  }

  for (unsigned int i = 0; i < wdth; i++){
    for (unsigned int j = 0; j < hght; j++){
      image(i,j,0,0) = tmpPict(i, j);//we copy the values of the matrix into the initial image
    }
  }

//  image.save("bin/outputs/output_rotation.png"); //saves the new image
   //image.save("../project/output_images/output_rotation.png");
   image.display();
}


/**
 * \fn void BWImage::inverse_rotation(float theta, unsigned int x0, unsigned int y0)
 * \brief Performs an inverse rotation of the image given the rotation angle and rotation center.
 * \param theta the rotation angle.
 * \param x0 the x coordinate of the rotation center.
 * \param y0 the y coordinate of the rotation center.
 */
void BWImage::inverse_rotation(float theta, unsigned int x0, unsigned int y0){

  //we create a new matrix
  Eigen::MatrixXf tmpPict(wdth, hght);

  for (unsigned int i = 0; i < wdth; i++){
    for (unsigned int j = 0; j < hght; j++){
      tmpPict(i, j) = 255;
    }
  }
  for (unsigned int y = 0; y < hght; y++){
    for (unsigned int x = 0; x < wdth; x++){
      Coord c = Coord(x,y);
      c.inverse_rotation(theta, x0, y0); //uses the inverse function of rotation to rotate the coordinates
      if(c.getX()<wdth && c.getY()<hght){
        tmpPict(c.getX(), c.getY()) = image(x,y,0,0);//fills the matrix wih the intensity values of the image
      }
    }
  }

  for (unsigned int i = 0; i < wdth; i++){
    for (unsigned int j = 0; j < hght; j++){
      image(i,j,0,0) = tmpPict(i, j); //we copy the values of the matrix into the initial image
    }
  }

  //image.save("bin/outputs/output_inverse_rotation.png"); //saves the new image
  image.save("../project/output_images/output_inverse_rotation.png");
}



/**
 * \fn void BWImage::rotation2(float theta, unsigned int x0, unsigned int y0)
 * \brief Performs a rotation of the image given the rotation angle and rotation center. Method :
 * 1. compute the coordinates of the rotated picture in the starting picture using inverse rotation function (coordinates as floats)
 * 2. compute the pixel intensity value of the pixel in the rotated picture using bilinear interpolation with the 4 nearest pixels in the starting picture.
 * \param theta the rotation angle.
 * \param x0 the x coordinate of the rotation center.
 * \param y0 the y coordinate of the rotation center.
 */
void BWImage::rotation2(float theta, unsigned int x0, unsigned int y0){

  //initializes a temporary matrix, used to do the rotation
  // unsigned int** tmpPict = new unsigned int*[wdth]; //we create a temporary matrix
  Eigen::MatrixXf tmpPict(wdth, hght);

  for (unsigned int x = 0; x < wdth; x++){
    for (unsigned int y = 0; y < hght; y++){
      Coord c = Coord(x,y);
      c.inverse_rotation(theta, x0, y0); //computes the coordinates in the starting picture of the pixel (x,y) of the rotated picture.
      if(c.getX_f()<0 || c.getX_f()>=wdth-1 || c.getY_f()<0 || c.getY_f()>=hght-1){tmpPict(x, y) = 255;} // if we are outside the boundaries of the starting picture, we put a black pixel
      else{
        //find 4 close enough neighboors of the pixel in the starting picture.
        // 1. coordinates :
        Coord cp1 = Coord(std::floor(c.getX_f()), std::floor(c.getY_f()));
        Coord cp2 = Coord(std::floor(c.getX_f()), std::ceil(c.getY_f()));
        Coord cp3 = Coord(std::ceil(c.getX_f()), std::floor(c.getY_f()));
        Coord cp4 = Coord(std::ceil(c.getX_f()), std::ceil(c.getY_f()));

        float deltaX = abs(c.getX_f()-c.getX());
        float deltaY = abs(c.getY_f()-c.getY());

        // if the x and y inverse coordinates aren't both integers (ie : we need to interpolate) :
        if(deltaX > EPSILON || deltaY > EPSILON){
          // if the ceil value of x is equal to the floor value of x (it's a problem to interpolate) :
          if(deltaX < EPSILON){
            // if the ceil value is smaller than the width, we increment the ceil value
            if(std::ceil(c.getX_f()) < wdth-1){
              cp3 = Coord(std::ceil(c.getX_f())+1, std::floor(c.getY_f()));
              cp4 = Coord(std::ceil(c.getX_f())+1, std::ceil(c.getY_f()));
            }
            // else we decrement the floor value
            else{
              cp1 = Coord(std::floor(c.getX_f())-1, std::floor(c.getY_f()));
              cp2 = Coord(std::floor(c.getX_f())-1, std::ceil(c.getY_f()));
            }
          }
          // else if the ceil value of y is equal to the floor value of y (it's a problem to interpolate) :
          else if(deltaY < EPSILON){
            // if the ceil value is smaller than the height, we increment the ceil value
            if(std::ceil(c.getY_f()) < hght-1){
              cp2 = Coord(std::floor(c.getX_f()), std::ceil(c.getY_f())+1);
              cp4 = Coord(std::ceil(c.getX_f()), std::ceil(c.getY_f())+1);
            }
            // else we decrement the floor value
            else if(std::ceil(c.getY_f()) >= hght-1){
              cp1 = Coord(std::floor(c.getX_f()), std::floor(c.getY_f())-1);
              cp3 = Coord(std::ceil(c.getX_f()), std::floor(c.getY_f())-1);

            }
          }

          // 2. pixels intensity values :
          unsigned int p1 = image(cp1.getX(),cp1.getY(),0,0);
          unsigned int p2 = image(cp2.getX(),cp2.getY(),0,0);
          unsigned int p3 = image(cp3.getX(),cp3.getY(),0,0);
          unsigned int p4 = image(cp4.getX(),cp4.getY(),0,0);

          tmpPict(x, y) = bilinear_interpolation2(c, cp1, cp4, p1, p2, p3, p4);
        }
        // else, if the x and y inverse coordinatesare both integers, we don't need to interpolate :
        else{
          tmpPict(x, y) = image(c.getX(), c.getY(), 0, 0);
        }
      }
    }
  }


  for (unsigned int i = 0; i < wdth; i++){
    for (unsigned int j = 0; j < hght; j++){
      image(i,j,0,0) = tmpPict(i, j);//we copy the values of the matrix into the initial image
    }
  }
  // image.save("../project/output_images/output_rotation2.png"); //saves the new image
}


/**
 * \fn void BWImage::rotation3(float theta, unsigned int x0, unsigned int y0)
 * \brief Performs a rotation of the image given the rotation angle and rotation center. Method :
 * 1. apply the rotation on each pixels' coordinates (during this step, we lose information because we get floating values,  and we cast them as integers tu use them as coordinates).
 * 2. fill the lost information using bilinear interpoation.
 * \param theta the rotation angle.
 * \param x0 the x coordinate of the rotation center.
 * \param y0 the y coordinate of the rotation center.
 */
void BWImage::rotation3(float theta, unsigned int x0, unsigned int y0){

  //initializes a temporary matrix, used to do the rotation
  Eigen::MatrixXf tmpPict(wdth, hght);

  // we fill it with -1 so that we know which pixels will not take an intensity value during the rotation
  for (unsigned int i = 0; i < wdth; i++){
    for (unsigned int j = 0; j < hght; j++){
      tmpPict(i, j) = -1;
    }
  }

  // we apply the rotation
  for (unsigned int y = 0; y < hght; y++){
    for (unsigned int x = 0; x < wdth; x++){
      Coord c = Coord(x,y);
      c.rotation(theta, x0, y0); //we rotate the coordinates
      if(c.getX()<wdth && c.getY()<hght){
        if(x == 0 || y == 0 || x==wdth-1 || y == hght-1){ // if we are on the borders
          tmpPict(c.getX(), c.getY()) = 256 + image(x,y,0,0); // we add 256, to save the information "it's a border"
        }
        else{
          tmpPict(c.getX(), c.getY()) = image(x,y,0,0); //we fill the temporary matrix with the rotated image
        }
      }
    }
  }

  // we fill the corners with white
  unsigned int corner_beginning, corner_ending;
  for (unsigned int i = 0; i < wdth; i++){
    corner_beginning = 0;
    corner_ending = 0;
    for (unsigned int j = 0; j < hght; j++){ // for each column, we fill the corner part with white :
      if(j==corner_beginning){
        corner_ending = corner_beginning;
        while(corner_ending<hght-1 && tmpPict(i, corner_ending)<256 && tmpPict(i, corner_ending)==-1){ // we check if we are in a corner
          corner_ending++;
        }
        if(tmpPict(i, corner_ending)!=-1  && tmpPict(i, corner_ending)<256){ // if we are not in a corner
          while(j<hght-1 && tmpPict(i, j)<256){ // we move until the next corner (or the end of the column)
            j++;
          }
        }
      }
      if(tmpPict(i, j) >= 256){ // if we are on a border, we remove the "+256" value we added before
        tmpPict(i, j) -= 256;
        corner_beginning = j+1;
      }
      else if(j>=corner_beginning && j<=corner_ending){ // if we are in a corner, we fill with white
        tmpPict(i, j) = 255;
      }
    }
  }

  unsigned int p1, p2, p3, p4 = 255;
  Coord cp1, cp2, cp3, cp4;
  unsigned int lim = 4; //we set the limit so we don't go to far from the pixel we want to interpolate
  for (unsigned int i = 0; i < wdth; i++){
    for (unsigned int j = 0; j < hght; j++){
        if(tmpPict(i, j) == -1){
          unsigned int l, k;

          // first loop (upper right corner) : (k, k-l-1)
          k = 0;
          while(k<lim){
            l = 0;
            while(l<lim && i+k<wdth && i+k>0 && j+k-l-1<hght && j+k-l-1>0 && tmpPict(i+k, j+k-l-1)==-1){ // border conditions, it detects the pixel which we want to use to interpolate
              l++;
            }
            if(l<lim && i+k<wdth && i+k>0 && j+k-l-1<hght && j+k-l-1>0){//border conditions, we go inside this loop only if we find a value != -1
              p1 = tmpPict(i+k, j+k-l-1);
              cp1.setX(i+k); //we save the coordinates of the points that we are using to interpolate
              cp1.setY(j+k-l-1); //so we can use them in the function 'interpolation'
              break;
            }
            k++;
          }
          // second loop (down right corner) : (l-k+1, l)
          k = 0;
          while(k<lim){
            l = 0;
            while(l<lim && i+l-k+1<wdth && i+l-k+1>0 && j+l<hght && j+l>0 && tmpPict(i+l-k+1, j+l)==-1){// border conditions, it detects the pixel which we want to use to interpolate
              l++;
            }
            if(l<lim && i+l-k+1<wdth && i+l-k+1>0 && j+l<hght && j+l>0){//border conditions, we go inside this loop only if we find a value != -1
              p2 = tmpPict(i+l-k+1, j+l);
              cp2.setX(i+l-k+1);//we save the coordinates of the points that we are using to interpolate
              cp2.setY(j+l);//so we can use them in the function 'interpolation'
              break;
            }
            k++;
          }

          // third loop (down left corner) : (k-l, k+1)
          k = 0;
          while(k<lim){
            l = 0;
            while(l<lim && i+k-l<wdth && i+k-l>0 && j+k+1<hght && j+k+1>0 && tmpPict(i+k-l, j+k+1)==-1){// border conditions, it detects the pixel which we want to use to interpolate
              l++;
            }
            if(l<lim && i+k-l<wdth && i+k-l>0 && j+k+1<hght && j+k+1>0){//border conditions, we go inside this loop only if we find a value != -1
              p3 = tmpPict(i+k-l, j+k+1);
              cp3.setX(i+k-l);//we save the coordinates of the points that we are using to interpolate
              cp3.setY(j+k+1);//so we can use them in the function 'interpolation'
              break;
            }
            k++;
          }
          // fourth loop (upper left corner) : (-l-1+k, -k)
          k = 0;
          while(k<lim){
            l = 0;
            while(l<lim && i-l-1+k<wdth && i-l-1+k>0 && j-k<hght && j-k>0 && tmpPict(i-l-1+k, j-k)==-1){// border conditions, it detects the pixel which we want to use to interpolate
              l++;
            }
            if(l<lim && i-l-1+k<wdth && i-l-1+k>0 && j-k<hght && j-k>0){//border conditions, we go inside this loop only if we find a value != -1
              p4 = tmpPict(i-l-1+k, j-k);
              cp4.setX(i-l-1+k);//we save the coordinates of the points that we are using to interpolate
              cp4.setY(j-k);//so we can use them in the function 'interpolation'
              break;
            }
            k++;
          }

          // we compute the bilinear interpolation with the four pixels :
          tmpPict(i, j) = bilinear_interpolation(cp1, cp2, cp3, cp4, p1, p2, p3, p4);
      }
    }
  }

  for (unsigned int i = 0; i < wdth; i++){
    for (unsigned int j = 0; j < hght; j++){
      image(i,j,0,0) = tmpPict(i, j);//we copy the values of the matrix into the initial image
    }
  }

  // image.save("../project/output_images/output_rotation3.png"); //saves the new image
}



/**
 * \fn unsigned int BWImage::bilinear_interpolation(Coord p1, Coord p2, Coord p3, Coord p4, unsigned int intensity1, unsigned int intensity2, unsigned int intensity3, unsigned int intensity4) const
 * \brief Performs a bilinear interpolation using 4 not aligned points.
 * \param p1 first point which we use to interpolate.
 * \param p2 second point which we use to interpolate.
 * \param p3 third point which we use to interpolate.
 * \param p4 fourth point which we use to interpolate.
 * \param intensity1 the pixel's intensity at p1.
 * \param intensity2 the pixel's intensity at p2.
 * \param intensity3 the pixel's intensity at p3.
 * \param intensity4 the pixel's intensity at p4.
 * \return the new intensity value.
 */
unsigned int BWImage::bilinear_interpolation(Coord p1, Coord p2, Coord p3, Coord p4,
  unsigned int intensity1, unsigned int intensity2, unsigned int intensity3, unsigned int intensity4) const {

  Coord center = Coord((float)((p1.getX_f()+p2.getX_f()+p3.getX_f()+p4.getX_f())/4.0), (float)((p1.getY_f()+p2.getY_f()+p3.getY_f()+p4.getY_f())/4.0)); //we compute the coordinates of the center of the 4 points

  float a = -p1.getX_f() + p3.getX_f();
  float b = -p1.getX_f() + p2.getX_f();
  float c = p1.getX_f() - p2.getX_f() - p3.getX_f() + p4.getX_f();
  float d = center.getX_f() - p1.getX_f();
  float e = -p1.getY_f() + p3.getY_f();
  float f = -p1.getY_f() + p2.getY_f();
  float g = p1.getY_f() - p2.getY_f() - p3.getY_f() + p4.getY_f();
  float h = center.getY_f() - p1.getY_f();

  // in case we encounter a division by 0, we set alpha to zero
  float alpha = (2*c*e - 2*a*g == 0 ? 0 : -(b*e - a*f + d*g - c*h + sqrt(-4*(c*e - a*g)*(d*f - b*h) + pow(b*e - a*f + d*g - c*h,2) ))/(2*c*e - 2*a*g));
  // in case we encounter a division by 0, we set beta to zero
  float beta  = (2*c*f - 2*b*g == 0 ? 0 :  (b*e - a*f - d*g + c*h + sqrt(-4*(c*e - a*g)*(d*f - b*h) + pow(b*e - a*f + d*g - c*h,2) ))/(2*c*f - 2*b*g));

  unsigned int newIntensity = (1.0 - alpha) * ((1.0 - beta) * (float)intensity1 + beta * (float)intensity2) + alpha * ((1.0 - beta) * (float)intensity3 + beta * (float)intensity4);
  if(newIntensity>255){ newIntensity = 255; }
  return newIntensity;
}

//is used in translation_f and local_rotation
/**
 * \fn unsigned int BWImage::bilinear_interpolation2(Coord c, Coord p1, Coord p2, unsigned int value1, unsigned int value2, unsigned int value3, unsigned int value4) const
 * \brief Performs a bilinear interpolation using 4 aligned points.
 * \param c the coordinates of the point which we want to interpolate.
 * \param p1 upper left point which we use to interpolate.
 * \param p2 down right point which we use to interpolate.
 * \param value1 the pixel's intensity at p1.
 * \param value2 the pixel's intensity at p2.
 * \param value3 the pixel's intensity at p3.
 * \param value4 the pixel's intensity at p4.
 * \return the new intensity value.
 */
unsigned int BWImage::bilinear_interpolation2(Coord c, Coord p1, Coord p2, unsigned int value1, unsigned int value2, unsigned int value3, unsigned int value4) const {
      float x2x1 = p2.getX_f() - p1.getX_f();
      float y2y1 = p2.getY_f() - p1.getY_f();
      float x2x = p2.getX_f() - c.getX_f();
      float y2y = p2.getY_f() - c.getY_f();
      float yy1 = c.getY_f() - p1.getY_f();
      float xx1 = c.getX_f() - p1.getX_f();
      return (unsigned int)((1.0 / (x2x1 * y2y1)) * ((float)value1 * x2x * y2y + (float)value2 * xx1 * y2y + (float)value3 * x2x * yy1 + (float)value4 * xx1 * yy1));
}


// m is a decreasing speed parameter
// We use the same algorithm than in "rotation2" (inverse_rotation + interpolation).
/**
 * \fn void BWImage::local_rotation(float theta, unsigned int x0, unsigned int y0, float dist_max, float m)
 * \brief Performs a local rotation of the image given the rotation angle and rotation center.
 * \param theta the rotation angle.
 * \param x0 the x coordinate of the rotation center.
 * \param y0 the y coordinate of the rotation center.
 * \param dist_max the distance from the rotation center.
 * \param m coefficient of the function used to simulate pressure.
 */
void BWImage::local_rotation(float theta, unsigned int x0, unsigned int y0, float dist_max, float m){

    //initializes a temporary matrix, used to do the rotation
    Eigen::MatrixXf tmpPict(wdth, hght);
    float t; // current angle (depending on the distance)
    float d; // current distance to (x0, y0)

    for (unsigned int x = 0; x < wdth; x++){
      for (unsigned int y = 0; y < hght; y++){
        Coord c = Coord(x,y);
        d = dist(x0, y0, c.getX(), c.getY());
        if(d<=dist_max){
          t = theta*pow((1-(d/dist_max)), m);
        }
        else{
          t=0;
        }
        c.inverse_rotation(t, x0, y0); //computes the coordinates in the starting picture of the pixel (x,y) of the rotated picture.
        if(c.getX_f()<0 || c.getX_f()>=wdth || c.getY_f()<0 || c.getY_f()>=hght){tmpPict(x, y) = 0;} // if we are outside the boundaries of the starting picture, we put a black pixel
        else{
          if(abs(c.getX_f()-c.getX()) < EPSILON && abs(c.getY_f()-c.getY()) < EPSILON){ // if we get rounded coordinates
            tmpPict(x, y) = image(c.getX(),c.getY(),0,0);
          }
          else{
            //find 4 close enough neighboors of the pixel in the starting picture.
            // 1. coordiates :
            Coord cp1 = Coord(floor(c.getX_f()), floor(c.getY_f()));
            Coord cp2= Coord(floor(c.getX_f()), ceil(c.getY_f()));
            Coord cp3 = Coord(ceil(c.getX_f()), floor(c.getY_f()));
            Coord cp4 = Coord(ceil(c.getX_f()), ceil(c.getY_f()));
            // 2. pixels intensity values :
            unsigned int p1 = image(cp1.getX(),cp1.getY(),0,0);
            unsigned int p2 = image(cp2.getX(),cp2.getY(),0,0);
            unsigned int p3 = image(cp3.getX(),cp3.getY(),0,0);
            unsigned int p4 = image(cp4.getX(),cp4.getY(),0,0);

            //compute the bilinear interpolation of this pixel intensity value using the four neighboors intensity value and distance :
            unsigned int newIntensity = bilinear_interpolation2(c, cp1, cp4, p1, p2, p3, p4);
            if(d<=dist_max){
              // we locally change the black intensity around the center of rotation :
              newIntensity = (float)newIntensity - 120.0*pow((1-(d/dist_max)), m) < 0 ? 0 : newIntensity - 120.0*pow((1-(d/dist_max)), m);
            }
            tmpPict(x, y) = newIntensity;
          }
        }
      }
    }


    for (unsigned int i = 0; i < wdth; i++){
      for (unsigned int j = 0; j < hght; j++){
        image(i,j,0,0) = tmpPict(i, j);//we copy the values of the matrix into the initial image
      }
    }

    image.save("../project/output_images/output_local_rotation.png"); //saves the new image
}

/**
 * \fn void BWImage::isotropic1(unsigned int x, unsigned int y)
 * \brief Displays a picture to which the isotropic function exp(-r)^10 is applied. (r is the distance of each pixel from the center of pressure)
 * \param x the x coordinate of the center of pressure.
 * \param y the y coordinate of the center of pressure.
 */

void BWImage::isotropic1(unsigned int x, unsigned int y){
  Eigen::MatrixXf values(wdth, hght);
  drawRect(x,y, 5, 5, 255); //white centered renctangle of pressure
  for (unsigned int i = 0; i < wdth; ++i){
    for (unsigned int j = 0; j < hght; j++){
      values(i, j) = (255 - image(i,j,0,0))*(pow(exp(- pow((dist(x, y, i, j)/sqrt(pow(wdth,2) + pow(hght,2))),2)),10));//distance is normaliwed between 0 and 1 and function g is computed
      image(i,j,0,0) = 255 - values(i, j);//changing the image
    }
  }
  image.save("../project/output_images/output_isotropic1.png");
  display();
}

/**
 * \fn void BWImage::isotropic2(unsigned int x, unsigned int y)
 * \brief Displays a picture to which the isotropic function 1/(1+r^15) is applied. (r is the distance of each pixel from the center of pressure)
 * \param x the x coordinate of the center of pressure.
 * \param y the y coordinate of the center of pressure.
 */
void BWImage::isotropic2(unsigned int x, unsigned int y){
  Eigen::MatrixXf values(wdth, hght);
  drawRect(x,y, 5, 5, 255);//white centered renctangle of pressure
  for (unsigned int i = 0; i < wdth; ++i){
    for (unsigned int j = 0; j < hght; j++){
    //  values[i][j] =  (255 - image(i,j,0,0))*(1/pow((1+(dist(x, y, i, j)/sqrt(pow(wdth,2) + pow(hght,2)))),23));
      if (dist(x, y, i, j) > 50){
        values(i, j) =  (255 - image(i,j,0,0))*(1/pow((1+((dist(x, y, i, j)-50)/sqrt(pow(wdth,2) + pow(hght,2)))),15));
        image(i,j,0,0) = 255 - values(i, j);
      }
    }
  }
  image.save("../project/output_images/output_isotropic2.png");
  display();
}

/**
 * \fn void BWImage::isotropic3(unsigned int x, unsigned int y)
 * \brief Displays a picture to which the isotropic function 1/(1 + (r/40)^2 ) is applied. (r is the distance of each pixel from the center of pressure)
 * \param x the x coordinate of the center of pressure.
 * \param y the y coordinate of the center of pressure.
 */
void BWImage::isotropic3(unsigned int x, unsigned int y){
  Eigen::MatrixXf values(wdth, hght);
  drawRect(x,y, 5, 5, 255);//white centered renctangle of pressure
  for (unsigned int i = 0; i < wdth; ++i){
    for (unsigned int j = 0; j < hght; j++){
      values(i, j) =  (255 - image(i,j,0,0))*(1/(1+pow((dist(x, y, i, j)/40), 2)));//filling the matrix of new values
      image(i,j,0,0) = 255 - values(i, j);//changing the image
    }
  }
  image.save("../project/output_images/output_isotropic3.png");
  display();
}


/**
 * \fn void BWImage::isotropicGauss(unsigned int x, unsigned int y, float alpha)
 * \brief Displays a picture to which the Gaussian isotropic function exp(-alpha * r^2) is applied. (r is the distance of each pixel from the center of pressure)
 * \param x the x coordinate of the center of pressure.
 * \param y the y coordinate of the center of pressure.
 * \param alpha the coefficient.
 */
void BWImage::isotropicGauss(unsigned int x, unsigned int y, float alpha){
  Eigen::MatrixXf values(wdth, hght);
  // drawRect(x,y, 5, 5, 255);//white centered renctangle of pressure
  for (unsigned int i = 0; i < wdth; ++i){
    for (unsigned int j = 0; j < hght; j++){
      values(i, j) =  (255 - image(i,j,0,0))*(1/(exp(alpha * pow(dist(x, y, i, j),2))));//filling the matrix of new values
      image(i,j,0,0) = 255 - values(i, j);//changing the image
    }
  }
   image.save("../project/output_images/output_isotropicGauss.png");
   display();
}

/**
 * \fn void BWImage::anisotropic(unsigned int x, unsigned int y, float a, float b)
 * \brief Displays a picture to which the anisotropic function 1/ (r/80)^2 is applied. (r is the elliptic distance of each pixel from the center of pressure)
 * \param x the x coordinate of the center of pressure.
 * \param y the y coordinate of the center of pressure.
 * \param a the parameter of elliptic distance.
 * \param b the parameter of elliptic distance.
 */
void BWImage::anisotropic(unsigned int x, unsigned int y, float a, float b){
  Eigen::MatrixXf values(wdth, hght);
  drawRect(x,y, 5, 5, 255);//white centered renctangle of pressure
  for (unsigned int i = 0; i < wdth; ++i){
    for (unsigned int j = 0; j < hght; j++){
      values(i, j) =  (255 - image(i,j,0,0))*(1/(1+pow(((dist_an(x,y,i,j,a,b)/80)), 2)));//filling the matrix of new values
      image(i,j,0,0) = 255 - values(i, j);//changing the image
    }
  }
  display();
}

/**
 * \fn void BWImage::anisotropic2(unsigned int x, unsigned int y, float a, float b)
 * \brief Displays a picture to which the anisotropic function 1/(1+r^15) is applied. (r is the elliptic distance of each pixel from the center of pressure)
 * \param x the x coordinate of the center of pressure.
 * \param y the y coordinate of the center of pressure.
 * \param a the parameter of elliptic distance.
 * \param b the parameter of elliptic distance.
 */
void BWImage::anisotropic2(unsigned int x, unsigned int y, float a, float b){
  Eigen::MatrixXf values(wdth, hght);
  drawRect(x,y, 5, 5, 255);//white centered renctangle of pressure
  for (unsigned int i = 0; i < wdth; ++i){
    for (unsigned int j = 0; j < hght; j++){
    //  values[i][j] =  (255 - image(i,j,0,0))*(1/pow((1+(dist(x, y, i, j)/sqrt(pow(wdth,2) + pow(hght,2)))),23));
      if (dist_an(x, y, i, j, a, b) > 50){
        values(i, j) =  (255 - image(i,j,0,0))*(1/pow((1+((dist_an(x, y, i, j, a, b)-47)/(sqrt(pow(wdth,2) + pow(hght,2))-47))),15));
        image(i,j,0,0) = 255 - values(i, j);
      }
      if (30 < dist_an(x, y, i, j, a, b) && dist_an(x, y, i, j, a, b) <= 50){
        values(i, j) =  (255 - image(i,j,0,0))*0.95;
        image(i,j,0,0) = 255 - values(i, j);
      }
    }
  }
  image.save("../project/output_images/output_anisotropic2-test.png");
  display();
}

/**
 * \fn void BWImage::anisotropicGauss(unsigned int x, unsigned int y, float a, float b)
 * \brief Displays a picture to which the Gaussian anisotropic function exp(-alpha * r^2) is applied. (r is the elliptic distance of each pixel from the center of pressure)
 * \param x the x coordinate of the center of pressure.
 * \param y the y coordinate of the center of pressure.
 * \param a the parameter of elliptic distance.
 * \param b the parameter of elliptic distance.
 */
void BWImage::anisotropicGauss(unsigned int x, unsigned int y, float a, float b, float alpha){
  Eigen::MatrixXf values(wdth, hght);
  drawRect(x,y, 5, 5, 255);//white centered renctangle of pressure
  for (unsigned int i = 0; i < wdth; ++i){
    for (unsigned int j = 0; j < hght; j++){
      values(i, j) =  (255 - image(i,j,0,0))*(1/(exp(alpha * pow(dist_an(x, y, i, j, a, b),2)/(sqrt(pow(wdth,2) + pow(hght,2))))));//filling the matrix of new values
      image(i,j,0,0) = 255 - values(i, j);//changing the image
    }
  }
  image.save("../project/output_images/output_isotropicGauss.png");
  display();
}

/**
 * \fn void BWImage::display() 
 * \brief Displays an image
 */
void BWImage::display() const {
  CImgDisplay main_disp(image,"Fingerprint");
  while (!main_disp.is_closed()) {
    main_disp.wait();
  }
}
