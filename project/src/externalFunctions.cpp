#include "externalFunctions.h"
using namespace cimg_library;
using namespace std;


/**
 * \fn float dist(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2)
 * \brief Computes the distance between two points
 * \param x1 the x-axis coordinate of the first point.
 * \param y1 the y-axis coordinate of the first point.
 * \param x2 the x-axis coordinate of the second point.
 * \param y2 the y-axis coordinate of the second point.
 * \return the euclidian distance between the 2 given points.
 */
float dist(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2){
  int x = (x1 - x2); //calculating number to square in next step
  int y = (y1 - y2);
  float dist;
  dist = pow(x, 2) + pow(y, 2);    //calculating distance
  dist = sqrt(dist);
  return dist;
}



/**
 * \fn float dist_an(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, float a, float b)
 * \brief Computes the elliptic distance between two points
 * \param x1 the x-axis coordinate of the first point.
 * \param y1 the y-axis coordinate of the first point.
 * \param x2 the x-axis coordinate of the second point.
 * \param y2 the y-axis coordinate of the second point.
 * \param a parameter for the elliptical distance  
 * \param b parameter for the elliptical distance
 * \return the elliptic distance between the 2 given points.
 */
float dist_an(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, float a, float b) {
    int x = (x1 - x2); //calculating number to square in next step
    int y = (y1 - y2);
    float dist;
    dist = pow(x, 2)/a + pow(y, 2)/b;    //calculating elliptic distance depending on a and b
    dist = sqrt(dist);

    return dist;
}









/**
 * \fn void display_error(const BWImage& img1, const BWImage& img2)
 * \brief Displays the error image, using 2 given images.
 * \param img1 the first image
 * \param img2 the second image
 */
void display_error(const BWImage& img1, const BWImage& img2){
  assert(img2.height() == img1.height() && img2.width() == img1.width());
  BWImage error_img(img1); //making a copy of the image to display the error

  for (unsigned int i = 0; i < img1.width(); i++){
    for (unsigned int j = 0; j < img1.height(); j++){
      error_img.setIntensity(i,j,abs(img1.getIntensity(i,j)-img2.getIntensity(i,j)));
    }
  }
  error_img.display();
}


/**
 * \fn float error(const BWImage& img1, const BWImage& img2)
 * \brief Computes the numeric error between 2 given images (sum of the square of the difference of the pixels).
 * \param img1 the first image
 * \param img2 the second image
 * \return the numeric error between the 2 given images
 */
float error(const BWImage& img1, const BWImage& img2){
  assert(img2.height() == img1.height() && img2.width() == img1.width());
  float error = 0;
  for (unsigned int i = 0; i < img1.width(); i++){
    for (unsigned int j = 0; j < img1.height(); j++){
      error += pow(img1.toFloat(i,j)-img2.toFloat(i,j), 2);
    }
  }
  return error;
}


/**
 * \fn float zncc_correlation(const BWImage& img1, const BWImage& img2)
 * \brief Computes the correlation between 2 given images.
 * \param img1 the first image
 * \param img2 the second image
 * \return the correlation between the 2 given images
 */
float zncc_correlation(const BWImage& img1, const BWImage& img2){
  assert(img2.height() == img1.height() && img2.width() == img1.width());
  float meanImg1 = meanIntensity(img1);
  float meanImg2 = meanIntensity(img2);
  float numerator = 0;
  float denominatorF = 0;
  float denominatorG = 0;
  float F = 0;
  float G = 0;
  float correlation;

  for(unsigned int i = 0; i < img1.width(); i++){
    for(unsigned int j = 0; j < img1.height(); j++){
      F = img1.toFloat(i,j) - meanImg1;
      G = img2.toFloat(i,j) - meanImg2;
      numerator += F*G;
      denominatorF += pow(F,2);
      denominatorG += pow(G,2);
    }
  }
  correlation = numerator/sqrt(denominatorF*denominatorG);
  return correlation;
}



/**
 * \fn float zncc_correlation_local(const BWImage& img1, const BWImage& img2)
 * \brief Computes the correlation between 2 given images, but only in a specific area (used to compare the rotation functions).
 * \param img1 the first image
 * \param img2 the second image
 * \return the correlation between the 2 given images, but only in a specific area.
 */
float zncc_correlation_local(const BWImage& img1, const BWImage& img2){
  assert(img2.height() == img1.height() && img2.width() == img1.width());
  BWImage error_img(img1); //making a copy of the image to display the error
  float meanImg1 = meanIntensity(img1);
  float meanImg2 = meanIntensity(img2);
  float numerator = 0;
  float denominatorF = 0;
  float denominatorG = 0;
  float F = 0;
  float G = 0;
  float correlation;

  for(unsigned int i = 6*img1.width()/27; i < 20*img1.width()/27; i++){
    for(unsigned int j = img1.height()/3; j < 24*img1.height()/27; j++){
      F = img1.toFloat(i,j) - meanImg1;
      G = img2.toFloat(i,j) - meanImg2;
      numerator += F*G;
      denominatorF += pow(F,2);
      denominatorG += pow(G,2);
      error_img.setIntensity(i,j,abs(img1.getIntensity(i,j)-img2.getIntensity(i,j)));
    }
  }
  correlation = numerator/sqrt(denominatorF*denominatorG);
  error_img.display();
  error_img.save("../project/output_images/local_error.png"); //saves the new image


  return correlation;
}




/**
 * \fn float meanIntensity(const BWImage& img)
 * \brief Gives the mean intensity of the image, returns value between 0 and 1
 * \param img an image
 * \return the mean intensity of the given image (value between 0 and 1)
 */
float meanIntensity(const BWImage& img){
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


/**
 * \fn float polychotomy_x(const BWImage& original_img, const BWImage& imgToFind, int accuracy, bool floatTranslation)
 * \brief Finds the x-translation parameter of a x-translated image using polychotomy
 * \param original_img the original image, before the x translation.
 * \param imgToFind the image we are looking for.
 * \param accuracy the polychotomy parameter (for instance, an accuracy 2 means we will use dichotomy). An higher accuracy generally gives more accurate results, but take more time to run.
 * \param floatTranslation true if we want to be able to translate by float values, false else.
 * \return the x-translation parameter of the given x-translated image.
 */
float polychotomy_x(const BWImage& original_img, const BWImage& imgToFind, int accuracy, bool floatTranslation){
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




/**
 * \fn Eigen::VectorXf polychotomy_xy(const BWImage& original_img, const BWImage& imgToFind, int accuracy, bool floatTranslation)
 * \brief Finds the x and y translation parameters of a translated image using polychotomy
 * \param original_img the original image, before the translation.
 * \param imgToFind the image we are looking for.
 * \param accuracy the polychotomy parameter (for instance, an accuracy 2 means we will use dichotomy). An higher accuracy generally gives more accurate results, but take more time to run.
 * \param floatTranslation true if we want to be able to translate by float values, false else.
 * \return the x and y translation parameters of the given translated image.
 */
Eigen::VectorXf polychotomy_xy(const BWImage& original_img, const BWImage& imgToFind, int accuracy, bool floatTranslation){
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





/**
 * \fn Eigen::VectorXf polychotomy_xy_rotation(const BWImage& original_img, const BWImage& imgToFind, int accuracy, bool floatTranslation)
 * \brief Finds the x and y translation parameters and the rotation parameter of a translated and rotated image using polychotomy
 * \param original_img the original image, before the translation and rotation.
 * \param imgToFind the image we are looking for.
 * \param accuracy the polychotomy parameter (for instance, an accuracy 2 means we will use dichotomy). An higher accuracy generally gives more accurate results, but take more time to run.
 * \param floatTranslation true if we want to be able to translate by float values, false else.
 * \return the x and y translation parameters and the rotation parameter of the given image.
 */
Eigen::VectorXf polychotomy_xy_rotation(const BWImage& original_img, const BWImage& imgToFind, int accuracy, bool floatTranslation){

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




/**
 * \fn Eigen::VectorXf polychotomy_xy_rotation_improved(const BWImage& original_img, const BWImage& imgToFind, int accuracy, bool floatTranslation)
 * \brief Finds the x and y translation parameters and the rotation parameter of a translated and rotated image using polychotomy, using the correlation function to compare the image we are looking for and the image we are moving.
 * \param original_img the original image, before the translation and rotation.
 * \param imgToFind the image we are looking for.
 * \param accuracy the polychotomy parameter (for instance, an accuracy 2 means we will use dichotomy). An higher accuracy generally gives more accurate results, but take more time to run.
 * \param floatTranslation true if we want to be able to translate by float values, false else.
 * \return the x and y translation parameters and the rotation parameter of the given image.
 */
Eigen::VectorXf polychotomy_xy_rotation_improved(const BWImage& original_img, const BWImage& imgToFind, int accuracy, bool floatTranslation){
  unsigned int w = original_img.width(); //width of the image
  unsigned int h = original_img.height(); //height of the image
  BWImage modified_img = original_img; //making a copy of the image
  Eigen::VectorXf finalParameters(3); // output (translation from the original image)

  unsigned int i  = 0; //to start in the loop with translation parameter 1/4
  float p_x = 0; float p_y = 0; float p_theta = 0;
  float p_x_tmp = 0; float p_y_tmp = 0; float p_theta_tmp = 0;
  float currentX, currentY, currentTheta;
  float delta;
  float correlation;

  unsigned int m = (unsigned int)std::log(h)/std::log(accuracy) + 1;
  unsigned int n = (unsigned int)std::log(w)/std::log(accuracy) + 1; //number of effective iterations that we need in the loop
  float o = 2*PI;
  // add condition for maximal number of rotation
  float maxCorrelation = zncc_correlation(modified_img, imgToFind);
  while (((i < m) || ( i < n ) || (o > 0.01)) && (maxCorrelation > EPSILON)){
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

          // we compute the correlation with these 3 values
          // we compare it to the max correlation
          // and if it's smaller, then we update p_x, p_y, p_theta and maxCorrelation
          modified_img = original_img;
          modified_img.rotation3(currentTheta, w/2, h/2);
          if(floatTranslation){ modified_img.translation_f(currentX, currentY); }
          else{ modified_img.translation((int)std::round(currentX), (int)std::round(currentY)); }
          correlation = zncc_correlation(modified_img, imgToFind);
          // display_error(modified_img, imgToFind);

          if(correlation>maxCorrelation){ // maximizing the function
            maxCorrelation = correlation;
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




/**
 * \fn Eigen::VectorXf coordinate_descent(const BWImage& original_img, const BWImage& imgToFind, float alpha)
 * \brief find the rotation and translation parameters of an image using coordinate descent
 * \param original_img the original image, before the translation and rotation.
 * \param imgToFind the image we are looking for.
 * \param alpha the original movement coefficient value (to initialize the algorithm)
 * \return the rotation and translation parameters of the given image
 */
Eigen::VectorXf coordinate_descent(const BWImage& original_img, const BWImage& imgToFind, float alpha){
  unsigned int w = original_img.width(); //width of the image
  unsigned int h = original_img.height(); //height of the image
  BWImage modified_img = original_img; //making a copy of the image
  Eigen::VectorXf finalParameters(3); // output (translation from the original image)

  float p_x = 0; float p_y = 0; float p_theta = 0;
  float p_x_tmp = 0; float p_y_tmp = 0; float p_theta_tmp = 0;
  float currentX, currentY, currentTheta;
  float alphaX = alpha; float alphaY = alpha; float alphaTheta = alpha;
  float alphaX_tmp, alphaY_tmp, alphaTheta_tmp;
  float correlation;


  // add condition for maximal number of rotation
  float maxCorrelation = zncc_correlation(modified_img, imgToFind);
  float  globalMaximumCorrelation = maxCorrelation; // we use globalMaximumCorrelation in the gaussian, it is increasing the closer w get to the solution
  while ((alphaX > 0.00001) || (alphaY > 0.00001) || (alphaTheta > 0.00001) ){ // we stop when we are accurate enough
    // *****  For x-axis : *****
    maxCorrelation = -1; //maxCorrelation takes values between -1 and 1, so the minimum is -1
    for(int xOrientation = -1; xOrientation<=1; xOrientation++){
      // compute the ith x coordinate
      currentX = p_x + w*alphaX*xOrientation;
      modified_img = original_img;
      modified_img.isotropicGauss(modified_img.width()/2, modified_img.height()/2,(1-globalMaximumCorrelation)/10000.0); //the parameter decreases here
      modified_img.rotation3(p_theta, w/2, h/2);
      modified_img.translation_f(currentX, p_y);
      correlation = zncc_correlation(modified_img, imgToFind);
      // display_error(imgToFind, modified_img);
      if(correlation>maxCorrelation){ // maximizing the function
        maxCorrelation = correlation;
        p_x_tmp = currentX;
        alphaX_tmp = alphaX * (xOrientation == 0 ? 0.5 : 1.1);
      }
    }
    p_x = p_x_tmp;
    alphaX = alphaX_tmp;
    if(globalMaximumCorrelation < maxCorrelation){
      globalMaximumCorrelation = maxCorrelation;
    }

    // *****  For y-axis : *****
    maxCorrelation = -1;
    for(int yOrientation = -1; yOrientation<=1; yOrientation++){
      // compute the ith x coordinate
      currentY = p_y + h*alphaY*yOrientation;
      modified_img = original_img;
      modified_img.isotropicGauss(modified_img.width()/2, modified_img.height()/2, (1-globalMaximumCorrelation)/10000.0);
      modified_img.rotation3(p_theta, w/2, h/2);
      modified_img.translation_f(p_x, currentY);
      correlation = zncc_correlation(modified_img, imgToFind);
      // display_error(imgToFind, modified_img);
      if(correlation>maxCorrelation){ // maximizing the function
        maxCorrelation = correlation;
        p_y_tmp = currentY;
        alphaY_tmp = alphaY * (yOrientation == 0 ? 0.5 : 1.1);
      }
    }
    p_y = p_y_tmp;
    alphaY = alphaY_tmp;
    if(globalMaximumCorrelation < maxCorrelation){
      globalMaximumCorrelation = maxCorrelation;
    }

    // *****  For rotation angle : *****
    maxCorrelation = -1;
    for(int thetaOrientation = -1; thetaOrientation<=1; thetaOrientation++){
      // compute the ith x coordinate
      currentTheta = p_theta + PI*alphaTheta*thetaOrientation;
      modified_img = original_img;
      modified_img.isotropicGauss(modified_img.width()/2, modified_img.height()/2, (1-globalMaximumCorrelation)/10000.0);
      modified_img.rotation3(currentTheta, w/2, h/2);
      modified_img.translation_f(p_x, p_y);
      correlation = zncc_correlation(modified_img, imgToFind);
      // display_error(imgToFind, modified_img);
      if(correlation>maxCorrelation){ // maximizing the function
        maxCorrelation = correlation;
        p_theta_tmp = currentTheta;
        alphaTheta_tmp = alphaTheta * (thetaOrientation == 0 ? 0.5 : 1.1);
      }
    }
    p_theta = p_theta_tmp;
    alphaTheta = alphaTheta_tmp;
  }

  finalParameters(0) = p_x;
  finalParameters(1) = p_y;
  finalParameters(2) = p_theta;
  return finalParameters;
}





/**
 * \fn Eigen::VectorXf gradient_error(const BWImage& imgToFind, const BWImage& modified_img, int gap)
 * \brief compute the gradient of the error function
 * \param imgToFind the image we are looking for.
 * \param modified_img the image we are moving.
 * \param gap the distance between 2 points to compute the derivative
 * \return the gradient of the error function
 */
Eigen::VectorXf gradient_error(const BWImage& imgToFind, const BWImage& modified_img, int gap){
  assert(imgToFind.height() == modified_img.height() && imgToFind.width() == modified_img.width());
  float xDerivative, yDerivative;
  Eigen::VectorXf finalParameters(2);
  float gradX = 0; float gradY = 0;
  for (unsigned int i = gap; i < imgToFind.width()-gap; i++){
    for (unsigned int j = gap; j < imgToFind.height()-gap; j++){
      xDerivative = (modified_img.toFloat(i-gap,j) - modified_img.toFloat(i+gap,j))/(2.0*gap);
      yDerivative = (modified_img.toFloat(i,j-gap) - modified_img.toFloat(i,j+gap))/(2.0*gap);
      gradX = gradX + 2*xDerivative*(modified_img.toFloat(i,j)-imgToFind.toFloat(i,j));
      gradY = gradY + 2*yDerivative*(modified_img.toFloat(i,j)-imgToFind.toFloat(i,j));
    }
  }
  finalParameters(0) = gradX;
  finalParameters(1) = gradY;
  return finalParameters;
}



/**
 * \fn Eigen::VectorXf gradient_descent(const BWImage& original_img, const BWImage& imgToFind, float alpha, float epsilon, int gap)
 * \brief find the translation parameter of an image using gradient descent
 * \param original_img the original image, before the translation and rotation.
 * \param imgToFind the image we are looking for.
 * \param alpha a coefficient to calibrate the gradient scale.
 * \param epsilon the accuracy parameter (the algorithm stop if the values of the gradient are smaller than this parameter).
 * \param gap the distance between 2 points to compute the derivative
 * \return the translation parameter of the given image
 */
Eigen::VectorXf gradient_descent(const BWImage& original_img, const BWImage& imgToFind, float alpha, float epsilon, int gap){
  BWImage modified_img = original_img; //making a copy of the image
  Eigen::VectorXf finalParameters(2); // output (translation from the original image)
  Eigen::VectorXf grad(2);
  float p_x = 0; float p_y = 0; // translation parameters
  float gradX = 100*epsilon; float gradY = 100*epsilon; // we initialize with a value big enough to go into the while loop
  int nbLoop = 0;
  while (((abs(gradX) > epsilon) || (abs(gradY) > epsilon)) && (nbLoop<150)){ // we stop when we are accurate enough
    // cout << "---------------------------------------------------" << endl;
    // cout << "Loop " << nbLoop << " : " << endl;
    // cout << "(px, py) : (" << p_x << ", " << p_y << ")" << endl;
    modified_img = original_img;
    modified_img.translation_f(p_x, p_y);
    // display_error(modified_img,imgToFind);
    grad = gradient_error(imgToFind, modified_img, gap);
    gradX = grad(0); gradY = grad(1);
    // cout << "new (gradX, gradY) : (" << gradX << ", " << gradY << ")" << endl;
    p_x -= alpha*gradX;
    p_y -= alpha*gradY;
    nbLoop++;
  }

  finalParameters(0) = p_x;
  finalParameters(1) = p_y;
  return finalParameters;
}
