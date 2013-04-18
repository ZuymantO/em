/*
 * EMMonitor.hpp
 *
 *  Created on: 18 avr. 2013
 *      Author: JC
 */

#ifndef EMMONITOR_HPP_
#define EMMONITOR_HPP_
#include <iostream>
#include <vector>
#include "Camera.hpp"
#include "CAMAnalyser.hpp"
#include "TrackForms.hpp"
#include "Form.hpp"

#define DEFAULT_TOP_BAR_H 20;
#define DEFAULT_BOTTOM_BAR_H 40;
#define DEFAULT_MONITOR_NAME "MBP-JC-CAM"
using namespace std;
namespace cv {

class EMMonitor {
public:
	CAMAnalyser* 	analyser;
	Camera*			cam;
	VideoWriter*	writer;
	VideoCapture*	cap;
	Mat*			frame;
	Mat*			cadre;
	Mat*			experimental;
	string			monitorName;
	int framesWidth;
	int framesHeight;
	int	barTopHeight;
	int barBottomHeight;
	EMMonitor();

	EMMonitor(Camera* ipcam){
		initMonitor();

		cam = ipcam;
		cap = &(cam->cap);
		analyser = new CAMAnalyser(cam);
		initAnalyser();
		framesWidth = cam->cap.get(CV_CAP_PROP_FRAME_WIDTH);
		framesHeight = cam->cap.get(CV_CAP_PROP_FRAME_HEIGHT);
		cadre		= new Mat(Size(framesWidth, framesHeight + barTopHeight + barBottomHeight) , cam->actualFrame.type());
		((cam->actualFrame).copyTo(*frame));
	};

	virtual ~EMMonitor();


	void drawRect(vector<Point> &pts, Mat &img){
		int i = 1, n = pts.size() ;
		int maxX = 0;
		int maxY = 0;
		int minX = 10000;
		int minY = 10000;
		std::vector<cv::Point>::iterator it;
		Point ctr;
		int sumX = 0, sumY = 0;
		for(it = pts.begin(); it != pts.end() && i < n; ++it){
			sumX += it->x;
			if(it->x > maxX)
				maxX = it->x;
			if(it->x < minX)
				minX = it->x;

			sumY += it->y;
			if(it->y > maxY)
				maxY = it->y;
			if(it->y < minY)
				minY = it->y;

		}
		ctr.x = sumX/n;
		ctr.y = sumY/n;
		rectangle(
		            img,
		            Point(minX-5, minY-5),
		            Point(maxX+5, maxY+5),
		            Scalar(0,200,0)
		        );
	}

	void drawRects(vector<vector<cv::Point> > &ct, Mat &img){
		if(&img == NULL) return;

		int i = 1, n = ct.size() ;
		std::cout << "NB calculé : " << n << endl;
		if(ct.size() == 1) return;
		 std::vector<std::vector<cv::Point> >::iterator it;
		 for(it = ct.begin(); it != ct.end() && i < n; ++it){
			 if(it->size() > 20){
				 cout << "\tForme " << i << " : " << it->size() << " points : " << endl;
				 drawRect(*it, img);
			 }
			 i++;
		 }
	}

	void captureVideo(){

		while (true){
			//Mat tmp = cadre->clone();
			cam->readFrame();
			analyser->boundsWithSimpleFilter(*experimental);
			drawRects(analyser->validContours, *frame);
			usleep(20000);

			drawMatInMat(*cadre, *frame);
			drawFrameInfos();
			putText(*cadre, getNewString(" ", cam->cap.get(CV_CAP_PROP_FRAME_COUNT)), Point(2, 15), 1, 0.8, Scalar(255,255,255));
			showFrame();

			if (waitKey(10) >= 0)
				break;
			//cadre->setTo(0);
			//tmp.copyTo(*cadre);
			cam->actualFrame.copyTo(*frame);
			analyser->clean();
		}
	};

	void drawMonitorInfos(){
		if(cadre == NULL) return;
		string str = monitorName;
		string fps =  getNewString(" FPS : ", cam->cap.get(CV_CAP_PROP_FPS));
		string format =  getNewString(getNewString(" ", framesWidth).append("x"), framesHeight);
		str.append(format).append(fps);
		putText(*cadre, str.append(getNewString(" ", cam->cap.get(CV_CAP_PROP_FRAME_COUNT))), Point(2, 15), 1, 0.8, Scalar(255,255,255));
	}
	void drawFrameInfos(){
		if(cadre == NULL) return;

		string fps =  getNewString(" FPS : ", cam->cap.get(CV_CAP_PROP_FPS));
		string format =  getNewString(getNewString(" ", framesWidth).append("x"), framesHeight);
		monitorName.append(format).append(fps);
	}

	void showFrame(){

		imshow("Monitor", *frame);
		imshow("Background", *cadre);

	};


	/**
	 * Dessiner une image dans une autre avec addWeighted == usage du channel alpha etc.
	 */
	void drawMatInMatWithABG(const Mat &irbigMat, const Mat &irsmallMat,
			double ialpha = 1. , double ibeta = 0.2, double igamma = 0.){
		Mat dstROI = irbigMat(Rect(Point(0, barTopHeight), Size(irsmallMat.cols, irsmallMat.rows)));
		addWeighted(dstROI, ialpha, irsmallMat, ibeta, igamma, dstROI, irsmallMat.type());
	};

	void drawMatInMat(const Mat &irbigMat, const Mat &irsmallMat ){
		Rect roiZone = Rect(Point(0, barTopHeight), Size(irsmallMat.cols, irsmallMat.rows));
		Mat dstROI = irbigMat(roiZone);
		irsmallMat.copyTo(dstROI);

		// On peut le faire avec des masks alpha gamma etc.. (Utile pour coller un logo)
		//addWeighted(dstROI, 1.0, irsmallMat,0.3, 0., dstROI, irsmallMat.type());
		//frame->copyTo(irbigMat(Rect(Point(0, barTopHeight), Size(frame->cols, frame->rows))));
	};


	string getNewString(const string& str, double val){
	  std::stringstream sstm;
	  sstm << str << val;
	  return sstm.str();
	}

	string getNewString(const string& str, int val){
	  std::stringstream sstm;
	  sstm << str << val;
	  return sstm.str();
	}

private:

	void initMonitor(){
		analyser 	= NULL;
		cam			= NULL;
		writer		= NULL;
		cap			= NULL;
		frame		= new Mat();
		cadre		= new Mat();
		experimental = NULL;
		framesWidth	= 0;
		framesHeight= 0;
		barTopHeight	= DEFAULT_TOP_BAR_H;
		barBottomHeight	= DEFAULT_BOTTOM_BAR_H;
		monitorName = DEFAULT_MONITOR_NAME;

	}

	void initAnalyser(){
		if(analyser == NULL) return;
		analyser->areaSeuilMin	= 10;
		analyser->areaSeuilMax 	= (double) framesWidth*framesHeight/2;

		if(analyser->areaSeuilMax > (1600*1200)/16 ){	// UXGA et QXGA : Non supporte
			analyser->areaSeuilMin = 150*150;
		}
		else if(analyser->areaSeuilMax > (1400*1050)/16 ){	// SXGA+, UXGA + Non supporte
			analyser->areaSeuilMin = 140*140;
		}
		// Affichage d'ecran supportes, les images doivent etre inferieurs a cette taille
		else if(analyser->areaSeuilMax > (1280*1020)/16 ){	// SXGA maximum supporte
			analyser->areaSeuilMin = 120*120;
		}
		else if(analyser->areaSeuilMax > (1024*768)/16 ){	// XGA+ + supporte
			analyser->areaSeuilMin = 100*100;
		}
		else if(analyser->areaSeuilMax > (800*600)/4 ){	// SXGA, UXGA + Non supporte
			analyser->areaSeuilMin = 80*80;
		}
		else if(analyser->areaSeuilMax > (640*480)/4 ){	// VGA, supporte
			analyser->areaSeuilMin = 40*40;
		}
		else if(analyser->areaSeuilMax > (320*240)/2 ){	// QVGA,  supporte
			analyser->areaSeuilMin = 20;
		}
	}
};

} /* namespace cv */
#endif /* EMMONITOR_HPP_ */
