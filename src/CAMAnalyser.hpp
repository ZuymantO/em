/*
 * CAMAnalyser.hpp
 *
 *  Created on: 17 avr. 2013
 *      Author: JC
 */

#ifndef CAMANALYSER_HPP_
#define CAMANALYSER_HPP_
#include <iostream>
#include "Camera.hpp"



#define DEFAULT_BLUR_SIZE (Size(3, 3))
#define DEFAULT_NDBLUR_SIZE  (Size(1,1))
#define DEFAULT_THRESHOLD	15
#define DEFAULT_READ_FILE	"./default.avi"
#define DEFAULT_HIST_DIFF	3
#define DEFAULT_MIN_AREA	30
#define DEFAULT_MAX_AREA	1000

namespace cv {

class CAMAnalyser {
public:
	Mat		*frame;
	Size	blurSize;
	Size	sndBlurSize;
	Camera* cam;
	std::vector<std::vector<cv::Point> > tmpContours; // Contours suspect
	std::vector<std::vector<cv::Point> > validContours;
	double	areaSeuilMin, areaSeuilMax;

	CAMAnalyser(){
		initCAMAnalyser();
	};

	CAMAnalyser(Camera* ipcam){
		initCAMAnalyser();
		if(ipcam == NULL){
			std::cout << "Camera is empty" << std::endl;
		}
		cam = ipcam;
		frame = &(ipcam->actualFrame);

	};

	void bgr2gray(Mat* ipframe){
		std::cout << " bgr2gray " << ipframe << std::endl;
		cvtColor(*ipframe, *ipframe, CV_BGR2GRAY);
	}

	void gray2bgr(Mat* ipframe){
		std::cout << " gray2bgr " << ipframe << std::endl;
		cvtColor(*ipframe, *ipframe, CV_GRAY2BGR);
	}

	void blurFrames(Mat *img, Mat* dst = NULL, Size blurS = DEFAULT_BLUR_SIZE){
		if(dst == NULL)
			blur(*img, *img, blurS);
		else
			blur(*img, *dst, blurS);
	};

	void retainValidBounds(double iareaMinLimit = DEFAULT_MIN_AREA,
			double iareaMaxLimit = DEFAULT_MAX_AREA){
		if(tmpContours.size()  < 2)
			return;
		std::cout << " Nb A diminuer contours " << tmpContours.size() << std::endl;
		    for (int i = 0; i < tmpContours.size(); i++)
		    {
		        double area = cv::contourArea(tmpContours[i]);
		        if (area >= areaSeuilMin && area <= areaSeuilMax)
		            validContours.push_back(tmpContours[i]);
		}

	};

	void boundsWithSimpleFilter (Mat &iomatDst){
		Mat ldiff, tmp;
		subFrame(ldiff);
		ldiff.copyTo(tmp);
		bgr2gray(&ldiff);
		threshold(ldiff, ldiff, cam->thresHold, 255, THRESH_BINARY );

		erode(ldiff, ldiff, Mat());
		dilate(ldiff, ldiff, cv::Mat());
		cv::findContours(ldiff, tmpContours, RETR_LIST, CHAIN_APPROX_SIMPLE);

		retainValidBounds();	// Diminuer le nombre de contour en ne prenant que les plus pertinent
		if (validContours.size() > 1 && &iomatDst != NULL)
			drawContours(iomatDst, validContours, -1, cam->brushColor, cam->brushSize+1.5);

	}

	void boundsWithChansAndMorph (Mat &iomatDst){
		Mat gtmp;
		subFrame(gtmp);
		std::vector<cv::Mat> channels;
		cv::split(gtmp, channels);
		cv::Mat d = cv::Mat::zeros(gtmp.size(), CV_8UC1);
		for (unsigned int i = 0; i < channels.size(); i++){
			cv::Mat tmp;
			cv::threshold(channels[i], tmp, cam->thresHold, 255, CV_THRESH_BINARY);
			d |= tmp;
		}

		Mat kernel, e;
		getStructuringElement(cv::MORPH_RECT, cv::Size(8,8));
		morphologyEx(d, e, cv::MORPH_CLOSE, kernel, cv::Point(-1,-1));	// operation de morphologie (remplace erode etc de l'autre methode)
		findContours(e, tmpContours, RETR_LIST, CHAIN_APPROX_SIMPLE);


		retainValidBounds();	// Diminuer le nombre de contour en ne prenant que les plus pertinent
		if (validContours.size() > 1)
			drawContours(iomatDst, validContours, -1, cam->brushColor, cam->brushSize);

	}

	void clean(){
		validContours.clear();
		tmpContours.clear();
	}
	virtual ~CAMAnalyser();

private:
	void subFrame(Mat &irdst){
		Mat srcBlur1, srcBlur2;
		blurFrames(frame, &srcBlur1);
		blurFrames(&cam->prevFrame, &srcBlur2);
		cam->createDiff(&srcBlur1, &srcBlur2, &irdst);
	}

	void initCAMAnalyser(){
		areaSeuilMin = DEFAULT_MIN_AREA;
		areaSeuilMax = DEFAULT_MAX_AREA;
		frame = new Mat();
		blurSize = DEFAULT_BLUR_SIZE;
		sndBlurSize = DEFAULT_NDBLUR_SIZE;
	};

};

} /* namespace cv */
#endif /* CAMANALYSER_HPP_ */
