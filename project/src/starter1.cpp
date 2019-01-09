#include "starter1.h"

BWImage::BWImage(CImg<unsigned char> img):image(img){
  image.channel(0);
  wdth = (unsigned int)image.width();
  hght = (unsigned int)image.height();
}

float BWImage::toFloat(unsigned int x, unsigned int y){
  return (float)(image(x,y,0,0)/255.0);
}

unsigned int BWImage::maxIntensity(){
  unsigned int max = 0;

  for (CImg<unsigned char>::iterator i = image.begin(); i != image.end(); ++i){
    if(*i > max){
      max = (int)(*i);
    }
  }
  return max;
}

unsigned int BWImage::minIntensity(){
  unsigned int min = 256;

  for (CImg<unsigned char>::iterator i = image.begin(); i != image.end(); ++i){
    if(*i < min){
      min = (int)(*i);
    }
  }
  return min;
}

unsigned int BWImage::height(){
  return hght;
}
unsigned int BWImage::width(){
  return wdth;
}



void BWImage::drawRect(unsigned int x, unsigned int y, unsigned int h, unsigned int w, unsigned int color){
  for(unsigned int i = x; i < x+w; i++){
      for(unsigned int j = y; j < y+h; j++){
        image(i,j,0,0) = color;
      }
    }
    image.save("bin/output_rect.png");
}

void BWImage::symmetry_Y(){
  unsigned int w = (wdth%2 == 1 ? wdth - 1 : wdth);
  for (unsigned int y = 0; y < hght; y++){
    for (unsigned int x = 0; x < (unsigned int)(w/2); x++){
      unsigned int tmp = image(x,y,0,0);
      image(x,y,0,0) = image(wdth-x-1,y,0,0);
      image(wdth-x-1,y,0,0) = tmp;
    }
  }
  image.save("bin/output_symmetry_Y.png");
}

void BWImage::symmetry_X(){
  unsigned int h = (hght%2 == 1 ? hght - 1 : hght);
  for (unsigned int y = 0; y < (unsigned int)(h/2); y++){
    for (unsigned int x = 0; x < wdth; x++){
      unsigned int tmp = image(x,y,0,0);
      image(x,y,0,0) = image(x,hght-y-1,0,0);
      image(x,hght-y-1,0,0) = tmp;
    }
  }
  image.save("bin/output_symmetry_X.png");
}

void BWImage::symmetry_diagonal(){
  unsigned int h = (hght%2 == 1 ? hght - 1 : hght);
  unsigned int w = (wdth%2 == 1 ? wdth - 1 : wdth);
  for (unsigned int y = hght-wdth; y < h; y++){
    for (unsigned int x = 0; x < (unsigned int)(y); x++){ // float(y*w)/h
      unsigned int tmp = image(x,y,0,0);
      image(x,y,0,0) = image(y,x,0,0);
      image(y,x,0,0) = tmp;
    }
  }

  drawRect(0, 0, hght-wdth, wdth, 0);
  image.save("bin/output_symmetry_diag.png");
}

void BWImage::display(){
  CImgDisplay main_disp(image,"Fingerprint");
  while (!main_disp.is_closed()) {
    main_disp.wait();
  }
}

void BWImage::display_i(){
  for (unsigned int y = 0; y < hght; y++){
      for (unsigned int x = 0; x < wdth; x++){
          cout << (unsigned int)image(x,y,0,0) << " ";
      }
      cout << endl;
  }
}

void BWImage::display_f(){
  for (unsigned int y = 0; y < hght; y++){
      for (unsigned int x = 0; x < wdth; x++){
          cout << toFloat(x, y) << " ";
      }
      cout << endl;
  }
}



int main() {
  CImg<unsigned char> image("/home/c/castellt/MASTER/project/bin/clean_finger_small.png"); // clean_finger_small

  BWImage img = BWImage(image);

  //img.drawRect(30, 40, 50, 30, 255);
  //img.drawRect(10, 10, 50, 60, 0);
  //img.symmetry_X();
  //img.symmetry_X();
  img.symmetry_diagonal();

  img.display();
  cout << "Min : " << img.minIntensity() << endl;
  cout << "Max : " << img.maxIntensity() << endl;

  return 0;
}
