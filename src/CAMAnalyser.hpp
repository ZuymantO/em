/*
 * CAMAnalyser.hpp
 * Include motion detection and other stuff
 *  Created on: 17 avr. 2013
 *      Author: JC
 */

#ifndef CAMANALYSER_HPP_
#define CAMANALYSER_HPP_
#include <iostream>
#include "Camera.hpp"
#include <vector>
#define DEBUG 1


#define DEFAULT_BLUR_SIZE (Size(3, 3))
#define DEFAULT_NDBLUR_SIZE  (Size(1,1))
#define DEFAULT_THRESHOLD	15
#define DEFAULT_HIST_DIFF	3
#define DEFAULT_MIN_AREA	30
#define DEFAULT_MAX_AREA	1000
using namespace std;
namespace cv {

class CAMAnalyser {
public:
	Mat		*frame;
	Size	blurSize;
	Size	sndBlurSize;
	Camera* cam;
	std::vector<std::vector<cv::Point> > tmpContours; // Contours suspect
	std::vector<std::vector<cv::Point> > validContours;
	std::vector<Rect>					uniqContours; // Les rectangles fusionnees
	double	areaSeuilMin, areaSeuilMax;

	CAMAnalyser(){
		initCAMAnalyser();
	};

	CAMAnalyser(Camera* ipcam){
		initCAMAnalyser();
		if(ipcam == NULL){
			if(DEBUG)
				std::cout << "Camera is empty" << std::endl;
		}
		cam = ipcam;
		frame = &(ipcam->actualFrame);

	};

	void bgr2gray(Mat* ipframe){
		cvtColor(*ipframe, *ipframe, CV_BGR2GRAY);
	}

	void gray2bgr(Mat* ipframe){
		cvtColor(*ipframe, *ipframe, CV_GRAY2BGR);
	}

	void blurFrames(Mat *img, Mat* dst = NULL, Size blurS = DEFAULT_BLUR_SIZE){
		if(dst == NULL)
			blur(*img, *img, blurS);
		else
			blur(*img, *dst, blurS);
	};

	pair<Point, Rect> rectFromPoints(vector<Point> &pts){
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

		return pair<Point, Rect>(ctr, Rect(Point(minX, minY-5), Point(maxX, maxY+5)));
	};

	vector<pair<Point, Rect> >* getPRList(vector<vector<Point> > &vpts){
		int i = 1, n = vpts.size() ;
		vector<pair<Point, Rect> >* rv = new vector<pair<Point, Rect> >();
		vector<vector<Point> >::iterator it ;
		for(it = vpts.begin(); it != vpts.end() && i < n; ++it){
			rv->push_back(rectFromPoints(*it));
		}

		return rv;
	};

	vector< Rect >* getRectList(vector<vector<Point> > &vpts){
		//cout << "vpts size : " << vpts.size() << endl;
		int i = 1, n = vpts.size() ;
		vector< Rect >* rv = new vector<Rect >();
		vector<vector<Point> >::iterator it ;
		for(it = vpts.begin(); it != vpts.end() && i < n; ++it){
			rv->push_back(rectFromPoints(*it).second);
		}
		//cout << "Rect size : " << rv->size();
		return rv;
	};

	/*************************************************************************************
	 * 								SORT AND VALIDATION
	 * Selections de bon rectangles
	 * Rafinement des rectangles
	 * Trie des rectangles
	 * ************************************************************************************
	 */

	bool retainValidBounds(double iareaMinLimit = DEFAULT_MIN_AREA,
			double iareaMaxLimit = DEFAULT_MAX_AREA){
		if(tmpContours.size()  < 2)
			return false;
			if(DEBUG)
				cout << " Nb contours " << tmpContours.size() << endl;
		    for (int i = 0; i < tmpContours.size(); i++)
		    {
		        double area = cv::contourArea(tmpContours[i]);
		        if (area >= areaSeuilMin && area <= areaSeuilMax)
		            validContours.push_back(tmpContours[i]);
		    }
		    if(DEBUG)
		    	cout << " Nb Valid ctrs " << validContours.size() << endl;
		    return true;
	};

	// Obtenir la liste des rectangles inclus dans irrect
	bool findIncludedRects(Rect &irrect, vector<Rect> *iprectList, vector<Rect> *opRslts){
		bool b = false;
		if(iprectList == NULL || opRslts == NULL) // TODO verifier opRslts a part + exception
			return b;

		vector<Rect >::iterator it = iprectList->begin();
		for (; it != iprectList->end(); it++){
			Rect r = *it;
			if(r != irrect && isOnFirst(irrect, r)){
				opRslts->push_back(r);
				b = true;
			}
		}
		return b;
	};

	void rectsRemoveElements(vector<Rect> *iprectList, vector<Rect> *iptoRemove, vector<Rect>* opRslts){
		if(iprectList == NULL || opRslts == NULL) // TODO verifier opRslts a part + exception
			return ;

		vector<Rect >::iterator it = iprectList->begin();
				for (; it != iprectList->end(); it++){
					Rect r = *it;
					// Si ca appartient aux elements a supprimer, ne pas considerer
					if(find(iptoRemove->begin(), iptoRemove->end(), r) == iptoRemove->end())
						opRslts->push_back(r);
				}
	}

	// Obtenir la liste des rectangles inclus dans irrect
	bool findContainerRects(Rect &irrect, vector<Rect> *iprectList, vector<Rect> *opRslts){
		bool b = false;
		if(iprectList == NULL || opRslts == NULL) // TODO verifier opRslts a part + exception
			return b;

		vector<Rect >::iterator it = iprectList->begin();
		for (; it != iprectList->end(); it++){
			Rect r = *it;
			if(isOnSecond(irrect, r)){
				opRslts->push_back(r);
				b = true;
			}
		}
		return b;
	};

	// Visites all rect to find the intersected ones.
	bool findInter(Rect &irrect, vector<pair<Point, Rect> >* iprectList, vector<Rect> *oprslt){
		bool b = false;
		if(iprectList == NULL || oprslt == NULL)
			return b;
//		vector<pair<Point, Rect> >::iterator it = iprectList->begin();
//	    for (; it != iprectList->end(); it++)
//	    {
//	    	pair<Point, Rect> tmpRslt = *it;
//	    	//vector<Rect>::iterator *itp = tmpRslt->begin();
//	    	//for(; itp != tmpRslt->end(); itp++){
//	    		Rect r1 = tmpRslt.second;
//	    		if(hasInter(irrect, r1)){
//	    			b = true;
//	    			oprslt->push_back(r1);
//	    		//}
//	    	//}
//	    }
	    return b;
	};

	// Verify and exclude small forms into bigger forms
	bool iterForIntersec(vector<Rect >* iprectList, vector<Rect> *oprslt){
		bool b = false;
		if(iprectList == NULL || oprslt == NULL)
			return b;

		vector< Rect >::iterator it = iprectList->begin();
	    for (; it != iprectList->end(); it++)
	    {
	    	Rect tmpRslt;
	    	Rect tpRect = *it;
	    	vector< Rect >::iterator tmpIt;
	    	for(tmpIt = it+1;  tmpIt != iprectList->end(); tmpIt++){
	    		Rect ri = *tmpIt;
//	    		if(findInter(ri, tpRect, &tmpRslt)){
////	    		b = true;
////	    		oprslt->push_back(r1);
	    	}
	    }
	    return (b);
	};

	// fusionner un ensemble de rectangle en un.
	bool fusionRects(vector<Rect> *ipsrc, Rect *irdst){
		if(ipsrc == NULL || irdst == NULL) return false;

		vector< Rect >::iterator it = ipsrc->begin();
		Rect tmp = *it;
	    for (; ++it != ipsrc->end();)
	    {
	    	Rect r1 = *it;
	    	*irdst = r1 | tmp;
	    }

		return false;
	};


	bool hasInter(Rect &ir1, Rect &ir2){
		Rect r = ir1 & ir2;
		return (r.height != 0 && r.width != 0);
	}


	bool isOnFirst(Rect &ir1, Rect &ir2){ // second rect is on the first rect
		Rect r = ir1 & ir2;
		return (r == ir1);
	}

	bool isOnSecond(Rect &ir1, Rect &ir2){ // First rect is on the second rect
		Rect r = ir1 & ir2;
		return (r == ir2);
	}

	bool isIncluded(Rect &ir1, Rect &ir2){
		Rect r = ir1 & ir2;
		return (r == ir1 || r == ir2);
	}

	bool isTooNear(Rect &ir1, Rect &ir2, int idx = 2, int idy=2){
		Rect r = ir1 & ir2;
		if((ir1.x >= ir2.x + 2 || ir1.x <= ir2.x - 2) && (ir1.y >= ir2.y + 2 || ir1.y <= ir2.y - 2))
			return (r.height != 0 && r.width != 0);
		return false;
	}

	// fusionner deux rectangle lorsqu'ils sont contenu l'un dans l'autre
	bool fusionRect(Rect &irsrc1, Rect &irsrc2, Rect *opdst){
		Rect rTmp = irsrc1 & irsrc2;
		if(rTmp.height == 0 || rTmp.width == 0) {
			if(DEBUG) cout << " rect trop  petit " << endl;
			return false;
		}

		if( rTmp == irsrc1 || rTmp == irsrc2){
			*opdst = irsrc1 | irsrc2;
			if(DEBUG) cout << " **** ---- On prend le rectangle le plus grand" << endl;
			return true;
		}
		else{
			Point ct1((irsrc1.width/2 + irsrc1.x), (irsrc1.height/2 + irsrc1.y));
			if((irsrc2.x < ct1.x  && irsrc2.x + irsrc2.width > ct1.x) && (irsrc1.y < ct1.y  && irsrc2.y + irsrc2.height > ct1.y)){
				*opdst = irsrc1 | irsrc2;
				if(DEBUG) cout << " ++++++++++++++ + Union de rectangle 1 " << irsrc1 <<  "dans 2" << irsrc2 << endl;
				return true;
			}
			Point ct2((irsrc2.width/2 + irsrc2.x), (irsrc2.height/2 + irsrc2.y));
			if((irsrc1.x < ct2.x  && irsrc1.x + irsrc1.width > ct2.x) && (irsrc1.y < ct2.y  && irsrc1.y + irsrc1.height > ct2.y)){
				*opdst = irsrc1 | irsrc2;
				if(DEBUG) cout << " ++++++++++++++ += Union de rectangle 2 " << irsrc2 <<  "dans 1" << irsrc1 << endl;
				return true;
			}
		}
		return false;
	};

	static bool rectInfRectX(const Rect &irp1, const Rect &irp2){
		return irp1.x < irp2.x;
	};

	bool sortByX(vector<Rect >& ircontours, bool iasc=true){
		if(ircontours.empty()){
			return false;
		}if(ircontours.size() == 1){
			return true;
		}
		std::sort(ircontours.begin(), ircontours.end(), (cv::CAMAnalyser::rectInfRectX));
	    return true;
	};

	// Verify and exclude small forms into bigger forms
	bool retainUniqBounds(unsigned int ideltax = 0, unsigned int ideltay = 0){

		if(validContours.empty()){
			if(DEBUG)
				cout << "No valide Bounds Yet. \n Building... ---" << endl;
			if(!retainValidBounds()) return false;
		}

		if(DEBUG)
			cout << "############################### ENTRE RETAIN UNIQUE ########################" << endl;
		if(DEBUG)
			cout << "#### NOMBRE D'ELEMENT DANS VALIDE BOUND : " << validContours.size() << " ####" << endl;
		vector<Rect>* rects = getRectList(validContours);
		if(! sortByX(*rects)) return false ;
		vector<Rect> *rsltRects = new vector< Rect >(rects->begin(), rects->end());
		if(DEBUG)
			cout << "####----- RSLTRECTS : " << rsltRects->size() << " ++++++++++" << endl;

		vector<Rect>::iterator it = rects->begin();
	    for (; it != rects->end(); it++)
	    {
	    	Rect r1 = *it;
	    	vector<Rect> tmp, tmpRslt;

	    	if(findIncludedRects(r1, rsltRects, &tmp)){
	    		if(DEBUG)
	    			cout << "#### NOMBRE DEL DANS TMP : " << tmp.size() << " ++++++++++" << endl;
	    		rectsRemoveElements(rsltRects, &tmp, &tmpRslt);
	    		if(DEBUG)
	    			cout << "#---- NOMBRE DANS TMPRSLT : " << tmpRslt.size() << " -++++++++++" << endl;
	    		rsltRects = new vector<Rect>(tmpRslt.begin(), tmpRslt.end());
	    		if(DEBUG)
	    			cout << "-#*#-- RSLTRECTS APRES OP : " << rsltRects->size() << " ++++++++++" << endl;
	    	}else{
	    		if(DEBUG)
	    			cout << " Aucun element inclus dans " << r1 <<  endl;
	    	}
	    }
	    uniqContours = vector<Rect>(rsltRects->begin(), rsltRects->end());
	    if(DEBUG) cout << "#### NOMBRE D'ELEMENT DANS UNIQUE BOUND : " << uniqContours.size() << " ####" << endl;


	    vector<Rect> *tmpRects = new vector< Rect >(rsltRects->begin(), rsltRects->end());
	    vector<Rect> rslts; //*realRects = new vector< Rect >(rsltRects->begin(), rsltRects->end());
	    it = tmpRects->begin();
	    for (; it != tmpRects->end(); it++){
	    	Rect r1 = *it;
	    	for(vector<Rect>::iterator itj = it+1; itj != tmpRects->end(); itj++){
	    		Rect r2 = *itj;
	    		Rect dst;
	    		if(hasInter(r1, r2)){
	    			if(fusionRect(r1, r2, &dst)){
	    				rslts.push_back(dst);
	    				//cout << " New dans uniq Contour " << dst << endl;
	    			}
	    		}else{


	    			//cout << " Devrions MAJ les Contours uniques " << r1 <<  " et " << r2 << endl;
	    			//break;
	    		}
	    	}
	    }
	    uniqContours = vector<Rect>(rslts.begin(), rslts.end());
	    if(DEBUG) cout << "#*#*#*APRES FUSION *#*#*#  ON A " << uniqContours.size() << endl;
	    if(DEBUG) cout << "#*#*#*#*#*#*#*#*#*# SORTIE DE RETAIN UNIQUE #*#*#*#*#*#*#*#*#*#*#*#" << endl;

	    return true;
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
		uniqContours.clear();
	}
	virtual ~CAMAnalyser();

private:
	void subFrame(Mat &irdst){
		Mat srcBlur1, srcBlur2;
		blurFrames(frame, &srcBlur1, Size(3,3));
		blurFrames(&cam->prevFrame, &srcBlur2, Size(3,3));
		/*// Decouvert par hazard : Permet d'obtenir les contours
		erode(srcBlur1,srcBlur1, cv::Mat());
		dilate(srcBlur2,srcBlur2, cv::Mat());
		*/
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
