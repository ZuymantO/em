/*
 * Camera.hpp
 *
 *  Created on: 17 avr. 2013
 *      Author: JC
 */

#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include <iostream>
#include<opencv2/opencv.hpp>
#include "opencv2/video/background_segm.hpp"
#include "opencv2/legacy/blobtrack.hpp"
#include "opencv2/legacy/legacy.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgproc/imgproc_c.h>


#define DEFAULT_BRUSH_COLOR (Scalar(255,0,0))
#define DEFAULT_BRUSH_SIZE  1.5
#define DEFAULT_THRESHOLD	15
#define DEFAULT_READ_FILE	"./default"
#define DEFAULT_HIST_DIFF	3
namespace cv {

class Camera {
public:

	VideoCapture 	cap;
	Scalar 			brushColor;
	int 			brushSize;
	int				frameCounter;
	int 			thresHold;
	Mat				actualFrame;
	Mat				prevFrame;
	Mat				diff;
	Mat				boundedFrame;
	std::string		videoStreamFile;
	int				majPrev;
	Camera(){
		initDefaultCamera();
		cap = VideoCapture(0);
		cap >> actualFrame;
		actualFrame.copyTo(prevFrame);

	};


	Camera(const std::string &irstream){
		initDefaultCamera();
		videoStreamFile = irstream;
		cap = VideoCapture(irstream);
		cap >> actualFrame;
		actualFrame.copyTo(prevFrame);
	};

	Camera(const std::string &irstream, int ibrushSize, Scalar &irbrushColor){
		initDefaultCamera();
		videoStreamFile = irstream;
		cap = VideoCapture(irstream);
		brushSize = ibrushSize;
		brushColor = irbrushColor;
		cap >> actualFrame;
		actualFrame.copyTo(prevFrame);
	};

	Mat readFrame(){

		if((++majPrevVal%majPrev) == 0){
			std::cout << " -------------- ";
			majPrevVal = 0;
			actualFrame.copyTo(prevFrame);
		}
		cap >> actualFrame;
		if (actualFrame.empty()){
			std::cout << " Unreadable Stream : Fermeture" << std::endl;
			release();
			exit(1);
		}
		return actualFrame;
	};

	void release(){
		cap.release();
	}

	Mat* createDiff(Mat *ipmatSrca = NULL, Mat *ipmatSrcb = NULL, Mat *iopmatDst = NULL){
		if(ipmatSrca == NULL)
			absdiff(actualFrame.clone(), prevFrame.clone(), diff);
		else
			absdiff(*ipmatSrca, *ipmatSrcb, *iopmatDst);
		return iopmatDst;
	}

	void loadDiff(){
		absdiff(actualFrame.clone(), prevFrame.clone(), diff);
	}
	virtual ~Camera(){ };

private:
	int				majPrevVal;
	void initDefaultCamera(){
//		if(singleton){
//			std::cout << "Une camera existe deja !!! " << std::endl;
//			exit (1);
//		}
//		singleton = true;
		brushColor = DEFAULT_BRUSH_COLOR;
		brushSize = DEFAULT_BRUSH_SIZE;
		thresHold	= DEFAULT_THRESHOLD;
		frameCounter = 0;
		majPrev = DEFAULT_HIST_DIFF;
		majPrevVal	= 0;
		videoStreamFile = "";
		actualFrame = Mat();
		prevFrame	= Mat();
		diff		= Mat();
		boundedFrame= Mat();

	}

};

} /* namespace cv */
#endif /* CAMERA_HPP_ */
