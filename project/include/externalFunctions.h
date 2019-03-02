
//#include <Eigen/Dense>
#include "image.h"

#ifndef EXTERNALFUNCTIONS_H
#define EXTERNALFUNCTIONS_H

float dist(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
float dist_an(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, float a, float b);
float polychotomy_x(const BWImage& original_img, const BWImage& imgToFind, int accuracy, bool floatTranslation);
Eigen::VectorXf polychotomy_xy(const BWImage& original_img, const BWImage& imgToFind, int accuracy, bool floatTranslation);
Eigen::VectorXf polychotomy_xy_rotation(const BWImage& original_img, const BWImage& imgToFind, int accuracy, bool floatTranslation);
Eigen::VectorXf polychotomy_xy_rotation_improved(const BWImage& original_img, const BWImage& imgToFind, int accuracy, bool floatTranslation);
Eigen::VectorXf coordinate_descent(const BWImage& original_img, const BWImage& imgToFind, float alpha);
void display_error(const BWImage& img1, const BWImage& img2);
float error(const BWImage& img1, const BWImage& img2);
float zncc_correlation(const BWImage& img1, const BWImage& img2);
float zncc_correlation_local(const BWImage& img1, const BWImage& img2);
float meanIntensity(const BWImage& img);

Eigen::VectorXf gradient_error(const BWImage& imgToFind, const BWImage& modified_img, int gap);
Eigen::VectorXf gradient_descent(const BWImage& original_img, const BWImage& imgToFind, float alpha, float epsilon, int gap);

#endif
