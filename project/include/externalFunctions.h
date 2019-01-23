
//#include <Eigen/Dense>
#include "image.h"

#ifndef EXTERNALFUNCTIONS_H
#define EXTERNALFUNCTIONS_H



vector<vector<float>> operator-(BWImage img1, BWImage img2);

float dist(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
float dist_an(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, float a, float b);
float optimize(BWImage img1, BWImage img2);
int greedy_algorithm_x(BWImage img1, BWImage img2);
vector<int> greedy_algorithm_xy(BWImage img1, BWImage img2);
float error(BWImage img1, BWImage img2);

#endif
