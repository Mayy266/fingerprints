#include "image.h"
#include "coord.h"
#include "externalFunctions.h"

using namespace cimg_library;
using namespace std;
using namespace Eigen;

int main(int argc, char const *argv[]) {
  if(argc == 2){
    CImg<unsigned char> image(argv[1]);
    BWImage img = BWImage(image);
    string answer;

    cout << "Would you like to know the maximum and minimum intensity of your image? ";
    cin >> answer;
    string affirmative = "yes";
    string affirmative2 = "Yes";
    if (answer==affirmative ||  answer == affirmative2){
      cout << "Min : " << img.minIntensity() << endl;
      cout << "Max : " << img.maxIntensity() << endl;
    }

    cout << "Would you like to draw rectangles in your image? ";
    cin >> answer;
    if (answer==affirmative ||  answer == affirmative2){
      img.drawRect(120, 100, 50, 30, 255);
      img.drawRect(10, 10, 50, 60, 0);
      img.display();
    }

    cout << "Would you like to perform a simmetry of your image with regard to x-axis? ";
    cin >> answer;
    if (answer==affirmative ||  answer == affirmative2){
      img = BWImage(image);
      img.symmetry_X();
      img.display();
    }

    cout << "Would you like to perform a simmetry of your image with regard to y-axis? ";
    cin >> answer;
    if (answer==affirmative ||  answer == affirmative2){
      img = BWImage(image);
      img.symmetry_Y();
      img.display();
    }

    cout << "Would you like to perform a diagonal simmetry of your image? ";
    cin >> answer;
    if (answer==affirmative ||  answer == affirmative2){
        img = BWImage(image);
        img.symmetry_diagonal();
        img.display();
    }

    cout << "Would you like to perform a translation of your image? ";
    cin >> answer;
    if (answer==affirmative ||  answer == affirmative2){
      cout << "Could you introduce two integer numbers for the translation? ";
      int x,y;
      cin >> x >> y;
        img = BWImage(image);
        img.translation(x,y);
        img.display();
    }

    cout << "Now, we will show different isotropic methods. If you want to see all of them answer yes. If you are just interested in the final result answer no."<< endl;
    cin >> answer;
    if (answer==affirmative ||  answer == affirmative2){
      cout << "The image corresponding to the first method is: "<<endl;
      img = BWImage(image);
      img.isotropic1((int)(img.height()/2),(int)(3*img.width()/4));
      cout << "The image corresponding to the second method is: "<<endl;
      img = BWImage(image);
      img.isotropic2((int)(img.height()/2),(int)(3*img.width()/4));
      cout << "The image corresponding to the Third method is: "<<endl;
      img = BWImage(image);
      img.isotropic3((int)(img.height()/2),(int)(3*img.width()/4));


    }
    cout << "Finally, we find Gauss function to be the most accurate one, would you like to see the image with this method?"<< endl;
    cin >> answer;
    if (answer==affirmative ||  answer == affirmative2){
      img = BWImage(image);
      img.isotropicGauss((unsigned int)(img.height()/2),(unsigned int)(3*img.width()/4), 0.001);
    }

    cout << "We have adapted Gauss isotropic function to be anisotropic, would you like to see the result image?"<< endl;
    cin >> answer;
    if (answer==affirmative ||  answer == affirmative2){
      img = BWImage(image);
      img.anisotropicGauss((int)(img.height()/2),(int)(3*img.width()/4), 0.1, 0.15,0.02);//a = 0.1, b = 0.15 simulate shape of an anisotropic fingerprint
    }
    //we can add the other functions too but it will be too long
    //img.anisotropic2((unsigned int)(img.height()/3),(unsigned int)(3*img.width()/4), 0.4, 1);// a = 0.4, b = 1 its a good example of an elipse
    //img.anisotropicGauss((unsigned int)(img.height()/3),(unsigned int)(3*img.width()/4), 0.4, 1, 0.1);
  }
  else{
      cout << "One argument is required: path of an image" << endl;
    }

  return 0;
}
