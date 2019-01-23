#include "externalFunctions.h"
//#include "image.h"
using namespace cimg_library;
using namespace std;
using namespace Eigen;

vector<vector<float>> operator-(BWImage img1, BWImage img2){
  assert(img1.height() == img2.height() && img1.width() == img2.width());
  unsigned int h = img1.height();
  unsigned int w = img1.width();

  vector<vector<float>> substrMatrix(h, vector<float>(w,1));
  for (unsigned int j = 0; j < w; j++){
      for(unsigned int i = 0; i < h; i++){
      //indx = i + j*h;
      // k++
      substrMatrix[i][j] = img1.toFloat(i,j) - img2.toFloat(i,j);
    }
  }

  return substrMatrix;
}

//numeric error
float error(BWImage img1, BWImage img2){
  assert(img2.height() == img1.height() && img2.width() == img1.width());
  float mean = 0;
  for (unsigned int i = 0; i < img1.width(); i++){
    for (unsigned int j = 0; j < img1.height(); j++){
      mean += pow(img1.image(i,j,0,0)-img2.image(i,j,0,0), 2);
      img2.image(i,j,0,0) = abs(img1.image(i,j,0,0)-img2.image(i,j,0,0));
    }
  }
  return mean;
}

/*
float meanIntensity(BWImage img){
  float sum = 0;
  unsigned int w = img.width();
  unsigned int h = img.height();
  for(unsigned int i = 0; i < w; i++){
      for(unsigned int j = 0; j <  h; j++){
        sum += image(i,j,0,0);
      }
    }
  float mean = sum/(w*h);
  return mean;
}

*/
float optimize(BWImage img1, BWImage img2){

  vector<vector<float>> substrMatrix;
  substrMatrix = img1 - img2;
  float error = 0;
  for(unsigned int i = 0; i < img1.height(); i++){
    for(unsigned int j = 0; j < img1.width(); j++){
      error += pow(substrMatrix[i][j],2);
    }
  }

  return error;
}


/*
int greedy_algorithm_x(BWImage img1, BWImage img2){
  int p_x; //translation parameter to be found
  unsigned int w = img1.width(); //width of the image
  BWImage original_img = img1; //making a copy of the image
  BWImage leftTr = img1;
  BWImage rightTr = img1;
  unsigned int i  = 2; //to start in the loop with translation parameter 1/4
  bool newest; //keeping track of the latest translation
  float a = 0;
  unsigned int l = (unsigned int)log2(w) + 1; //number of effective iterations that we need in the loop
  float error = optimize(img1, img2); //checking if we images already match
  while ((i < l) && (error != 0)){
    img1 = original_img;
    img1.translation((int)(((a-pow((0.5),i))*w)),0);
    leftTr = img1;
    img1 = original_img;
    img1.translation((int)(((a+pow((0.5),i))*w)),0);
    rightTr = img1;
    if(optimize(img2, leftTr) < optimize(img2, rightTr)){ //comparing left and right translation to define the correct direction
      a -= pow((0.5),i);
      error = optimize(img2, leftTr);
      newest = true;
    }
    else{
      a += pow((0.5),i);
      error = optimize(img2, rightTr);
      newest = false;
    }
    i++;
  }

  if(newest){//to display the last chosen translation
    leftTr.display();
  }
  else{
    rightTr.display();
  }
  img2.display();
  p_x = (int)(a*w); //final translation paremeter found
  cout << "error = " << error << endl;
  return p_x;
}

vector<int> greedy_algorithm_xy(BWImage img1, BWImage img2){
  unsigned int w = img1.width(); //width of the image
  unsigned int h = img1.height();
  BWImage original_img = img1; //making a copy of the image
  BWImage leftUpTr = img1;
  BWImage leftDownTr = img1;
  BWImage rightUpTr = img1;
  BWImage rightDownTr = img1;
  vector<int> finalParameters(2);
  BWImage newest = img1;
  BWImage helpNewest = img1;

  unsigned int j = 2;
  unsigned int i  = 2; //to start in the loop with translation parameter 1/4
  //bool newest; //keeping track of the latest translation
  float a = 0;
  float b = 0;
  float p_x = 0;
  float p_y = 0;
  bool undoAB;

  unsigned int m = (unsigned int)log2(h) + 1;
  unsigned int l = (unsigned int)log2(w) + 1; //number of effective iterations that we need in the loop
  float error1, error2, error3, error4, error5, error6, minError;
  if(optimize(img1, img2)!=0){minError = w*h*255;} //checking if we images already match
  else{minError = 0;}
  std::cout << "first min " << minError << '\n';
  while (((i < l) || ( j < m)) && (minError != 0)){
    img1 = original_img;
    img1.translation((int)(((p_x-pow((0.5),i))*w)),(int)(((p_y-pow((0.5),j))*h)));
    leftUpTr = img1;
    cout << "LeftUp; px = "<<(int)(((p_x-pow((0.5),i))*w))<< ", py= "<< (int)(((p_y-pow((0.5),j))*h))<<endl;

    img1 = original_img;
    img1.translation((int)(((p_x+pow((0.5),i))*w)),(int)(((p_y-pow((0.5),j))*h)));
    rightUpTr = img1;
    cout << "RighttUp; px = "<<(int)(((p_x+pow((0.5),i))*w))<< ", py = " << (int)(((p_y-pow((0.5),j))*h))<<endl;


    img1 = original_img;
    img1.translation((int)(((p_x-pow((0.5),i))*w)),(int)(((p_y+pow((0.5),j))*h)));
    leftDownTr = img1;
    cout << "LeftDown; px = "<<(int)(((p_x-pow((0.5),i))*w))<< ", py= "<< (int)(((p_y+pow((0.5),j))*h))<<endl;


    img1 = original_img; //translation parameter to be found
    img1.translation((int)(((p_x+pow((0.5),i))*w)),(int)(((p_y+pow((0.5),j))*h)));
    rightDownTr = img1;
    cout << "RightDown; px = " <<(int)(((p_x+pow((0.5),i))*w))<< ", py= "<< (int)(((p_y+pow((0.5),j))*h))<<endl;


    if(optimize(img2, leftUpTr) < optimize(img2, rightUpTr)){
      a -= pow((0.5),i);
      b -= pow((0.5),j);
      error1 = optimize(img2, leftUpTr);
      undoAB = true;
      helpNewest = leftUpTr;
    }
    else{
      a += pow((0.5),i);
      b -= pow((0.5),j);
      error1 = optimize(img2, rightUpTr);
      undoAB = false;
      helpNewest = rightUpTr;
    }
    if(error1 < minError){
      minError = error1;
      p_x = a;
      p_y = b;
      newest = helpNewest;
    }

    std::cout << "error1 = " <<error1 << " min = " << minError << '\n';

    if(optimize(img2, leftUpTr) < optimize(img2, rightDownTr)){
      if(undoAB){
        a += pow((0.5),i);
        b += pow((0.5),j);
      }
      else{
        a -= pow((0.5),i);
        b += pow((0.5),j);
      }

      a -= pow((0.5),i);
      b -= pow((0.5),j);
      error2 = optimize(img2, leftUpTr);
      undoAB = true;
      helpNewest = leftUpTr;
    }
    else{
      if(undoAB){
        a += pow((0.5),i);
        b += pow((0.5),j);
      }
      else{
        a -= pow((0.5),i);
        b += pow((0.5),j);
      }

      a += pow((0.5),i);
      b += pow((0.5),j);
      error2 = optimize(img2, rightDownTr);
      undoAB = false;
      helpNewest = rightDownTr;
    }
    if(error2 < minError){
      minError = error2;
      p_x = a;
      p_y = b;
      newest = helpNewest;
    }

    std::cout << "error2 = " <<error2 << " min = " << minError << '\n';

    if(optimize(img2, leftUpTr) < optimize(img2, leftDownTr)){
      if(undoAB){
        a += pow((0.5),i);
        b += pow((0.5),j);
      }
      else{
        a -= pow((0.5),i);
        b -= pow((0.5),j);
      }

      a -= pow((0.5),i);
      b -= pow((0.5),j);
      error3 = optimize(img2, leftUpTr);
      undoAB =true;
      helpNewest = leftUpTr;
    }
    else{
      if(undoAB){
        a += pow((0.5),i);
        b += pow((0.5),j);
      }
      else{
        a -= pow((0.5),i);
        b -= pow((0.5),j);
      }

      a -= pow((0.5),i);
      b += pow((0.5),j);
      error3 = optimize(img2, leftDownTr);
      undoAB = false;
      helpNewest = leftDownTr;
    }
    if(error3 < minError){
      minError = error3;
      p_x = a;
      p_y = b;
      newest = helpNewest;
    }
    cout << "iteration i = "<< i << ", a = " << a << ", b = " << b << endl;

    std::cout << "error3 = " <<error3 << " min = " << minError << '\n';

    if(optimize(img2, rightUpTr) < optimize(img2, rightDownTr)){
      if(undoAB){
        a += pow((0.5),i);
        b += pow((0.5),j);
      }
      else{
        a += pow((0.5),i);
        b -= pow((0.5),j);
      }
      a += pow((0.5),i);
      b -= pow((0.5),j);
      error4 = optimize(img2, rightUpTr);
      undoAB = true;
      helpNewest = rightUpTr;
    }
    else{
      if(undoAB){
        a += pow((0.5),i);
        b += pow((0.5),j);
      }
      else{
        a += pow((0.5),i);
        b -= pow((0.5),j);
      }
      a += pow((0.5),i);
      b += pow((0.5),j);
      error4 = optimize(img2, rightDownTr);
      undoAB = false;
      helpNewest = rightDownTr;
    }
    if(error4 < minError){
      minError = error4;
      p_x = a;
      p_y = b;
      newest = helpNewest;
    }

    std::cout << "error4 = " <<error4 << " min = " << minError << '\n';

    if(optimize(img2, rightUpTr) < optimize(img2, leftDownTr)){
      if(undoAB){
        a -= pow((0.5),i);
        b += pow((0.5),j);
      }
      else{
        a -= pow((0.5),i);
        b -= pow((0.5),j);
      }
      a += pow((0.5),i);
      b -= pow((0.5),j);
      error5 = optimize(img2, rightUpTr);
      undoAB = true;
      helpNewest = rightUpTr;
    }
    else{
      if(undoAB){
        a -= pow((0.5),i);
        b += pow((0.5),j);
      }
      else{
        a -= pow((0.5),i);
        b -= pow((0.5),j);
      }
      a -= pow((0.5),i);
      b += pow((0.5),j);
      error5 = optimize(img2, leftDownTr);
      undoAB = false;
      helpNewest = leftDownTr;
    }
    if(error5 < minError){
      minError = error5;
      p_x = a;
      p_y = b;
      newest = helpNewest;
    }

    std::cout << "error5 = " << error5 << " min = " << minError << '\n';

    if(optimize(img2, rightDownTr) < optimize(img2, leftDownTr)){
      if(undoAB){
        a -= pow((0.5),i);
        b += pow((0.5),j);
      }
      else{
        a += pow((0.5),i);
        b -= pow((0.5),j);
      }
      a += pow((0.5),i);
      b += pow((0.5),j);
      error6 = optimize(img2, rightDownTr);
      undoAB = true;
      helpNewest = rightDownTr;
    }
    else{
      if(undoAB){
        a -= pow((0.5),i);
        b += pow((0.5),j);
      }
      else{
        a += pow((0.5),i);
        b -= pow((0.5),j);
      }
      a -= pow((0.5),i);
      b += pow((0.5),j);
      error6 = optimize(img2, leftDownTr);
      undoAB = false;
      helpNewest = leftDownTr;
    }
    if(error6 < minError){
      minError = error6;
      p_x = a;
      p_y = b;
      newest = helpNewest;
    }

    std::cout << "error6 = " << error6 << " min = " << minError << '\n';

    std::cout << "px = " << p_x*w << ", py = " << p_y*h << '\n';
    if(i < l){i++;}
    if(j < m){j++;}
    i++;
    j++;
  }
  img2.display();
  newest.display();
  p_y = (int)(p_y*h);
  p_x = (int)(p_x*w); //final translation paremeters found
  cout << "final error = " << minError << endl;
  finalParameters[0] = p_x;
  finalParameters[1] = p_y;
  return finalParameters;
}
*/


// algorithm : dichotomy
int greedy_algorithm_x(BWImage img1, BWImage img2){
  unsigned int w = img1.width(); //width of the image
  BWImage original_img = img1; //making a copy of the image

  unsigned int i  = 2; //to start in the loop with translation parameter 1/4
  int p_x; //translation parameter to be found
  int xLeft, xRight;

  unsigned int l = (unsigned int)log2(w) + 1; //number of effective iterations that we need in the loop
  int minErr = (int)error(img2,img1);
  while ((i < l) && (minErr != 0)){
    xLeft = p_x - pow(0.5, i)*w;
    xRight = p_x + pow(0.5, i)*w;

    img1 = original_img;
    img1.translation(xLeft, 0);
    int e1 = (int)error(img1,img2);

    img1 = original_img;
    img1.translation(xRight, 0);
    int e2 = (int)error(img1,img2);

    minErr = min(e1, e2);
    if(e1 == minErr){ p_x = xLeft;}
    else { p_x = xRight;}

    i++;
  }
  return p_x;
}


// algorithm : dichotomy
vector<int> greedy_algorithm_xy(BWImage img1, BWImage img2){
  unsigned int w = img1.width(); //width of the image
  unsigned int h = img1.height(); //height of the image
  BWImage original_img = img1; //making a copy of the image
  vector<int> finalParameters(2); // output (translation from the original image)

  unsigned int i  = 2; //to start in the loop with translation parameter 1/4
  float p_x = 0; float p_y = 0;
  int xLeft, xRight, yUp, yDown;
  float delta;

  unsigned int m = (unsigned int)log2(h) + 1;
  unsigned int l = (unsigned int)log2(w) + 1; //number of effective iterations that we need in the loop
  int minErr = (int)error(img2,img1);
  while (((i < l) || ( i < m)) && (minErr != 0)){
    delta = pow(0.5, i);
    xLeft = p_x - delta*w;
    xRight = p_x + delta*w;
    yUp = p_y - delta*h;
    yDown = p_y + delta*h;

    img1 = original_img;
    img1.translation(xLeft, yUp);
    int e1 = (int)error(img1,img2);

    img1 = original_img;
    img1.translation(xRight, yUp);
    int e2 = (int)error(img1,img2);

    img1 = original_img;
    img1.translation(xLeft, yDown);
    int e3 = (int)error(img1,img2);

    img1 = original_img;
    img1.translation(xRight, yDown);
    int e4 = (int)error(img1,img2);

    minErr = min(e1, min(e2, min(e3, e4)));

    if(e1 == minErr){ p_x = xLeft; p_y = yUp; }
    else if(e2 == minErr){ p_x = xRight; p_y = yUp; }
    else if(e3 == minErr){ p_x = xLeft; p_y = yDown; }
    else { p_x = xRight; p_y = yDown; }

    i++;
  }
  finalParameters[0] = p_x;
  finalParameters[1] = p_y;
  return finalParameters;
}
