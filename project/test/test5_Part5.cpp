#include "image.h"
#include "coord.h"
#include "externalFunctions.h"

using namespace cimg_library;
using namespace std;
using namespace Eigen;

int main(int argc, char const *argv[]) {
  string affirmative = "yes";
  string affirmative2 = "Yes";
  string answer;

  if(argc == 2){
  //img1.anisotropicGauss((unsigned int)(img1.height()/3),(unsigned int)(3*img1.width()/4), 0.4, 1, 0.08);

      CImg<unsigned char> image_input(argv[1]);
      //CImg<unsigned char> image_input2(argv[2]);

      float rotation_angle = PI/3;
      float xTranslation;
      float yTranslation;

      BWImage img1 = BWImage(image_input);
      BWImage img2 = img1;
      string affirmative = "yes";
      string affirmative2 = "Yes";
      string affirmative3 = "y";
      int accuracy = 3;


      string answer;

      cout << "***********************************************************************************" << endl << endl;
      cout << "In this part we will work with two loss functions to look for an original_image given starting with one which is translated and rotated" << endl;
      cout << "To begin, we will deal with the function which gives the sum of the squared errors." << endl;
      cout << "Our first task is to find the image with a translation along x axis, would you like to see some numerical results?" << endl;
      cin >> answer;
      if (answer==affirmative ||  answer == affirmative2 || answer == affirmative3){
        BWImage img2 = img1;
        xTranslation = 101.25;
        img2.translation_f(xTranslation, 0);
        float a = polychotomy_x(img1,img2,accuracy,true);
        cout << "The expected result is " << xTranslation << ", and with accuracy "<< accuracy<< " we obtain the value x = " << a << endl << endl;
        cout << "---------------------" << endl;
      }
      /////////////////////////////////////////////////////////////////////////////////////////////////////
      //THERE IS NO POSSIBLE VALUES FOR XTRANSLATION AND YTRANSLATION THAT MAKES THE METHOD WORK PROPERLY
      ///////////////////////////////////////////////////////////////////////////////////////////////////////
      cout << "We implemented a method which also does y-axis translation and rotation in the image, do you want to see some numerical results?"<<endl;
      cin >> answer;
      if (answer==affirmative ||  answer == affirmative2 || answer == affirmative3){
        cout << "Please wait..."<<endl;
        BWImage img2 = img1;
        accuracy = 5;
        rotation_angle = -PI/3;
        xTranslation = 60.25;
        yTranslation = -20.9;
        img2.rotation3(rotation_angle, img2.width()/2, img2.height()/2);
        img2.translation_f(xTranslation, yTranslation);
        Eigen::VectorXf a= polychotomy_xy_rotation(img1,img2,accuracy,true);
        cout << "The expected result is (" << xTranslation << ", "<< yTranslation<< ", "<< rotation_angle <<"), and with accuracy "<< accuracy<< " we  obtain the values (x,y,theta) = (" << a(0)<<", "<<a(1)<<", "<<a(2)<<")." << endl << endl;
        cout << "---------------------" << endl;
      }

      cout << "Now, we will consider the function zncc-correlation. Would you like to see some results with translation and rotation?"<<endl;
      cin >> answer;
      if (answer==affirmative ||  answer == affirmative2 || answer == affirmative3){
        cout << "Please wait..."<<endl;
        BWImage img2 = img1;
        accuracy = 3;
        rotation_angle = -PI/3;
        xTranslation = 25.3;
        yTranslation = 80.56;
        img2.rotation3(rotation_angle, img2.width()/2, img2.height()/2);
        img2.translation_f(xTranslation, yTranslation);
        Eigen::VectorXf a= polychotomy_xy_rotation_improved(img1,img2,accuracy,true);
        cout << "The expected result is (" << xTranslation << ", "<< yTranslation<< ", "<< rotation_angle <<"), and with accuracy "<< accuracy<< " we  obtain the values (x,y,theta) = (" << a(0)<<", "<<a(1)<<", "<<a(2)<<")." << endl << endl;
        cout << "---------------------" << endl;
      }

      cout << "Considering the coordinate descent algorithm we can obtain more results. Would you like to see them?"<<endl;
      cin >> answer;
      if (answer==affirmative ||  answer == affirmative2 || answer == affirmative3){
        cout << "Please wait..."<<endl;
        rotation_angle = PI/3;
        xTranslation = 41.7;
        yTranslation = -20.56;
        BWImage img2 = img1;
        img2.rotation3(rotation_angle, img2.width()/2, img2.height()/2);
        img2.translation_f(xTranslation, yTranslation);
        Eigen::VectorXf a = coordinate_descent(img1,img2,0.1);
        cout << "The expected result is (" << xTranslation << ", "<< yTranslation<< ", "<< rotation_angle <<"), and we obtain the values (x,y,theta) = (" << a(0)<<", "<<a(1)<<", "<<a(2)<<")." << endl << endl;
        cout << "---------------------" << endl;
      }


      cout << "The last implemented algorithm is based on the gradient descent. Would you like to see some results?"<<endl;
      cin >> answer;
      if (answer==affirmative ||  answer == affirmative2 || answer == affirmative3){
        xTranslation = 80.7;
        yTranslation = -47.56;
        BWImage img2 = img1;
        img2.translation_f(xTranslation, yTranslation);
        Eigen::VectorXf a= gradient_descent(img1,img2, 0.0083, 0.01, 5);
        cout << "The expected result is (" << xTranslation << ", "<< yTranslation <<"), and we  obtain the values (x,y) = (" << a(0)<<", "<<a(1)<<")." << endl << endl;
        cout << "---------------------" << endl;
      }


      cout << "This is the end of the demonstration." << endl;




    // *****************  TEST polychotomy_xyrotation *********************

    // img2.rotation3(rotation_angle, img2.width()/2, img2.height()/2);
    // img2.translation_f(xTranslation, yTranslation);
    //
    // int acccuracy = 4;
    // Eigen::VectorXf v = polychotomy_xy_rotation(img1,img2,acccuracy,false);
    // cout << "Without float translation : px = "<< v(0) << ", py = " << v(1) << ", theta = " << v(2) << endl;

    // Eigen::VectorXf v = polychotomy_xy_rotation(img1,img2,acccuracy,true);
    // cout << "With float translation : px = "<< v(0) << ", py = " << v(1) << ", theta = " << v(2) << endl;
    //
    // cout << "Expected result : px = "<< xTranslation << ", py = " << yTranslation << ", theta = " << rotation_angle << endl;

    // *****************  TEST polychotomy_xyrotation_improved *********************

    // img2.rotation3(rotation_angle, img2.width()/2, img2.height()/2);
    // img2.translation_f(xTranslation, yTranslation);

    // int acccuracy = 5;
    // Eigen::VectorXf v = polychotomy_xy_rotation_improved(img1,img2,acccuracy,false);
    // cout << "Without float translation : px = "<< v(0) << ", py = " << v(1) << ", theta = " << v(2) << endl;

    // Eigen::VectorXf v = polychotomy_xy_rotation(img1,img2,acccuracy,true);


    // *****************  TEST coordinate_descent *********************
    // img2.rotation3(rotation_angle, img2.width()/2, img2.height()/2);
    // img2.translation_f(xTranslation, yTranslation);
    // Eigen::VectorXf v = coordinate_descent(img1,img2, 0.1);
    // cout << "With float translation : px = "<< v(0) << ", py = " << v(1) << ", theta = " << v(2) << endl;
    // cout << "Expected result : px = "<< xTranslation << ", py = " << yTranslation << ", theta = " << rotation_angle << endl;

    // *****************  TEST gradient_descent *********************
    // img2.rotation3(rotation_angle, img2.width()/2, img2.height()/2);
    //img2.translation_f(xTranslation, yTranslation);

    // Eigen::VectorXf v;
    // float bestDist,  dist;
    // bestDist = 999999999;
    // for(float epsilon = 0.1; epsilon < 0.5; epsilon += 0.1){
    //   cout << epsilon << endl;
    //   for(float alpha = 0.0082; alpha < 0.0084; alpha += 0.00005){
    //     v = gradient_descent(img1,img2, alpha, epsilon, 5);
    //     dist = pow(v(0)-xTranslation, 2) + pow(v(1)-yTranslation, 2);    //calculating distance
    //     dist = sqrt(dist);
    //     if(dist<bestDist){
    //       bestDist = dist;
    //       cout << "------------------------" << endl;
    //       cout << "New best parameters : " << endl;
    //       cout << "Epsilon : " << epsilon << endl;
    //       cout << "Alpha : " << alpha << endl;
    //       cout << "(distance : " << dist << ")" << endl;
    //     }
    //   }
    // } // gap 5, epsilon 0.1, alpha 0.0083


  //  Eigen::VectorXf v = gradient_descent(img1,img2, 0.0083, 0.01, 5);
  //  cout << "With float translation : px = "<< v(0) << ", py = " << v(1) << endl;
  //  cout << "Expected result : px = "<< xTranslation << ", py = " << yTranslation << endl;

    // *****************  TEST polychotomy_xy *********************
    // img2.translation_f(65.5, -40.7);
    // int acccuracy = 7;
    // Eigen::VectorXf v = polychotomy_xy(img1,img2,acccuracy,false);
    // cout << "px = "<< v(0) << ", py = " << v(1) << endl;
    //
    // v = polychotomy_xy(img1,img2,acccuracy,true);
    // cout << "px = "<< v(0) << ", py = " << v(1) << endl;

  /*
  img2 = original_img;
  img2.translation(xTranslation,0);

  int px2 = greedy_algorithm_x_improved(original_img,img2);
  cout << "px2 = "<< px2 << endl;
  //VectorXf v2(2);
  // v2 = greedy_algorithm_x_improved(original_img, img2);
  // cout << "px improved = "<< v2(0) << ", py improved = " << v2(1) << endl;

  //int px = greedy_algorithm_x(img1,img2)
*/
  //cout << "px = "<< px(0) <<", " << px(1) << endl;
  //cout << "py = "<< py(0) << ", " << py(1)<<endl;
  //float mean = meanIntensity(img1);
  //cout << "mean = " << mean << endl;
  //img1.display();
  //cout << img1 - img1 << endl;
  //matrixToImage(img1 - img1).display();
  //float a = error_improved(img1, img2);
  //float b = error(img1, img2);
  //cout << "error "//img1.anisotropicGauss((unsigned int)(img1.height()/3),(unsigned int)(3*img1.width()/4), 0.4, 1, 0.08);




  }
  else{
    cout << "One argument needed"<< endl;
  }
  return 0;
}
