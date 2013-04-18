///*
// * FormList.hpp
// *
// *  Created on: 4 avr. 2013
// *      Author: JC
// */
//
//#ifndef FORMLIST_HPP_
//#define FORMLIST_HPP_
//
//#include <iostream>
//#include <deque>
//#include "Form.hpp"
//
//namespace cv {
//
//class TrackForms {
//
//public:
//	std::vector<Form> trackedForms;
//	std::vector<Form> suspiciousForms;
//	TrackForms();
//	virtual ~TrackForms();
//	void Update(Form &irform, int inbFrm);
//	void Render(IplImage *ipfrm);
//	void SetSizes(int x, int y){capW = x; capH = y; };
//
//private:
//	int capW;
//	int capH;
//	int ctCurFrm;
//	int nbEffTracked;
//	int nbEffSuspic;
//
//	bool findFormByXY(Point &irpos, int &id);
//	bool findFormByS(Rect &irrec, int iarea, int &id);
//	bool findFormByRGB(Scalar &scl, int &id);
//	void updateForm(Form &irfrom, int id);
//	void addForm(Form &irform);
//	void removeOld();				// Purge les id = 0, delay - lastSeen <= 0 et stillAlive = false
//
//};
//
//} /* namespace cv */
//#endif /* FORMLIST_HPP_ */
