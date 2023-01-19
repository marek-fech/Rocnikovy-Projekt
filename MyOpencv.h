#pragma once
#include"Include.h"

void addPoints(int width, int height, cv::Mat DispImage);
cv::Mat rotateImage(cv::Mat img);
int getMax(int x, int y);
void addImage(int size, int width, bool image, cv::Mat img, cv::Mat DispImage);
void ShowManyImages(std::string title, cv::Mat img1, cv::Mat img2);
