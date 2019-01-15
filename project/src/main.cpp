#include "image.h"
#include "coord.h"

int main(int argc, char const *argv[]) {
  //STARTER1
  //CImg<unsigned char> image("clean_finger_small.png");
  CImg<unsigned char> image(argv[1]);
  //CImg<unsigned char> image2(argv[2]);

  BWImage img = BWImage(image); //creates an instance of class BWImage
  //BWImage img2 = BWImage(image2); //creates an instance of class BWImage

  //cout << optimize(img, img2) << '\n';
  //CImg<unsigned char> image("clean_finger.png");
  //cout << "Min : " << img.minIntensity() << endl;
  //cout << "Max : " << img.maxIntensity() << endl;
  //img.drawRect(30, 40, 50, 30, 255);
  //img.drawRect(10, 10, 50, 60, 0);
  //img.display();
  //img.symmetry_X();
  //img.symmetry_Y();
  //img.symmetry_diagonal();

  //img.translation(40,44);

  //MAIN1- FOR ISOTROPIC AND ANISOTROPIC
  //img = BWImage(image);
  //img.isotropic1((int)(img.height()/2),(int)(3*img.width()/4));
  //img = BWImage(image);
  //img.isotropic2((int)(img.height()/2),(int)(3*img.width()/4));
  //img = BWImage(image);
  //img.isotropic3((int)(img.height()/2),(int)(3*img.width()/4));
  //img.drawRect((int)(img.height()/2), (int)(3*img.width()/4), 7, 7, 255); //center of pressure
  //img.anisotropic((int)(img.height()/2),(int)(3*img.width()/4), 0.1, 0.15);//a = 0.1, b = 0.15 simulate shape of an anisotropic fingerprint
  //img = BWImage(image);
  //img.anisotropic2((unsigned int)(img.height()/3),(unsigned int)(3*img.width()/4), 0.4, 1);// a = 0.4, b = 1 its a good example of an elipse
  img.anisotropicGauss((unsigned int)(img.height()/3),(unsigned int)(3*img.width()/4), 0.4, 1, 0.1);

//STARTER 5
  //img.translation(50, 0);
  //img.translation(-50, 0);
  img.display();
  return 0;
}
