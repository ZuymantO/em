///*
// * TrackForms.cpp
// *
// *  Created on: 4 avr. 2013
// *      Author: JC
// */
//
//#include "TrackForms.hpp"
//#include "Form.hpp"
//
//namespace cv {
//
//TrackForms::TrackForms() {
//	// TODO Auto-generated constructor stub
//
//}
//
//TrackForms::~TrackForms() {
//	// TODO Auto-generated destructor stub
//}
//
//void TrackForms::Update(Form &irform, int inbfrm){
//	ctCurFrm = inbfrm;
//	int nrXY, nrS, nrCOL, nrDX;
//	int id=0;
//	nrXY = findFormByXY(irform.position,id);
//	nrS = findFormByS(irform.rect, irform.area, id);
//	if(nrS == 0) nrXY = 0;	// si la surface indiqué est vide, on annule le maj
//
//	if(nrXY == 1)	// si on a trouve un objet a la position x y et que la surface est occupe
//		updateForm(irform,id); // mettre a jour
//	if(nrXY == 0)	// Si en x y il n'y a rien d'enregistre,
//		addForm(irform);	// on l'enregistre
//
//
//}
//
//bool TrackForms::findFormByXY(Point &irpos, int &id){
//	return true;
//}
//bool TrackForms::findFormByS(Rect &irrec, int iarea, int &id){
//
//	return true;
//}
//bool TrackForms::findFormByRGB(Scalar &scl, int &id){
//	return true;
//}
//void updateForm(Form &irfrom, int id){
//
//}
//} /* namespace cv */
