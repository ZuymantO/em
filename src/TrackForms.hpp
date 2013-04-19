/*
 * FormList.hpp
 *
 *  Created on: 4 avr. 2013
 *      Author: JC
 */

#ifndef FORMLIST_HPP_
#define FORMLIST_HPP_

#include <iostream>
#include <vector>
#include "Form.hpp"
#include "Camera.hpp"

namespace cv {

class TrackForms {

public:
	Camera *cam;
	std::vector<Form> trackedForms;
	std::vector<Form> suspiciousForms;
	TrackForms();
	virtual ~TrackForms();
	void Update(Form &irform, int inbFrm);

private:
	int capW;
	int capH;
	int ctCurFrm;
	int nbEffTracked;
	int nbEffSuspic;

	bool findFormByXY(Point &irpos, int &id);
	// Utilise plus tard pour optimiser le tracking (detecter les gens immobile p.e)
	bool findFormByS(Rect &irrec, int iarea, int &id);
	bool findFormByRGB(Scalar &scl, int &id);

	void updateForm(Form &irfrom, int id);
	void addForm(Form &irform);
	void addForms(std::vector<Form> &irforms);
	void createFormAndAdd(Rect &irRect);
	void createFormsAndAdd(std::vector<Rect> &irRectforms);
	void removeOld();				// Purge les id = 0, delay - lastSeen <= 0 et stillAlive = false
};

} /* namespace cv */
#endif /* FORMLIST_HPP_ */
