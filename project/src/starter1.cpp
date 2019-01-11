#include "starter1.h"

//constuctor
BWImage::BWImage(CImg<unsigned char> img):image(img){
  image.channel(0);
  wdth = (unsigned int)image.width();
  hght = (unsigned int)image.height();
}

//conversion to float of the intensity of the pixels
float BWImage::toFloat(unsigned int x, unsigned int y){
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
unsigned int BWImage::height(){
  return hght;
}
//getter
unsigned int BWImage::width(){
  return wdth;
}


//draws rectangles on the picture
void BWImage::drawRect(unsigned int x, unsigned int y, unsigned int h, unsigned int w, unsigned int color){ //color: black = 0, white = 255, 0<gray<255
  for(unsigned int i = x; i < x+w; i++){
      for(unsigned int j = y; j < y+h; j++){
        image(i,j,0,0) = color;
      }
    }
    image.save("bin/output_rect.png"); //saves the new image
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
  image.save("bin/output_symmetry_Y.png"); //saves the new image
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
  image.save("bin/output_symmetry_X.png"); //saves the new image
}

//symmetry along the diagonal
void BWImage::symmetry_diagonal(){
  unsigned int h = (hght%2 == 1 ? hght - 1 : hght); //checks wether the height of the image is even or odd
  unsigned int w = (wdth%2 == 1 ? wdth - 1 : wdth); //checks wether the width of the image is even or odd
  for (unsigned int y = hght-wdth; y < h; y++){
    for (unsigned int x = 0; x < (unsigned int)(y-(hght-wdth)); x++){
      unsigned int tmp = image(x,y,0,0);
      image(x,y,0,0) = image(y-(hght-wdth),x+(hght-wdth),0,0);
      image(y-(hght-wdth),x+(hght-wdth),0,0) = tmp; //we crop the image so its width and height are the same, then we perform the symmetry
    }
  }
  drawRect(0, 0, hght-wdth, wdth, 255); //it sets the top part of the image to white
  image.save("bin/outputs/output_symmetry_diag.png"); //saves the new image
}

void BWImage::translation(int a, int b){
    //initializes a temporary matrix, used to do the rotation
    unsigned int** tmpPict = new unsigned int*[wdth];

    for (unsigned int i = 0; i < wdth; i++){
      tmpPict[i] = new unsigned int[hght];
      for (unsigned int j = 0; j < hght; j++){
        tmpPict[i][j] = 255;
      }
    }

    unsigned int h = (hght%2 == 1 ? hght - 1 : hght); //checks wether the height of the image is even or odd
    unsigned int w = (wdth%2 == 1 ? wdth - 1 : wdth); //checks wether the width of the image is even or odd
    for (unsigned int y = 0; y < h; y++){
      for (unsigned int x = 0; x < w; x++){
        Coord c = Coord(x,y);
        c.translation(a, b);
        //if(c.getX()>=0 && c.getY()>=0 && c.getX()<wdth && c.getY()<hght){
        if(c.getX()<wdth && c.getY()<hght){
          tmpPict[c.getX()][c.getY()] = image(x,y,0,0);
        }
      }
    }

    for (unsigned int i = 0; i < wdth; i++){
      for (unsigned int j = 0; j < hght; j++){
        image(i,j,0,0) = tmpPict[i][j];
      }
    }

    for (unsigned int i = 0; i < wdth; i++){
      delete[] tmpPict[i];
    }
    delete[] tmpPict;

    image.save("bin/outputs/output_translation.png"); //saves the new image
}

void BWImage::rotation(float theta, unsigned int x0, unsigned int y0){

  //initializes a temporary matrix, used to do the rotation
  unsigned int** tmpPict = new unsigned int*[wdth];

  for (unsigned int i = 0; i < wdth; i++){
    tmpPict[i] = new unsigned int[hght];
    for (unsigned int j = 0; j < hght; j++){
      tmpPict[i][j] = 0;
    }
  }
  unsigned int h = (hght%2 == 1 ? hght - 1 : hght); //checks wether the height of the image is even or odd
  unsigned int w = (wdth%2 == 1 ? wdth - 1 : wdth); //checks wether the width of the image is even or odd
  for (unsigned int y = 0; y < h; y++){
    for (unsigned int x = 0; x < w; x++){
      Coord c = Coord(x,y);
      c.rotation(theta, x0, y0);
      if(c.getX()<wdth && c.getY()<hght){
        tmpPict[c.getX()][c.getY()] = image(x,y,0,0);
      }
    }
  }

  for (unsigned int i = 0; i < wdth; i++){
    for (unsigned int j = 0; j < hght; j++){
      image(i,j,0,0) = tmpPict[i][j];
    }
  }

  for (unsigned int i = 0; i < wdth; i++){
    delete[] tmpPict[i];
  }
  delete[] tmpPict;

  image.save("bin/outputs/output_rotation.png"); //saves the new image
}


void BWImage::rotation_and_fill(float theta, unsigned int x0, unsigned int y0){

  //initializes a temporary matrix, used to do the rotation
  unsigned int** tmpPict = new unsigned int*[wdth]; //we create a temporary matrix

  for (unsigned int i = 0; i < wdth; i++){
    tmpPict[i] = new unsigned int[hght];
    for (unsigned int j = 0; j < hght; j++){
      tmpPict[i][j] = 300; // we fill it with a number >255 so that we know which pixels will not take an intensity value during the rotation
    }
  }
  unsigned int h = (hght%2 == 1 ? hght - 1 : hght); //checks wether the height of the image is even or odd
  unsigned int w = (wdth%2 == 1 ? wdth - 1 : wdth); //checks wether the width of the image is even or odd
  for (unsigned int y = 0; y < h; y++){
    for (unsigned int x = 0; x < w; x++){
      Coord c = Coord(x,y);
      c.rotation(theta, x0, y0);
      if(c.getX()<wdth && c.getY()<hght){
        tmpPict[c.getX()][c.getY()] = image(x,y,0,0); //we fill the temporary matrix with the rotated image
      }
    }
  }


  for (unsigned int i = 0; i < wdth; i++){
    for (unsigned int j = 0; j < hght; j++){
      unsigned int k = 1;
      while(tmpPict[i][j]==300 && j+k<hght && k<4){ //whenever we have more than 4 "300" values in a row (it means we are in the corners) we fill everything with white
        tmpPict[i][j]=tmpPict[i][j+k]; // fill each "300" value with the next non-300 value (Y-axis).
        k++;
      }
      image(i,j,0,0) = tmpPict[i][j]; //we copy the values of the matrix into the original image
      if(tmpPict[i][j]==300){
        image(i,j,0,0) = 255; // fill the corners with white
      }
    }
  }

  for (unsigned int i = 0; i < wdth; i++){ //we delete the temporary matrix
    delete[] tmpPict[i];
  }
  delete[] tmpPict;

  image.save("bin/output_rotation_fill.png"); //saves the new image
}


//displays the image
void BWImage::display(){
  CImgDisplay main_disp(image,"Fingerprint");
  while (!main_disp.is_closed()) {
    main_disp.wait();
  }
}

//displays the pixels in integers between 0 and 255
void BWImage::display_i(){
  for (unsigned int y = 0; y < hght; y++){
      for (unsigned int x = 0; x < wdth; x++){
          cout << (unsigned int)image(x,y,0,0) << " ";
      }
      cout << endl;
  }
}

//displays the pixels in floats between 0 and 1
void BWImage::display_f(){
  for (unsigned int y = 0; y < hght; y++){
      for (unsigned int x = 0; x < wdth; x++){
          cout << toFloat(x, y) << " ";
      }
      cout << endl;
  }
}


float dist(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2)
{
	int x = x1 - x2; //calculating number to square in next step
	int y = y1 - y2;
	float dist;

	dist = pow(x, 2) + pow(y, 2);       //calculating Euclidean distance
	dist = sqrt(dist);

	return dist;
}


void BWImage::isotropic1(unsigned int x, unsigned int y){
  vector<vector<float> > values(wdth, vector<float>(hght));
  for (unsigned int i = 0; i < wdth; ++i){
    for (unsigned int j = 0; j < hght; j++){
      values[i][j] = (255 - image(i,j,0,0))*(pow(exp(- pow((dist(x, y, i, j)/sqrt(pow(wdth,2) + pow(hght,2))),2)),10));//distance is normaliwed between 0 and 1 and function g is computed
      image(i,j,0,0) = 255 - values[i][j];//changing the image
    }
  }
  image.save("bin/output_isotropic1.png");
  (*this).display();
}

void BWImage::isotropic2(unsigned int x, unsigned int y){
  vector<vector<float> > values(wdth, vector<float>(hght));
  for (unsigned int i = 0; i < wdth; ++i){
    for (unsigned int j = 0; j < hght; j++){
      values[i][j] =  (255 - image(i,j,0,0))*(1/pow((1+(dist(x, y, i, j)/sqrt(pow(wdth,2) + pow(hght,2)))),23));
      image(i,j,0,0) = 255 - values[i][j];//changing the image
    }
  }
  image.save("bin/output_isotropic2.png");
  (*this).display();
}

void BWImage::isotropic3(unsigned int x, unsigned int y){
  vector<vector<float> > values(wdth, vector<float>(hght));
  for (unsigned int i = 0; i < wdth; ++i){
    for (unsigned int j = 0; j < hght; j++){
      values[i][j] =  (255 - image(i,j,0,0))*(1/(1+pow((dist(x, y, i, j)/40), 2)));//filling the matrix of new values
      image(i,j,0,0) = 255 - values[i][j];//changing the image
    }
  }
  image.save("bin/output_isotropic5.png");
  (*this).display();
}

void BWImage::anisotropic1(unsigned int x, unsigned int y){
  vector<vector<float> > values(wdth, vector<float>(hght));
  for (unsigned int i = 0; i < wdth; ++i){
    for (unsigned int j = 0; j < hght; j++){
      //values[i][j] =  (255 - image(i,j,0,0))*(1/(1+pow(sqrt(pow(i,2)/4 + pow(j,2))/40, 2)));//filling the matrix of new values
      values[i][j] =  (255 - image(i,j,0,0))*(1/pow((1+(sqrt(pow(i,2)/4 + pow(j,2))/sqrt(pow(wdth,2) + pow(hght,2)))),4));
      image(i,j,0,0) = 255 - values[i][j];//changing the image
    }
  }
  image.save("bin/output_isotropic5.png");
  (*this).display();
}

int main() {
//  CImg<unsigned char> image("/home/c/castellt/MASTER/fingerprints/project/bin/clean_finger_small.png"); //uploads the image
  //CImg<unsigned char> image("clean_finger_small.png");
  CImg<unsigned char> image("clean_finger.png");
  BWImage img = BWImage(image); //creates an instance of class BWImage

  //img.drawRect(30, 40, 50, 30, 255);
  //img.drawRect(10, 10, 50, 60, 0);
  //img.symmetry_X();
  //img.symmetry_X();
  //img.symmetry_diagonal();

//  img.display();
  //cout << "Min : " << img.minIntensity() << endl;
  //cout << "Max : " << img.maxIntensity() << endl;
  img.drawRect((int)(img.height()/2), (int)(img.width()/2), 7, 7, 255); //center of pressure
  img.anisotropic1((int)(img.height()/2),(int)(img.width()/2));

//  img.isotropic2((int)(img.height()/2),(int)(img.width()/2));
  return 0;
}
