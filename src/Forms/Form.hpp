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

namespace cv {

class Form {
public:
	int id;
	int delay;
	bool stillAlive;
	std::string name;
	Rect rect;

	Form(): id(0), delay(0), stillAlive(true), name(""), rect(){
		// TODO Auto-generated constructor stub
	}
	virtual ~Form(){};
};

} /* namespace cv */
#endif /* FORM_H_ */
