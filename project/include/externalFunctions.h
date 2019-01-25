
//#include <Eigen/Dense>
#include "image.h"

#ifndef EXTERNALFUNCTIONS_H
#define EXTERNALFUNCTIONS_H



Eigen::MatrixXf operator-(BWImage img1, BWImage img2);

float dist(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
float dist_an(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, float a, float b);
float polychotomy_x(const BWImage original_img, const BWImage imgToFind, int accuracy, bool floatTranslation);
Eigen::VectorXf polychotomy_xy(const BWImage original_img, const BWImage imgToFind, int accuracy, bool floatTranslation);
Eigen::VectorXf polychotomy_xy_rotation(const BWImage original_img, const BWImage imgToFind, int accuracy, bool floatTranslation);
Eigen::VectorXf polychotomy_xy_rotation_maybeee_improved(const BWImage original_img, const BWImage imgToFind, int accuracy);
void display_error(const BWImage img1, const BWImage img2);
float error(const BWImage img1, const BWImage img2);
float error_improved(const BWImage img1, const BWImage img2);
float meanIntensity(const BWImage img);


#endif
