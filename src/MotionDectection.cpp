/*
 * MotionDectection.cpp
 *
 *  Created on: 16 avr. 2013
 *      Author: JC
 */

#include "MotionDectection.h"

namespace cv {
//============================================================================
// Name        : EM1.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
////#include<opencv2/opencv.hpp>
////#include<iostream>
////#include<vector>
////#include "opencv2/video/background_segm.hpp"
////#include "opencv2/legacy/blobtrack.hpp"
////#include "opencv2/legacy/legacy.hpp"
////#include "opencv2/highgui/highgui.hpp"
////#include <opencv2/imgproc/imgproc_c.h>
////#include <stdio.h>
////#include <stdlib.h>
////#include <ctype.h>
////#include <fstream>
////#include <math.h>
////#include "cvBlob/cvblob.h"
////
////using namespace std;
////using namespace cvb;
////using namespace cv;
////
////
////CascadeClassifier cascade;
////vector<Rect> faces;
////vector<Rect> windows;
////
////
////void invert (Mat* img){
////	img->inv(0);
////}
////
////void invert (IplImage* img)
////{
////
////  uchar *p, *line;
////  assert (img->depth == IPL_DEPTH_8U && img->nChannels == 1); //en gris 8 bit
////  // parcours des lignes de l'image
//  // on positionne le pointeur "line" sur le début de l'image
//  // et on le fait avancer de la taille d'une ligne à chaque itération
//  // jusqu'à tomber sur l'octet suivant le dernier pixel de l'image
//  for (line = (uchar*) img->imageData;
//       line < (uchar*) img->imageData + img->imageSize;
//       line += img->widthStep)
//    {
//      // parcours de la ligne "line"
//      // on positionne le pointeur p sur le début de la ligne
//      // et on le fait avancer de la taille d'un pixel à chaque itération
//      // jusqu'à tomber sur le dernier pixel de la ligne
//      for (p = line; p < line + img->width; ++p)
//	*p = 255 - *p;
//
//    }
//}
//
//
//
//int main(int argc, char *argv[])
//{
//	  VideoCapture cap(-1); // remplacer 0 par f si positionné.
//
//	  if (!cap.isOpened())
//	    return -1;
//
//	  namedWindow("[Eyes Motion]", CV_WINDOW_AUTOSIZE);
//	  namedWindow("Background", CV_WINDOW_AUTOSIZE);
//	  namedWindow("Actual Frame", CV_WINDOW_AUTOSIZE);
//      moveWindow("[Eyes Motion]", 50,200);
//      moveWindow("Background", 0, 500);
//	  Scalar colorDelim = Scalar(0,255,0);
//	  int sizeStrokeDelim = 1;
//	  double threshold = 18.0;
//	  std::vector<std::vector<cv::Point> > contours;
//
//
//    cv::BackgroundSubtractorMOG2 bg(5, threshold-5);
//
//	  Mat img;
//	  cap >> img;
//	  cv::Mat bground, pImg ,tmp;
//	  img.copyTo(pImg);
//	  img.copyTo(tmp);
//	  cvtColor(tmp, tmp, CV_BGR2GRAY);
//	  while (true)
//	    {
//
//		  Mat m;
//	      cap >> img;
//	      if (img.empty())
//	    	  continue;
//	      blur(img , img,  Size(3,3));
//
//	      absdiff(pImg, img, m);
//	      Mat gray;
//	      blur(m , m,  Size(3,3));
//	      m.copyTo(bground);
//	      cv::cvtColor(bground, bground, CV_BGR2GRAY);
//	      cv::cvtColor(m, gray, CV_BGR2GRAY);
//	      cv::threshold(gray, gray, 10, 255, THRESH_BINARY_INV );
//	      blur(gray, gray,  Size(5,5));
//	      cv::erode(gray, gray, cv::Mat());
//	      cv::dilate(gray, gray, cv::Mat());
//	      cv::findContours(gray, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);
//	      cv::drawContours(bground, contours, -1, cv::Scalar(0,0,205),4);
//	      blur(bground, bground,  Size(5,5));
//	      cv::threshold(bground, bground, 18, 255, THRESH_BINARY_INV );
//	      cv::findContours(bground, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);
//	      cv::drawContours(img, contours, -1, cv::Scalar(0,0,105),2);
//
//	      cout << "NB ct : " << contours.size() << endl;
//	      imshow("[Eyes Motion]", m);
//	      imshow("Background", img);
//	      img.copyTo(pImg);
//	      img = Mat();
//	      cv::cvtColor(bground, bground, CV_GRAY2BGR);
//	      if (waitKey(10) >= 0)
//	    	  break;
//	    }
//	  return 0;
//
//}
//

MotionDectection::MotionDectection() {
	// TODO Auto-generated constructor stub

}

MotionDectection::~MotionDectection() {
	// TODO Auto-generated destructor stub
}

} /* namespace cv */
