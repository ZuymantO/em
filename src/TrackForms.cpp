/*
 * TrackForms.cpp
 *
 *  Created on: 4 avr. 2013
 *      Author: JC
 */

#include "TrackForms.hpp"
#include "Form.hpp"
#include <iostream>
#include <vector>

namespace cv {

TrackForms::TrackForms() {
	// TODO Auto-generated constructor stub

}

TrackForms::~TrackForms() {
	// TODO Auto-generated destructor stub
}

void TrackForms::Update(Form &irform, int inbfrm){
	// verifier si le forum existe dans les trackes
	// Si oui (ancienne (position des vieux
}
void TrackForms::drawForms(Mat &img){
	vector<Form>::iterator it = this->trackedForms.begin();
	bool b = false;
	for(; it < this->trackedForms.end() ; it++){
		Form tmp = *it;
		tmp.drawForm(img);
	}

}

void TrackForms::tracks(vector<Form> &forms){
	if(this->suspiciousForms.empty() || forms.empty()){
		this->suspiciousForms = forms; // On gere pas le cas forms vide TODO gerer le cas forms vide
		return ;
	}
	// Associer les forms suspectes a forms
	this->suspiciousForms = forms;
	// decremantee la dure de vu des forms reel de 1 (si formes reelles exitent, sinon associer forms a formes reelles)
	decrForms();

	// verifier si les formes dans suspects se trouvent dans les reel (si reel non vide)
	// Si oui (position reel == ancienne position suspect) on met a jour la position et gardons le nom et id
	// Si non (non trouve dans la liste) on l'ajoute en attribuant un nouvelle identifiant
	// On associe cette nouvelle liste a la liste reel ( recherchons les forms dont la dure de vie est fini pour les supprimer)

}


void TrackForms::decrForms(){
	vector<Form>::iterator it = this->trackedForms.begin();
	bool b = false;
	for(; it < this->trackedForms.end() ; it++){
		Form tmp = *it;
		tmp.lastSeen = tmp.lastSeen - 1;
	}
}

bool TrackForms::findFormByXY(Point &irpos, int &id){

	vector<Form>::iterator it = this->trackedForms.begin();
	bool b = false;
	for(; it < this->trackedForms.end() ; it++){
		Form tmp = *it;
		if(irpos == tmp.position || irpos == tmp.lastPos){
			// C'est la meme position (devrait pas arriver) c'est la position précédente (OK)
			return true;
		}else if((irpos.x == tmp.position.x + 2) && (irpos.x == tmp.position.y - 2 || irpos.x == tmp.position.y + 2)){
			return true;
		}else return false;
	}

	return false;
}

bool TrackForms::findFormByS(Rect &irrec, int iarea, int &id){

	return true;
}
bool TrackForms::findFormByRGB(Scalar &scl, int &id){
	return true;
}

void TrackForms::updateForm(Form &irfrom, int id){

}

void TrackForms::addForm(Form &irform){
	this->trackedForms.push_back(irform);
};

void TrackForms::addForms(std::vector<Form> &irforms){
	for(int i = 0; i < irforms.size(); i++){
		this->addForm(irforms.at(i));
	}
};

/**
 * Creer une forme et l'ajouter a la liste des formes
 */
void TrackForms::createFormAndAdd(Rect &irRect){
	Form f(irRect);
	f.id = findMaxID(*this) + 1;

	f.update(f.position);	// Met a jour son nom apres initialisation
	this->addForm(f);
};

/**
 * Trouver l'ID le plus grand de la liste des IDs
 */
int TrackForms::findMaxID(TrackForms &tr){
	vector<Form>::iterator it = tr.trackedForms.begin();
	int max = 0;
	for(; it < tr.trackedForms.end() ; it++){
		Form tmp = *it;
		if(max < tmp.id)
			max = tmp.id;
	}
	return max;
};

/**
 * Ajouter plusieurs forme en une fois
 */
void TrackForms::createFormsAndAdd(std::vector<Rect> &irRectForms){
	for(int i = 0; i < irRectForms.size(); i++){
		this->createFormAndAdd(irRectForms.at(i));
	}
}

} /* namespace cv */
