#include "externalFunctions.h"
//#include "image.h"

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


float optimize(BWImage img1, BWImage img2){

  vector<vector<float>> substrMatrix;
  substrMatrix = img1 - img2;
  float error = 0;
  for(unsigned int i = 0; i < img1.height(); i++){
    for(unsigned int j = 0; j < img1.width(); j++){
      error += pow(substrMatrix[i][j],2);
    }
  }

  return error/(img1.height()*img1.width());
}



// algorithm : dichotomy
int greedy_algorithm_x(BWImage img1, BWImage img2){
  unsigned int w = img1.width(); //width of the image
  BWImage original_img = img1; //making a copy of the image

  unsigned int i  = 2; //to start in the loop with translation parameter 1/4
  int p_x; //translation parameter to be found
  int xLeft, xRight;

  unsigned int l = (unsigned int)log2(w) + 1; //number of effective iterations that we need in the loop
  int minErr = (int)img2.error(img1);
  while ((i < l) && (minErr != 0)){
    xLeft = p_x - pow(0.5, i)*w;
    xRight = p_x + pow(0.5, i)*w;

    img1 = original_img;
    img1.translation(xLeft, 0);
    int e1 = (int)img1.error(img2);

    img1 = original_img;
    img1.translation(xRight, 0);
    int e2 = (int)img1.error(img2);

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
  int minErr = (int)img2.error(img1);
  while (((i < l) || ( i < m)) && (minErr != 0)){
    delta = pow(0.5, i);
    xLeft = p_x - delta*w;
    xRight = p_x + delta*w;
    yUp = p_y - delta*h;
    yDown = p_y + delta*h;

    img1 = original_img;
    img1.translation(xLeft, yUp);
    int e1 = (int)img1.error(img2);

    img1 = original_img;
    img1.translation(xRight, yUp);
    int e2 = (int)img1.error(img2);

    img1 = original_img;
    img1.translation(xLeft, yDown);
    int e3 = (int)img1.error(img2);

    img1 = original_img;
    img1.translation(xRight, yDown);
    int e4 = (int)img1.error(img2);

    minErr = min(e1, min(e2, min(e3, e4)));

    if(e1 == minErr){ p_x = xLeft; p_y = yUp; }
    else if(e2 == minErr){ p_x = xRight; p_y = yUp; }
    else if(e3 == minErr){ p_x = xLeft; p_y = yDown; }
    else { p_x = xRight; p_y = yDown; }

    i++;
  }
  cout << "Error : " << minErr << endl;
  finalParameters[0] = p_x;
  finalParameters[1] = p_y;
  return finalParameters;
}


// vector<float> most_greedy_algorithm_ever(BWImage img1, BWImage img2){
//   unsigned int w = img1.width(); //width of the image
//   unsigned int h = img1.height(); //height of the image
//   BWImage original_img = img1; //making a copy of the image
//   vector<float> finalParameters(3); // output (translation from the original image)
//
//   unsigned int i  = 2; //to start in the loop with translation parameter 1/4
//   float p_x = 0; float p_y = 0;
//   int xLeft, xRight, yUp, yDown;
//   float delta;
//
//   unsigned int m = (unsigned int)log2(h) + 1;
//   unsigned int l = (unsigned int)log2(w) + 1; //number of effective iterations that we need in the loop
//   int minErr = (int)img2.error(img1);
//   while (((i < l) || ( i < m)) && (minErr != 0)){
//     delta = pow(0.5, i);
//     xLeft = p_x - delta*w;
//     xRight = p_x + delta*w;
//     yUp = p_y - delta*h;
//     yDown = p_y + delta*h;
//
//     img1 = original_img;
//     img1.translation(xLeft, yUp);
//     while (e1 )
//     img1.rotation3(2*theta/j,xLeft, yUp )
//     int e1 = (int)img1.error(img2);
//
//     img1 = original_img;
//     img1.translation(xRight, yUp);
//     int e2 = (int)img1.error(img2);
//
//     img1 = original_img;
//     img1.translation(xLeft, yDown);
//     int e3 = (int)img1.error(img2);
//
//     img1 = original_img;
//     img1.translation(xRight, yDown);
//     int e4 = (int)img1.error(img2);
//
//     minErr = min(e1, min(e2, min(e3, e4)));
//
//     if(e1 == minErr){ p_x = xLeft; p_y = yUp; }
//     else if(e2 == minErr){ p_x = xRight; p_y = yUp; }
//     else if(e3 == minErr){ p_x = xLeft; p_y = yDown; }
//     else { p_x = xRight; p_y = yDown; }
//
//     i++;
//   }
//   cout << "Error : " << minErr << endl;
//   finalParameters[0] = p_x;
//   finalParameters[1] = p_y;
//   return finalParameters;
// }
