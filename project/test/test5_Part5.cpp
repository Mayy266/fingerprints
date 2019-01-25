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


  ///////////////////


      CImg<unsigned char> image_input(argv[1]);
      //CImg<unsigned char> image_input2(argv[2]);

      float rotation_angle = PI/3;
      float xTranslation = 100.3;
      float yTranslation = -40.5;

      BWImage img1 = BWImage(image_input);
      BWImage img2 = img1;


    // *****************  TEST polychotomy_xyrotation *********************

    img2.rotation3(rotation_angle, img2.width()/2, img2.height()/2);
    img2.translation_f(xTranslation, yTranslation);

    int acccuracy = 2;
    Eigen::VectorXf v = polychotomy_xy_rotation(img1,img2,acccuracy,false);
    cout << "Without float translation : px = "<< v(0) << ", py = " << v(1) << ", theta = " << v(2) << endl;

    v = polychotomy_xy_rotation(img1,img2,acccuracy,true);
    cout << "With float translation : px = "<< v(0) << ", py = " << v(1) << ", theta = " << v(2) << endl;

    cout << "Expected result : px = "<< xTranslation << ", py = " << yTranslation << ", theta = " << rotation_angle << endl;

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
