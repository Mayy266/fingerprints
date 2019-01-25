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
    CImg<unsigned char> image_input(argv[1]);
    BWImage img = BWImage(image_input);
    float rotation_angle = PI/4;
    cout << "In this part we will show some geometrical warps. We will work on rotation methods." << endl;
    cout << "We have implemented three different methods, each one is more accurate than the previous one." << endl;
    cout << "The first one is the simple rotation and we lose some information. Would you like to see the result with the image?" << endl;
    cin >> answer;
    if (answer==affirmative ||  answer == affirmative2){
      img = BWImage(image_input);
      img.rotation(rotation_angle, img.width()/2, img.height()/2);
      img.display();
    }

    cout << "The second one uses simple rotation and then bilinear interpolation to fill the lost information. Would you like to see the resultant image?" << endl;
    cin >> answer;
    if (answer==affirmative ||  answer == affirmative2){
      img = BWImage(image_input);
      img.rotation2(rotation_angle, img.width()/2, img.height()/2);
      img.display();
    }

    cout << "The third one uses inverse mapping. Would you like to see the resultant image?" << endl;
    cin >> answer;
    if (answer==affirmative ||  answer == affirmative2){
      img = BWImage(image_input);
      img.rotation3(rotation_angle, img.width()/2, img.height()/2);
      img.display();
    }

    cout << "Finally we have implemented local rotation, would you like to see the resultant image?" << endl;
    cin >> answer;
    if (answer==affirmative ||  answer == affirmative2){
      img = BWImage(image_input);
      img.local_rotation(rotation_angle, img.width()/2, 4*img.height()/5,50,1.3);
      img.display();
    }

  }

  else{
      cout << "One argument is required: path of an image" << endl;
    }




//STARTER2
  //CImg<unsigned char> image_input2(argv[2]);

  //float rotation_angle = PI/4;

  //BWImage img2 = BWImage(image_input2); //creates an instance of class BWImage
  //img1.drawRect((int)(img1.width()/2), (int)(img1.height()/2), 50, 50, 255);

  //img1.rotation(rotation_angle, img1.width()/2, img1.height()/2);
  //img1.display();

  // BWImage img_2 = BWImage(image_input); //creates an instance of class BWImage
  // img_2.rotation2(rotation_angle, img_2.width()/2, img_2.height()/2);
  // img_2.display();
  //
  // BWImage img_3 = BWImage(image_input); //creates an instance of class BWImage
  // img_3.rotation3(rotation_angle, img_3.width()/2, img_3.height()/2);
  // img_3.display();
  //img1.local_rotation(PI/2,100,150,90,1.5);
  //img_1.inverse_rotation(rotation_angle, img_1.width()/2, img_1.height()/2);
  //img_1.display();



  return 0;
}
