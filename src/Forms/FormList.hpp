/*
 * FormList.hpp
 *
 *  Created on: 4 avr. 2013
 *      Author: JC
 */

#ifndef FORMLIST_HPP_
#define FORMLIST_HPP_

#include <iostream>
#include <deque>
#include "Form.hpp"

namespace cv {

class FormList {

public:
	std::deque<Form> forms;
	FormList();
	virtual ~FormList();
};

} /* namespace cv */
#endif /* FORMLIST_HPP_ */
