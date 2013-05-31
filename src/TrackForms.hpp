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
#include "CAMAnalyser.hpp"

namespace cv {

class TrackForms {

public:
	CAMAnalyser *ana;
	std::vector<Form> trackedForms;
	std::vector<Form> suspiciousForms;
	TrackForms();
	virtual ~TrackForms();
	void Update(Form &irform, int inbFrm);

	/**
	 * On genere la liste des point rect
	 * On les tries pour ne garder que les cas simple (les rectangles contenu sont supprime)
	 * On itere dessus pour en creer des forms
	 * On indique ces forme comme suspicieux
	 *
	 */
	void searchSuspicious(vector<Rect> *iprects){
		if(!suspiciousForms.empty())
			suspiciousForms.clear();
		vector<Rect>* founds = iprects;
		if(founds == NULL || founds->empty()) return ;

		vector<Rect >::iterator it ;
		for(it = founds->begin(); it != founds->end(); ++it){
			Form nf = *it;
			nf.area = nf.rect.area();
			//

			suspiciousForms.push_back(nf);
		}



	};

	/**
	 * On genere la liste des formes suspicieux
	 * On vérifie pour chaque forme suspect si elle existe dans la liste des formes tracke
	 * On met a jour (en deplacant la position) si on a trouvé une forme proche
	 * On ajoute dans les forme nouvelles (si aucune forme trouvé) seulement si la forme
	 * se trouve dans les coins avec une certaine marge
	 * ou en plein milieu ssi il existe une forme qui avait disparu en plein milieu (dans ces cas le delay est plus long pour detecter la reaparition)
	 *
	 */

	void trackedFilter(){

	};
	void tracks(vector<Form> &forms);
	void updateForm(Form &irfrom, int id);
	void addForm(Form &irform);
	void addForms(std::vector<Form> &irforms);
	void createFormAndAdd(Rect &irRect);
	void createFormsAndAdd(std::vector<Rect> &irRectforms);
	int findMaxID(TrackForms &tr);
	void drawForms(Mat &irimg);

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
	void decrForms();
	void removeOld();				// Purge les id = 0, delay - lastSeen <= 0 et stillAlive = false
};

} /* namespace cv */
#endif /* FORMLIST_HPP_ */
