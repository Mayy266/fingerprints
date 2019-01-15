#include "image.h"
#include <cstdlib>
#include <cassert>
#include <vector>

using namespace cimg_library;
using namespace std;

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

/*
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
*/

/*
float greedy_algorithm(BWImage img1, BWImage img2){
  unsigned int i  = 0;
  while (i < 4){

  }


  return error;
}
*/
