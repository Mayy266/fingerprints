#include "externalFunctions.h"
//#include "image.h"
using namespace cimg_library;
using namespace std;
using namespace Eigen;

MatrixXf operator-(BWImage img1, BWImage img2){
  assert(img1.height() == img2.height() && img1.width() == img2.width());
  unsigned int h = img1.height();
  unsigned int w = img1.width();

  MatrixXf substrMatrix(h,w);
  for (unsigned int j = 0; j < w; j++){
      for(unsigned int i = 0; i < h; i++){

        substrMatrix(i,j) = img1.toFloat(i,j) - img2.toFloat(i,j);
    }
  }

  return substrMatrix;
}

//computes the distance between two points
float dist(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2){
  int x = (x1 - x2); //calculating number to square in next step
  int y = (y1 - y2);
  float dist;
  dist = pow(x, 2) + pow(y, 2);    //calculating distance
  dist = sqrt(dist);
  return dist;
}

//computes the elliptic distance between two points
float dist_an(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, float a, float b) {
    int x = (x1 - x2); //calculating number to square in next step
    int y = (y1 - y2);
    float dist;
    dist = pow(x, 2)/a + pow(y, 2)/b;    //calculating elliptic distance depending on a and b
    dist = sqrt(dist);

    return dist;
}

//numeric error (difference^2)
float error(const BWImage img1, const BWImage img2){
  assert(img2.height() == img1.height() && img2.width() == img1.width());
  float output = 0;
  for (unsigned int i = 0; i < img1.width(); i++){
    for (unsigned int j = 0; j < img1.height(); j++){
      output += pow(img1.image(i,j,0,0)-img2.image(i,j,0,0), 2);
    }
  }
  // cout << "error : " << output << endl;
  return output;
}

// display the error image
void display_error(const BWImage img1, const BWImage img2){
  assert(img2.height() == img1.height() && img2.width() == img1.width());
  BWImage error_img = img1; //making a copy of the image to display the error

  for (unsigned int i = 0; i < img1.width(); i++){
    for (unsigned int j = 0; j < img1.height(); j++){
      error_img.image(i,j,0,0) = abs(img1.image(i,j,0,0)-img2.image(i,j,0,0));
    }
  }
  error_img.display();
}

//we don't know exactly what's going on here but ok
float error_improved(const BWImage img1, const BWImage img2){
  assert(img2.height() == img1.height() && img2.width() == img1.width());
  float meanImg1 = meanIntensity(img1);
  float meanImg2 = meanIntensity(img2);
  float numerator = 0;
  float denominatorF = 0;
  float denominatorG = 0;
  float F = 0;
  float G = 0;
  float error;

  for(unsigned int i = 0; i < img1.width(); i++){
    for(unsigned int j = 0; j < img1.height(); j++){
      F = img1.toFloat(i,j) - meanImg1;
      G = img2.toFloat(i,j) - meanImg2;
      numerator += F*G;
      denominatorF += pow(F,2);
      denominatorG += pow(G,2);
    }
  }
  error = numerator/sqrt(denominatorF*denominatorG);
  return error;
}

//mean intensity of the image, returns value between 0 and 1
float meanIntensity(const BWImage img){
  float sum = 0;
  unsigned int w = img.width();
  unsigned int h = img.height();
  for(unsigned int i = 0; i < w; i++){
      for(unsigned int j = 0; j <  h; j++){
        sum += img.toFloat(i,j);
      }
    }
  float mean = sum/(w*h);
  return mean;
}


// algorithm : polychotomy
float polychotomy_x(const BWImage original_img, const BWImage imgToFind, int accuracy, bool floatTranslation){
  unsigned int w = original_img.width(); //width of the image
  BWImage modified_img = original_img; //making a copy of the image

  unsigned int i  = 0;
  float p_x = 0;
  float p_x_tmp = 0;
  float currentX, delta, err;
  unsigned int n = (unsigned int)std::log(w)/std::log(accuracy) + 1; //number of effective iterations that we need in the loop

  float minErr = error(modified_img, imgToFind);

  while (( i < n ) && (minErr > EPSILON)){
    delta = pow((1/(float)accuracy), i);
    for(int j = 0; j<accuracy; j++){
      // compute the jth x coordinate
      currentX = p_x - delta*w/2 + delta*w/(2* accuracy) + j*delta*w/accuracy;

      // we compute the error err with these 2 values, we compare it to the min error
      // and if it's smaller, then we update p_x, p_y and minErr
      modified_img = original_img;
      if(floatTranslation){ modified_img.translation_f(currentX, 0); }
      else{ modified_img.translation(std::round(currentX), 0); }

      err = error(modified_img, imgToFind);
      if(err-minErr < 0){
        minErr = err;
        p_x_tmp = currentX;
      }
    }
    p_x = p_x_tmp;
    i++;
  }
  return p_x;
}


// algorithm : polychotomy
Eigen::VectorXf polychotomy_xy(const BWImage original_img, const BWImage imgToFind, int accuracy, bool floatTranslation){
  unsigned int w = original_img.width(); //width of the image
  unsigned int h = original_img.height(); //height of the image
  BWImage modified_img = original_img; //making a copy of the image
  Eigen::VectorXf finalParameters(2); // output (translation from the original image)

  unsigned int i  = 0;
  float p_x = 0; float p_y = 0;
  float p_x_tmp = 0; float p_y_tmp = 0;
  float currentX, currentY, delta, err;

  unsigned int m = (unsigned int)std::log(h)/std::log(accuracy) + 1;
  unsigned int n = (unsigned int)std::log(w)/std::log(accuracy) + 1; //number of effective iterations that we need in the loop
  float minErr = error(modified_img, imgToFind);
  while (((i < m) || ( i < n )) && (minErr > EPSILON)){
    delta = pow((1/(float)accuracy), i);
    for(int j = 0; j<accuracy; j++){
      // compute the jth x coordinate
      currentX = p_x - delta*w/2 + delta*w/(2* accuracy) + j*delta*w/accuracy;
      for(int k = 0; k<accuracy; k++){
        // compute the kth y coordinate
        currentY = p_y - delta*h/2 + delta*h/(2* accuracy) + k*delta*h/accuracy;

        // we compute the error err with these 2 values, we compare it to the min error
        // and if it's smaller, then we update p_x, p_y and minErr
        modified_img = original_img;
        if(floatTranslation){ modified_img.translation_f(currentX, currentY); }
        else{ modified_img.translation(std::round(currentX), std::round(currentY)); }

        err = error(modified_img, imgToFind);
        if(err-minErr < 0){
          minErr = err;
          p_x_tmp = currentX;
          p_y_tmp = currentY;
        }
      }
    }
    p_x = p_x_tmp;
    p_y = p_y_tmp;
    i++;
  }
  finalParameters(0) = p_x;
  finalParameters(1) = p_y;
  return finalParameters;
}

// algorithm : polychotomy and rotation
Eigen::VectorXf polychotomy_xy_rotation(const BWImage original_img, const BWImage imgToFind, int accuracy, bool floatTranslation){
  // idea :
  // - add gaussian when big error, and remove it at the end (when small error)
  // - reduce picture size

  unsigned int w = original_img.width(); //width of the image
  unsigned int h = original_img.height(); //height of the image
  BWImage modified_img = original_img; //making a copy of the image
  Eigen::VectorXf finalParameters(3); // output (translation from the original image)

  unsigned int i  = 0; //to start in the loop with translation parameter 1/4
  float p_x = 0; float p_y = 0; float p_theta = 0;
  float p_x_tmp = 0; float p_y_tmp = 0; float p_theta_tmp = 0;
  float currentX, currentY, currentTheta;
  float delta;
  float err;

  unsigned int m = (unsigned int)std::log(h)/std::log(accuracy) + 1;
  unsigned int n = (unsigned int)std::log(w)/std::log(accuracy) + 1; //number of effective iterations that we need in the loop
  float o = 2*PI;
  // add condition for maximal number of rotation
  float minErr = error(modified_img, imgToFind);
  while (((i < m) || ( i < n ) || (o > 0.01)) && (minErr > EPSILON)){
    delta = pow((1/(float)accuracy), i);
    // cout << "delta : " << delta << endl;
    for(int j = 0; j<accuracy; j++){
      // compute the ith x coordinate
      currentX = p_x - delta*w/2 + delta*w/(2* accuracy) + j*delta*w/accuracy;
      for(int k = 0; k<accuracy; k++){
        // compute the jth y coordinate
        currentY = p_y - delta*h/2 + delta*h/(2* accuracy) + k*delta*h/accuracy;
        for(int l = 0; l<accuracy; l++){
          // compute the kth theta rectangles
          currentTheta = p_theta - delta*PI + delta*PI/accuracy + l*delta*2*PI/accuracy;

          // we compute the error err with these 3 values
          // we compare it to the min error
          // and if it's smaller, then we update p_x, p_y, p_theta and minErr
          modified_img = original_img;
          modified_img.rotation3(currentTheta, w/2, h/2);
          if(floatTranslation){ modified_img.translation_f(currentX, currentY); }
          else{ modified_img.translation((int)std::round(currentX), (int)std::round(currentY)); }
          // cout << "-----" << endl;
          // cout <<  "(j,k,l) : (" << j << ", " << k << ", " << l << ")" << endl;
          // cout << "(x,y,theta) : (" << currentX << ", " << currentY << ", " << currentTheta << ")" << endl;
          err = error(modified_img, imgToFind);
          // display_error(modified_img, imgToFind);

          if(err<minErr){
            minErr = err;
            p_x_tmp = currentX;
            p_y_tmp = currentY;
            p_theta_tmp = currentTheta;
          }
        }
      }
    }
    p_x = p_x_tmp;
    p_y = p_y_tmp;
    p_theta = p_theta_tmp;
    o = delta*2*PI;
    i++;
  }
  finalParameters(0) = p_x;
  finalParameters(1) = p_y;
  finalParameters(2) = p_theta;
  return finalParameters;
}

// algorithm : dichotomy sth is wrong here
Eigen::VectorXf polychotomy_xy_rotation_maybeee_improved(const BWImage original_img, const BWImage imgToFind, int accuracy){
  unsigned int w = original_img.width(); //width of the image
  unsigned int h = original_img.height(); //height of the image
  BWImage img = original_img; //making a copy of the image
  Eigen::VectorXf finalParameters(3); // output (translation from the original image)

  unsigned int i  = 0; //to start in the loop with translation parameter 1/4
  float p_x = 0; float p_y = 0; float p_theta = 0;
  float p_x_tmp = 0; float p_y_tmp = 0; float p_theta_tmp = 0;
  float currentX, currentY, currentTheta;
  float delta;
  float err;

  unsigned int m = (unsigned int)std::log(h)/std::log(accuracy) + 1;
  unsigned int n = (unsigned int)std::log(w)/std::log(accuracy) + 1; //number of effective iterations that we need in the loop
  float o = 2*PI;
  // add condition for maximal number of rotation
  float minErr = error_improved(img, imgToFind);
  while (((i < m) || ( i < n ) || (o > 0.01)) && (abs(minErr) > EPSILON)){
    cout << "step : " << i << endl;
    delta = pow((1/(float)accuracy), i);
    // cout << "delta : " << delta << endl;
    for(int j = 0; j<accuracy; j++){
      // compute the ith x coordinate
      currentX = p_x - delta*w/2 + delta*w/(2* accuracy) + j*delta*w/accuracy;
      for(int k = 0; k<accuracy; k++){
        // compute the jth y coordinate
        currentY = p_y - delta*h/2 + delta*h/(2* accuracy) + k*delta*h/accuracy;
        for(int l = 0; l<accuracy; l++){
          // compute the kth theta rectangles
          currentTheta = p_theta - delta*PI + delta*PI/accuracy + l*delta*2*PI/accuracy;

          // we compute the error err with these 3 values
          // we compare it to the min error
          // and if it's smaller, then we update p_x, p_y, p_theta and minErr
          img = original_img;
          img.rotation3(currentTheta, w/2, h/2);
          img.translation(currentX, currentY);
          // cout << "-----" << endl;
          // cout <<  "(j,k,l) : (" << j << ", " << k << ", " << l << ")" << endl;
          // cout << "(x,y,theta) : (" << currentX << ", " << currentY << ", " << currentTheta << ")" << endl;
          err = error_improved(img, imgToFind);

          if(abs(abs(err) - abs(minErr)) < EPSILON){
            minErr = err;
            p_x_tmp = currentX;
            p_y_tmp = currentY;
            p_theta_tmp = currentTheta;
          }
        }
      }
    }
    p_x = p_x_tmp;
    p_y = p_y_tmp;
    p_theta = p_theta_tmp;
    o = delta*2*PI;
    i++;
  }
  finalParameters(0) = p_x;
  finalParameters(1) = p_y;
  finalParameters(2) = p_theta;
  return finalParameters;
}
