/*
 * Form.h
 *
 *  Created on: 4 avr. 2013
 *      Author: JC
 */

#ifndef FORM_HPP_
#define FORM_HPP_
#include <iostream>
#include "opencv2/core/core.hpp"
#define DEFAULT_DELAY	50
namespace cv {

class Form {
public:
	static int delay;	// Nombre de frame avant de supprimer la form (delay - lastSeen > 0)
	int id;	// Identifiant de l'objet si id <= 0 alors l'objet est hors du champs
	int lastSeen ;// nombre de frame depuis la derniers localisation
	int area ;			// Surface occupe par l'objet (usage ulterieur si cvBlob utilise)
	int cat;			// Identifier si objet a tracker (> 0 mobile et < 0 immobile)
	bool stillAlive;	// Indique si l'objet est toujours en jeu (utilisation ulterieure)
	std::string name;	// Nom de l'objet (sans id)
	Rect rect;			// Cadre regroupant l'objet.
	Point position;		// Position actuelle de l'objet (centre de gravité)
	Point lastPos;		// Derniere position de l'objet
	Scalar color;		// Couleur attribue a l'objet

	Form(int _id, int _delay, bool sa, std::string &nm): id(_id), stillAlive(sa), name(nm), rect(){
		initDefaultForm();
	}

	Form(): id(0), stillAlive(true), name(""), rect(){
		// TODO Auto-generated constructor stub
		initDefaultForm();
	}
	virtual ~Form(){};

private:
	void initDefaultForm(){
		Form::delay = DEFAULT_DELAY;
	}
};

} /* namespace cv */
#endif /* FORM_H_ */
