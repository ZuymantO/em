/*
 * Form.h
 *
 *  Created on: 4 avr. 2013
 *      Author: JC
 */

#ifndef FORM_HPP_
#define FORM_HPP_
#include <iostream>
#include <sstream>
#include "opencv2/core/core.hpp"
#define DEFAULT_FORM_DELAY	100 // 25 img / s => autorisation a disparaitre au plus 4 secondes
#define DEFAULT_FORM_ID		0
#define DEFAULT_FORM_COLOR	Scalar(255, 0, 0)
#define DEFAULT_FORM_POS	Point(0,0)
#define DEFAULT_FORM_NAME	"OBJ "

namespace cv {

class Form {

public:
	int delay;	// Nombre de frame avant de supprimer la form (delay - lastSeen > 0)
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

	int dirX, dirY, dirZ;	// Direction suspectee ...
	Form(int _id, int _delay, bool sa, std::string &nm): id(_id), stillAlive(sa), name(nm), rect(){
		initForm();
	};

	Form(Rect &rct): rect(rct){
		initForm();
		this->position = Point((rct.x+rct.width)/2, (rct.y + rct.height)/2);
	};

	Form(){
		// TODO Auto-generated constructor stub
		initForm();
	}
	virtual ~Form(){};

	void update(Point &pos){
		std::ostringstream oss;
		oss << this->id;
		this->name = this->name.append(string(oss.str()));
		this->lastPos = this->position;
		this->position = pos;
		this->lastSeen = DEFAULT_FORM_DELAY;

	}

	Point getPosition(){
		return this->position;
	}

	void drawForm(Mat &img){
		rectangle(img, rect, Scalar(0,200,0));
		putText(img, name, position, 1, 0.8, Scalar(200.,200.,0.));
	};

	bool isAlive(){
		if(lastSeen > 0) return true;
		else stillAlive = false;

		return stillAlive;
	}


private:
	void initForm(){
		delay 	= DEFAULT_FORM_DELAY;
		id	 	= DEFAULT_FORM_ID;
		color 	= DEFAULT_FORM_COLOR;
		name 	= DEFAULT_FORM_NAME;
		stillAlive = true;
		 position= DEFAULT_FORM_POS;
		lastPos = position;
		cat = 0;
		area = rect.area();
		lastSeen = 0;
		dirX = dirY = dirZ = 0;

	}
};

} /* namespace cv */
#endif /* FORM_H_ */
