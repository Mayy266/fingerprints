//#include <Eigen/Dense>
#include "image.h"

#ifndef EXTERNALFUNCTIONS_H
#define EXTERNALFUNCTIONS_H



vector<vector<float>> operator-(BWImage img1, BWImage img2);
float optimize(BWImage img1, BWImage img2);
int greedy_algorithm_x(BWImage img1, BWImage img2);
vector<int> greedy_algorithm_xy(BWImage img1, BWImage img2);
// vector<float> most_greedy_algorithm_ever(BWImage img1, BWImage img2);

#endif
