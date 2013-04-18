/*
 * MotionDectection.h
 *
 *  Created on: 16 avr. 2013
 *      Author: JC
 */

#ifndef MOTIONDECTECTION_H_
#define MOTIONDECTECTION_H_

namespace cv {

class MotionDectection {
public:
	MotionDectection();
	virtual ~MotionDectection();
};

} /* namespace cv */
#endif /* MOTIONDECTECTION_H_ */

// Version de detection ou j'extrait les personnes pour afficher dans img
//void invert (IplImage* img)
//{
//
//  uchar *p, *line;
//  assert (img->depth == IPL_DEPTH_8U && img->nChannels == 1); //en gris 8 bit
//  // parcours des lignes de l'image
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
//void drawRect(vector<Point> &pts, Mat &img){
//	int i = 1, n = pts.size() ;
//	std::vector<cv::Point>::iterator it;
//	Point ctr;
//	int sumX = 0, sumY = 0;
//	for(it = pts.begin(); it != pts.end() && i < n; ++it){
//		sumX += it->x;
//		sumY += it->y;
//	}
//	ctr.x = sumX/n;
//	ctr.y = sumY/n;
//	rectangle(
//	            img,
//	            Point(ctr.x-15, ctr.y-25),
//	            Point(ctr.x +15, ctr.y + 25),
//	            CV_RGB(0,200,0)
//	        );
//}
//
//void prtsp(vector<vector<cv::Point> > &ct, Mat &img){
//	int i = 1, n = ct.size() ;
//	std::cout << "NB calculé : " << n << endl;
//	if(ct.size() == 1) return;
//	 std::vector<std::vector<cv::Point> >::iterator it;
//	 for(it = ct.begin(); it != ct.end() && i < n; ++it){
//		 if(it->size() > 20){
//			 cout << "\tForme " << i << " : " << it->size() << " points : " << endl;
//			 drawRect(*it, img);
//		 }else{
//			 if(!it->empty()){
//				 it->clear();
//				 ct.erase(it);
//			 }
//		 }
//		 i++;
//	 }
//}
//
//
//int main(int argc, char *argv[])
//{
//	  VideoCapture cap("/Users/JC/Desktop/tests/TownCentreXVIDWEB.m4v"); // remplacer 0 par f si positionné.
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
//
//	  int i = 0;
//	  while (true)
//	    {
//
//		  Mat m;
//		  if(++i%1000 == 0)
//			  cap >> img;
//	      if (img.empty())
//	    	  continue;
//
//	      absdiff(img, pImg, m);
//	      Mat gray;
//	      img.copyTo(pImg);
//	      blur(m , m,  Size(3,3));
//	      m.copyTo(bground);
//	      cv::cvtColor(bground, bground, CV_BGR2GRAY);
//	      cv::cvtColor(m, gray, CV_BGR2GRAY);
//	      cv::threshold(gray, gray, threshold-12, 255, THRESH_BINARY_INV );
//	      blur(gray, gray,  Size(1,1));
//	      cv::erode(gray, gray, cv::Mat());
//	      cv::dilate(gray, gray, cv::Mat());
//	      cv::findContours(gray, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);
//
//	      std::cout << "Apres calcul: " << contours.size() << endl;
//	      cv::drawContours(bground, contours, -1, cv::Scalar(0,0,255),2);
//
//	      blur(bground, bground,  Size(1,1));
//	      cv::dilate(bground, gray, cv::Mat());
//	      cv::threshold(gray, gray, threshold-10, 255, THRESH_BINARY_INV );
//	      cv::findContours(gray, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);
//	      cv::drawContours(img, contours, -1, cv::Scalar(0,0,105),-1);
//	      prtsp(contours, img);
//	      	      usleep(50000);
//	      imshow("Actual Frame", img);
//	      imshow("Background", bground);
//
//
//	      img = Mat();
//	      contours.clear();
//	     // cv::cvtColor(bground, bground, CV_GRAY2BGR);
//	      if (waitKey(10) >= 0)
//	    	  break;
//	    }
//
//	  return 0;
//
//}
