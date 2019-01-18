#include "image.h"

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
  unsigned int min = 255;

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
  unsigned int w = (wdth%2 == 1 ? wdth - 1 : wdth); //checks wether the width of the image is even or odd
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

    image.save("../project/output_images/output_translation.png"); //saves the new image
}

//rotation of the image
void BWImage::rotation(float theta, unsigned int x0, unsigned int y0){

  //initializes a temporary matrix, used to do the rotation
  unsigned int** tmpPict = new unsigned int*[wdth];

  // MatrixXf test = MatrixXf::Zero(wdth, hght);
  // for (unsigned int i = 0; i < wdth; i++){
  //   for (unsigned int j = 0; j < hght; j++){
  //     cout << test(i,j) << " ";
  //   }
  //   cout << endl;
  // }

  for (unsigned int i = 0; i < wdth; i++){
    tmpPict[i] = new unsigned int[hght];
    for (unsigned int j = 0; j < hght; j++){
      tmpPict[i][j] = 0;
    }
  }
  for (unsigned int y = 0; y < hght; y++){
    for (unsigned int x = 0; x < wdth; x++){
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

  //image.save("bin/outputs/output_rotation.png"); //saves the new image
  image.save("../project/output_images/output_rotation.png");
}

//inverse rotation of the image
void BWImage::inverse_rotation(float theta, unsigned int x0, unsigned int y0){

  //initializes a temporary matrix, it is used to do the rotation
  unsigned int** tmpPict = new unsigned int*[wdth];

  for (unsigned int i = 0; i < wdth; i++){
    tmpPict[i] = new unsigned int[hght];
    for (unsigned int j = 0; j < hght; j++){
      tmpPict[i][j] = 0;
    }
  }
  for (unsigned int y = 0; y < hght; y++){
    for (unsigned int x = 0; x < wdth; x++){
      Coord c = Coord(x,y);
      c.inverse_rotation(theta, x0, y0);
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

  //image.save("bin/outputs/output_inverse_rotation.png"); //saves the new image
  image.save("../project/output_images/output_inverse_rotation.png");
}


//rotation and filling of the lost information
void BWImage::rotation_and_fill(float theta, unsigned int x0, unsigned int y0){

  //initializes a temporary matrix, used to do the rotation
  unsigned int** tmpPict = new unsigned int*[wdth]; //we create a temporary matrix

  for (unsigned int i = 0; i < wdth; i++){
    tmpPict[i] = new unsigned int[hght];
    for (unsigned int j = 0; j < hght; j++){
      tmpPict[i][j] = 300; // we fill it with a number >255 so that we know which pixels will not take an intensity value during the rotation
    }
  }
  for (unsigned int y = 0; y < hght; y++){
    for (unsigned int x = 0; x < wdth; x++){
      Coord c = Coord(x,y);
      c.rotation(theta, x0, y0);
      if(c.getX()<wdth && c.getY()<hght){
        tmpPict[c.getX()][c.getY()] = image(x,y,0,0); //we fill the temporary matrix with the rotated image
      }
    }
  }

  unsigned int p1, p2, p3, p4 = 0;
  unsigned int lim = 4;
  for (unsigned int i = 5; i < wdth-5; i++){
    for (unsigned int j = 5; j < hght-5; j++){
      if(tmpPict[i][j] == 300){
        // first loop (upper right corner) : (k, k-l-1)
        unsigned int l, k;

        k = 0;
        while(k<lim){
          l = 0;
          while(l<lim && tmpPict[i+k][j+k-l-1]==300){ // +1 or -1 ?
            l++;
          }
          if(l<lim){
            p1 = tmpPict[i+k][j+k-l+1];
            break;
          }
          k++;
        }
        // second loop (down right corner) : (l-k+1, l)
        k = 0;
        while(k<lim){
          l = 0;
          while(l<lim && tmpPict[i+l-k+1][j+l]==300){
            l++;
          }
          if(l<lim){
            p2 = tmpPict[i+l-k+1][j+l];
            break;
          }
          k++;
        }
        // third loop (down left corner) : (k-l, k+1)
        k = 0;
        while(k<lim){
          l = 0;
          while(l<lim && tmpPict[i+k-l][j+k+1]==300){
            l++;
          }
          if(l<lim){
            p3 = tmpPict[i+k-l][j+k+1];
            break;
          }
          k++;
        }
        // fourth loop (upper left corner) : (-l-1+k, -k)
        k = 0;
        while(k<lim){
           l = 0;
          while(l<lim && tmpPict[i-l-1+k][j-k]==300){
            l++;
          }
          if(l<lim){
            p4 = tmpPict[i-l-1+k][j-k];
            break;
          }
          k++;
        }

        // we compute the bilinear interpolation with the four pixels :
        tmpPict[i][j] = (p1+p2+p3+p4)/4;
      }
    }
  }

  for (unsigned int i = 0; i < wdth; i++){
    for (unsigned int j = 0; j < hght; j++){
      image(i,j,0,0) = tmpPict[i][j];
    }
  }

  for (unsigned int i = 0; i < wdth; i++){ //we delete the temporary matrix
    delete[] tmpPict[i];
  }
  delete[] tmpPict;

  image.save("../project/output_images/output_rotation_fill.png"); //saves the new image
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


float dist(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2){
  int x = (x1 - x2); //calculating number to square in next step
  int y = (y1 - y2);
  float dist;
  dist = pow(x, 2) + pow(y, 2);    //calculating elliptic distance depending on a and b
  dist = sqrt(dist);
	return dist;
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
      /*if (values[i][j] < 50){
        values[i][j] = 0;
      }
      else{
        values[i][j] = 255;
      }
      */
      //changing the image
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

float dist_an(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, float a, float b) {
	int x = (x1 - x2); //calculating number to square in next step
	int y = (y1 - y2);
	float dist;
	dist = pow(x, 2)/a + pow(y, 2)/b;    //calculating elliptic distance depending on a and b
	dist = sqrt(dist);

	return dist;
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
  image.save("../project/output_images/output_anisotropicGauss.png");
  (*this).display();
}

/*
int main(int argc, char const *argv[]) {
//int main(){
  //STARTER1
  //CImg<unsigned char> image("clean_finger_small.png");
  CImg<unsigned char> image(argv[1]);
  //CImg<unsigned char> image("clean_finger.png");
  BWImage img = BWImage(image); //creates an instance of class BWImage
  //cout << "Min : " << img.minIntensity() << endl;
  //cout << "Max : " << img.maxIntensity() << endl;
  //img.drawRect(30, 40, 50, 30, 255);
  //img.drawRect(10, 10, 50, 60, 0);
  //img.display();
  //img.symmetry_X();
  //img.symmetry_Y();
  //img.symmetry_diagonal();

  img.translation(40,44);

  //MAIN1- FOR ISOTROPIC AND ANISOTROPIC
  img = BWImage(image);
  img.isotropic1((int)(img.height()/2),(int)(3*img.width()/4));
  img = BWImage(image);
  img.isotropic2((int)(img.height()/2),(int)(3*img.width()/4));
  img = BWImage(image);
  img.isotropic3((int)(img.height()/2),(int)(3*img.width()/4));
  img.drawRect((int)(img.height()/2), (int)(3*img.width()/4), 7, 7, 255); //center of pressure
  img.anisotropic((int)(img.height()/2),(int)(3*img.width()/4), 0.1, 0.15);//a = 0.1, b = 0.15 simulate shape of an anisotropic fingerprint
  img = BWImage(image);
  img.anisotropic((int)(img.height()/2),(int)(3*img.width()/4), 0.4, 1);// a = 0.4, b = 1 its a good example of an elipse

  return 0;
}
*/
