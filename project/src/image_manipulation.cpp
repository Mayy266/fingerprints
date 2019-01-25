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

//conversion to float of the intensity of the pixels
float BWImage::toFloat(unsigned int x, unsigned int y) const {
  return (float)(image(x,y,0,0)/255.0);
}

//returns the maximum value of the intensity of the pixels
unsigned int BWImage::maxIntensity(){
  unsigned int max = 0;
  for (CImg<unsigned char>::iterator i = image.begin(); i != image.end(); ++i){
    if(*i > max){
      max = (int)(*i);
    }
  }
  return max;
}

//returns the minimum value of the intensity of the pixels
unsigned int BWImage::minIntensity(){
  unsigned int min = 256;

  for (CImg<unsigned char>::iterator i = image.begin(); i != image.end(); ++i){
    if(*i < min){
      min = (int)(*i);
    }
  }
  return min;
}

//getter
unsigned int BWImage::height() const {
  return hght;
}
//getter
unsigned int BWImage::width() const {
  return wdth;
}


//draws rectangles on the picture
void BWImage::drawRect(unsigned int x, unsigned int y, unsigned int h, unsigned int w, unsigned int color){ //color: black = 0, white = 255, 0<gray<255
  for(unsigned int i = x; i < x+w; i++){
      for(unsigned int j = y; j < y+h; j++){
        image(i,j,0,0) = color;
      }
    }
    image.save("../project/output_images/output_rect.png"); //saves the new image
}

//symmetry along the Y axis
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

//symmetry along the X axis
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

//symmetry along the diagonal
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

//translation of the image
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

    image.save("../project/output_images/output_translation.png"); //saves the new image
}

//translation of the image
void BWImage::translation_f(float a, float b){
    //initializes a temporary matrix, used to do the rotation
    Eigen::MatrixXf tmpPict(wdth, hght);

    for (unsigned int x = 0; x < wdth; x++){
      for (unsigned int y = 0; y < hght; y++){
        Coord c = Coord(x,y);
        c.translation(-a,-b); //computes the coordinates in the starting picture of the pixel (x,y) of the rotated picture.
        if(c.getX_f()<0 || c.getX_f()>=wdth || c.getY_f()<0 || c.getY_f()>=hght){tmpPict(x, y) = 255;} // if we are outside the boundaries of the starting picture, we put a white pixel
        else{
          //find 4 close enough neighboors of the pixel in the starting picture.
          // 1. coordinates :
          Coord cp1 = Coord(std::floor(c.getX_f()), std::floor(c.getY_f()));
          Coord cp2 = Coord(std::floor(c.getX_f()), std::ceil(c.getY_f()));
          Coord cp3 = Coord(std::ceil(c.getX_f()), std::floor(c.getY_f()));
          Coord cp4 = Coord(std::ceil(c.getX_f()), std::ceil(c.getY_f()));

          float deltaX = abs(c.getX_f()-c.getX());
          float deltaY = abs(c.getY_f()-c.getY());
          if(deltaX > EPSILON || deltaY > EPSILON){
            if((deltaX < EPSILON) && (c.getX_f() < wdth-1)){
              cp3 = Coord(std::ceil(c.getX_f())+1, std::floor(c.getY_f()));
              cp4 = Coord(std::ceil(c.getX_f())+1, std::ceil(c.getY_f()));
            }
            else if((deltaY < EPSILON) && (c.getY_f() < hght-1)){
              cp2 = Coord(std::floor(c.getX_f()), std::ceil(c.getY_f())+1);
              cp4 = Coord(std::ceil(c.getX_f()), std::ceil(c.getY_f())+1);
            }
            // 2. pixels intensity values :
            unsigned int p1 = image(cp1.getX(),cp1.getY(),0,0);
            unsigned int p2 = image(cp2.getX(),cp2.getY(),0,0);
            unsigned int p3 = image(cp3.getX(),cp3.getY(),0,0);
            unsigned int p4 = image(cp4.getX(),cp4.getY(),0,0);

            tmpPict(x, y) = bilinear_interpolation2(c, cp1, cp4, p1, p2, p3, p4);
          }
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

    image.save("../project/output_images/output_translation_f.png"); //saves the new image
}


//inverse rotation of the image
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

//rotation of the image
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

  //image.save("bin/outputs/output_rotation.png"); //saves the new image
  image.save("../project/output_images/output_rotation.png");
}

//rotation and filling of the lost information
//method :
// 1. apply the rotation on each pixels' coordinates
//    (during this step, we lose information because we get floating values,
//    and we cast them as integers tu use them as coordinates).
// 2. fill the lost information using bilinear interpoation.
void BWImage::rotation2(float theta, unsigned int x0, unsigned int y0){

  //initializes a temporary matrix, used to do the rotation
  Eigen::MatrixXf tmpPict(wdth, hght);

  for (unsigned int i = 0; i < wdth; i++){
    for (unsigned int j = 0; j < hght; j++){
      tmpPict(i, j) = 300; // we fill it with a number >255 so that we know which pixels will not take an intensity value during the rotation
    }
  }
  for (unsigned int y = 0; y < hght; y++){
    for (unsigned int x = 0; x < wdth; x++){
      Coord c = Coord(x,y);
      c.rotation(theta, x0, y0); //we rotate the coordinates
      if(c.getX()<wdth && c.getY()<hght){
        tmpPict(c.getX(), c.getY()) = image(x,y,0,0); //we fill the temporary matrix with the rotated image
      }
    }
  }

  for (unsigned int i = 0; i < wdth; i++){
    for (unsigned int j = 0; j < hght; j++){
      unsigned int k = 1;
      while(k<4 && j+k<hght && tmpPict(i, j+k)==300){ //in Y axis, whenever we have more than 4 "300" values in a row (it means we are in the corners) we fill everything with white
        k++;
      }
      if(k==4){
        tmpPict(i, j) = 0;
      }
      else{
        k = 1;
        while(k<4 && i+k<wdth && tmpPict(i+k, j)==300){ //in X axis, whenever we have more than 4 "300" values in a row (it means we are in the corners) we fill everything with white
          k++;
        }
        if(k==4){
          tmpPict(i, j) = 0;
        }
      }
    }
  }

  unsigned int p1, p2, p3, p4 = 0;
  Coord cp1, cp2, cp3, cp4;
  unsigned int lim = 4; //we set the limit so we don't go to far from the pixel we want to interpolate (to differentiate corners from the actual picture)
  for (unsigned int i = 0; i < wdth; i++){
    for (unsigned int j = 0; j < hght; j++){
      if(tmpPict(i, j) == 300){
        unsigned int l, k;

        // first loop (upper right corner) : (k, k-l-1)
        k = 0;
        while(k<lim){
          l = 0;
          while(l<lim && i+k<wdth && i+k>0 && j+k-l-1<hght && j+k-l-1>0 && tmpPict(i+k, j+k-l-1)==300){ // border conditions, it detects the pixel which we want to use to interpolate
            l++;
          }
          if(l<lim && i+k<wdth && i+k>0 && j+k-l-1<hght && j+k-l-1>0){//border conditions, we go inside this loop only if we find a non-300 value
            p1 = tmpPict(i+k, j+k-l+1);
            cp1.setX(i+k); //we save the coordinates of the points that we are using to interpolate
            cp1.setY(j+k-l+1); //so we can use them in the function 'interpolation'
            break;
          }
          k++;
        }
        // second loop (down right corner) : (l-k+1, l)
        k = 0;
        while(k<lim){
          l = 0;
          while(l<lim && i+l-k+1<wdth && i+l-k+1>0 && j+l<hght && j+l>0 && tmpPict(i+l-k+1, j+l)==300){// border conditions, it detects the pixel which we want to use to interpolate
            l++;
          }
          if(l<lim && i+l-k+1<wdth && i+l-k+1>0 && j+l<hght && j+l>0){//border conditions, we go inside this loop only if we find a non-300 value
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
          while(l<lim && i+k-l<wdth && i+k-l>0 && j+k+1<hght && j+k+1>0 && tmpPict(i+k-l, j+k+1)==300){// border conditions, it detects the pixel which we want to use to interpolate
            l++;
          }
          if(l<lim && i+k-l<wdth && i+k-l>0 && j+k+1<hght && j+k+1>0){//border conditions, we go insi//border conditions, we go inside this loop only if we find a non-300 value de this loop only if we find a non-300 value
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
          while(l<lim && i-l-1+k<wdth && i-l-1+k>0 && j-k<hght && j-k>0 && tmpPict(i-l-1+k, j-k)==300){// border conditions, it detects the pixel which we want to use to interpolate
            l++;
          }
          if(l<lim && i-l-1+k<wdth && i-l-1+k>0 && j-k<hght && j-k>0){//border conditions, we go inside this loop only if we find a non-300 value
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

  image.save("../project/output_images/output_rotation2.png"); //saves the new image
}


//rotation optimized to avoid the lost of information
//method :
// 1. compute the coordinates of the rotated picture in the starting picture using inverse rotation function (coordinates as floats)
// 2. compute the pixel intensity value of the pixel in the rotated picture using bilinear interpolation with the 4 nearest pixels in the starting picture.
void BWImage::rotation3(float theta, unsigned int x0, unsigned int y0){

  //initializes a temporary matrix, used to do the rotation
  // unsigned int** tmpPict = new unsigned int*[wdth]; //we create a temporary matrix
  Eigen::MatrixXf tmpPict(wdth, hght);

  for (unsigned int x = 0; x < wdth; x++){
    // tmpPict[x] = new unsigned int[hght];
    for (unsigned int y = 0; y < hght; y++){
      Coord c = Coord(x,y);
      c.inverse_rotation(theta, x0, y0); //computes the coordinates in the starting picture of the pixel (x,y) of the rotated picture.
      if(c.getX_f()<0 || c.getX_f()>=wdth || c.getY_f()<0 || c.getY_f()>=hght){tmpPict(x, y) = 255;} // if we are outside the boundaries of the starting picture, we put a black pixel
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
        tmpPict(x, y) = bilinear_interpolation(cp1, cp2, cp3, cp4, p1, p2, p3, p4);
      }
    }
  }


  for (unsigned int i = 0; i < wdth; i++){
    for (unsigned int j = 0; j < hght; j++){
      image(i,j,0,0) = tmpPict(i, j);//we copy the values of the matrix into the initial image
    }
  }

  // for (unsigned int i = 0; i < wdth; i++){ //we delete the temporary matrix
  //   delete[] tmpPict[i];
  // }
  // delete[] tmpPict;

  image.save("../project/output_images/output_rotation3.png"); //saves the new image
}


//interpolation using 4 points
unsigned int BWImage::bilinear_interpolation(Coord p1, Coord p2, Coord p3, Coord p4,
  unsigned int intensity1, unsigned int intensity2, unsigned int intensity3, unsigned int intensity4){

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
  return newIntensity;
}

//interpolation using 4 aligned points
//p1 upper left point and p2 down right point
//is used in translation_f and local_rotation
unsigned int BWImage::bilinear_interpolation2(Coord c, Coord p1, Coord p2, unsigned int value1, unsigned int value2, unsigned int value3, unsigned int value4){
      float x2x1 = p2.getX_f() - p1.getX_f();
      float y2y1 = p2.getY_f() - p1.getY_f();
      float x2x = p2.getX_f() - c.getX_f();
      float y2y = p2.getY_f() - c.getY_f();
      float yy1 = c.getY_f() - p1.getY_f();
      float xx1 = c.getX_f() - p1.getX_f();
      return (unsigned int)((1.0 / (x2x1 * y2y1)) * ((float)value1 * x2x * y2y + (float)value2 * xx1 * y2y + (float)value3 * x2x * yy1 + (float)value4 * xx1 * yy1));
}



// Apply a local rotation around (x0, y0), on the distance "dist", with an angle "theta".
// m is a decreasing speed parameter
// We use the same algorithm than in "rotation3" (inverse_rotation + interpolation).
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
              newIntensity = (float)newIntensity - 120.0*pow((1-(d/dist_max)), m) < 0 ? 0 : newIntensity - 120*pow((1-(d/dist_max)), m);
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



void BWImage::isotropic1(unsigned int x, unsigned int y){
  vector<vector<float> > values(wdth, vector<float>(hght));
  (*this).drawRect(x,y, 5, 5, 255); //white centered renctangle of pressure
  for (unsigned int i = 0; i < wdth; ++i){
    for (unsigned int j = 0; j < hght; j++){
      values[i][j] = (255 - image(i,j,0,0))*(pow(exp(- pow((dist(x, y, i, j)/sqrt(pow(wdth,2) + pow(hght,2))),2)),10));//distance is normaliwed between 0 and 1 and function g is computed
      image(i,j,0,0) = 255 - values[i][j];//changing the image
    }
  }
  image.save("../project/output_images/output_isotropic1.png");
  (*this).display();
}

void BWImage::isotropic2(unsigned int x, unsigned int y){
  vector<vector<float> > values(wdth, vector<float>(hght));
  (*this).drawRect(x,y, 5, 5, 255);//white centered renctangle of pressure
  for (unsigned int i = 0; i < wdth; ++i){
    for (unsigned int j = 0; j < hght; j++){
    //  values[i][j] =  (255 - image(i,j,0,0))*(1/pow((1+(dist(x, y, i, j)/sqrt(pow(wdth,2) + pow(hght,2)))),23));
      if (dist(x, y, i, j) > 50){
        values[i][j] =  (255 - image(i,j,0,0))*(1/pow((1+((dist(x, y, i, j)-50)/sqrt(pow(wdth,2) + pow(hght,2)))),15));
        image(i,j,0,0) = 255 - values[i][j];
      }
    }
  }
  image.save("../project/output_images/output_isotropic2.png");
  (*this).display();
}

void BWImage::isotropic3(unsigned int x, unsigned int y){
  vector<vector<float> > values(wdth, vector<float>(hght));
  (*this).drawRect(x,y, 5, 5, 255);//white centered renctangle of pressure
  for (unsigned int i = 0; i < wdth; ++i){
    for (unsigned int j = 0; j < hght; j++){
      values[i][j] =  (255 - image(i,j,0,0))*(1/(1+pow((dist(x, y, i, j)/40), 2)));//filling the matrix of new values
      image(i,j,0,0) = 255 - values[i][j];//changing the image
    }
  }
  image.save("../project/output_images/output_isotropic3.png");
  (*this).display();
}

void BWImage::isotropicGauss(unsigned int x, unsigned int y, float alpha){
  vector<vector<float> > values(wdth, vector<float>(hght));
  (*this).drawRect(x,y, 5, 5, 255);//white centered renctangle of pressure
  for (unsigned int i = 0; i < wdth; ++i){
    for (unsigned int j = 0; j < hght; j++){
      values[i][j] =  (255 - image(i,j,0,0))*(1/(exp(alpha * pow(dist(x, y, i, j),2))));//filling the matrix of new values
      image(i,j,0,0) = 255 - values[i][j];//changing the image
    }
  }
  image.save("../project/output_images/output_isotropicGauss.png");
  (*this).display();
}

void BWImage::anisotropic(unsigned int x, unsigned int y, float a, float b){
  vector<vector<float> > values(wdth, vector<float>(hght));
  (*this).drawRect(x,y, 5, 5, 255);//white centered renctangle of pressure
  for (unsigned int i = 0; i < wdth; ++i){
    for (unsigned int j = 0; j < hght; j++){
      values[i][j] =  (255 - image(i,j,0,0))*(1/(1+pow(((dist_an(x,y,i,j,a,b)/80)), 2)));//filling the matrix of new values
      /*if (values[i][j] < 210){
        values[i][j] = 0;
      }
      else{
        values[i][j] = 255;
      }
      */
      image(i,j,0,0) = 255 - values[i][j];//changing the image

    }
  }
}

void BWImage::anisotropic2(unsigned int x, unsigned int y, float a, float b){
  vector<vector<float> > values(wdth, vector<float>(hght));
  (*this).drawRect(x,y, 5, 5, 255);//white centered renctangle of pressure
  for (unsigned int i = 0; i < wdth; ++i){
    for (unsigned int j = 0; j < hght; j++){
    //  values[i][j] =  (255 - image(i,j,0,0))*(1/pow((1+(dist(x, y, i, j)/sqrt(pow(wdth,2) + pow(hght,2)))),23));
      if (dist_an(x, y, i, j, a, b) > 50){
        values[i][j] =  (255 - image(i,j,0,0))*(1/pow((1+((dist_an(x, y, i, j, a, b)-47)/(sqrt(pow(wdth,2) + pow(hght,2))-47))),15));
        image(i,j,0,0) = 255 - values[i][j];
      }
      if (30 < dist_an(x, y, i, j, a, b) && dist_an(x, y, i, j, a, b) <= 50){
        values[i][j] =  (255 - image(i,j,0,0))*0.95;
        image(i,j,0,0) = 255 - values[i][j];
      }
    }
  }
  image.save("../project/output_images/output_anisotropic2-test.png");
  (*this).display();
}

void BWImage::anisotropicGauss(unsigned int x, unsigned int y, float a, float b, float alpha){
  vector<vector<float> > values(wdth, vector<float>(hght));
  (*this).drawRect(x,y, 5, 5, 255);//white centered renctangle of pressure
  for (unsigned int i = 0; i < wdth; ++i){
    for (unsigned int j = 0; j < hght; j++){
      values[i][j] =  (255 - image(i,j,0,0))*(1/(exp(alpha * pow(dist_an(x, y, i, j, a, b),2)/(sqrt(pow(wdth,2) + pow(hght,2))))));//filling the matrix of new values
      image(i,j,0,0) = 255 - values[i][j];//changing the image
    }
  }
  image.save("../project/output_images/output_isotropicGauss.png");
  (*this).display();
}


//displays the image
void BWImage::display(){
  CImgDisplay main_disp(image,"Fingerprint");
  while (!main_disp.is_closed()) {
    main_disp.wait();
  }
}
