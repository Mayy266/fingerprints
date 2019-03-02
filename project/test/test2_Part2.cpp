#include "image.h"
#include "coord.h"
#include "externalFunctions.h"

using namespace cimg_library;
using namespace std;

int main(int argc, char const *argv[]) {
  string affirmative = "yes";
  string affirmative2 = "Yes";
  string affirmative3 = "y";

  string answer;

  if(argc == 2){
    CImg<unsigned char> image_input(argv[1]);
    BWImage img = BWImage(image_input);
    float rotation_angle = PI/4;

    cout << "***********************************************************************************" << endl;
    cout << "In this part we will show some geometrical warps. We will work on rotation methods." << endl;
    cout << "We have implemented three different methods, each one is more accurate than the previous one." << endl;

    //*************** ROTATION
    cout << "The first one is the simple rotation and we lose some information. Would you like to see the result with the image?" << endl;
    cin >> answer;
    img = BWImage(image_input);
    cout <<"first";
    if (answer==affirmative ||  answer == affirmative2 || answer == affirmative3){
      cout<<"second";
      img = BWImage(image_input);
      cout<<"third";
      img.rotation(rotation_angle, img.width()/2, img.height()/2);
      cout<<"fourth";
    }

    //*************** ROTATION2
    cout << "The second one uses inverse mapping. Would you like to see the resultant image?" << endl;
    cin >> answer;
    if (answer==affirmative ||  answer == affirmative2 || answer == affirmative3){
      img = BWImage(image_input);
      img.rotation3(rotation_angle, img.width()/2, img.height()/2);
      img.display();
      // img.rotation3(-rotation_angle, img.width()/2, img.height()/2);


      // BWImage original_img = BWImage(image_input);
      //
      // img = original_img;
      // img.rotation3(rotation_angle, img.width()/2, img.height()/2);
      // img.rotation3(-rotation_angle, img.width()/2, img.height()/2);
      // cout << "Error rotation3 : " << zncc_correlation_local(original_img, img) << endl;
      //
      // img = original_img;
      // img.rotation2(rotation_angle, img.width()/2, img.height()/2);
      // img.rotation2(-rotation_angle, img.width()/2, img.height()/2);
      // cout << "Error rotation2 : " << zncc_correlation_local(original_img, img) << endl;
    }


    //*************** ROTATION3
    cout << "The third one uses simple rotation and then bilinear interpolation to fill the lost information. Would you like to see the resultant image?" << endl;
    cin >> answer;
    if (answer==affirmative ||  answer == affirmative2 || answer == affirmative3){
      img = BWImage(image_input);
      img.rotation3(rotation_angle, img.width()/2, img.height()/2);
      img.display();
    }


    //*************** LOCAL_ROTATION
    cout << "Finally we have implemented a local rotation, would you like to see the resultant image?" << endl;
    cin >> answer;
    if (answer==affirmative ||  answer == affirmative2 || answer == affirmative3){
      img = BWImage(image_input);
      img.local_rotation(rotation_angle, img.width()/2, 4*img.height()/5,60,1.2);
      img.display();
    }

    cout << "This is the end of the demonstration for the second part. Now, you can execute the next part or try some methods by yourself." << endl;
  }
  else {
    cout << "One argument is required: path of an image." << endl;
  }
  return 0;
}
